#include <iostream>
#include <fstream>

#include <IO/TUMDatasetStream.hpp>

namespace avr {

using std::string;
using std::deque;

// camera's intrisic parameters
static real_t freiburg[][9] = {
   /* fx     fy     cx     cy     d0       d1       d2       d3      d4   */
   { 517.3, 516.5, 318.6, 255.3, 0.2624, -0.9531, -0.0054,  0.0026, 1.1633 }, // freiburg1
   { 520.9, 521.0, 325.1, 249.7, 0.2312, -0.7849, -0.0033, -0.0001, 0.9172 }, // freiburg2
   { 535.4, 539.2, 320.1, 247.6, 0.0000,  0.0000,  0.0000,  0.0000, 0.0000 }  // freiburg3
};

static void GenerateK(size_t id, Matrix& K);
static void ConvertPose(const Vec7r& p, Matrix& T);
static bool Initialize();

TUMDatasetStream::TUMDatasetStream()
   : ImageStream(), xIntrinsic(MATRIX::Eye(3, 3)), xCurrentGT(MATRIX::Eye(4, 4)) {/* ctor */}

void TUMDatasetStream::NextFrame(Image& frame) {
   if(hasNext()) {
      string temp = xPath + xFiles.back();
      frame = cv::imread(temp, cv::IMREAD_UNCHANGED);

      ConvertPose(xData.back(), xCurrentGT);

      xFiles.pop_back();
      xData.pop_back();
   }
}

void TUMDatasetStream::LoadStream(const string& path, bool& loaded) {
   loaded = false;
   {
      size_t pos = path.find("freiburg");
      if(pos == string::npos) return;

      xID = (index_t)(path[pos + 8] - '1');
      if(xID > 2) { xID = -1; return; }
   }

   // reset
   xPath = "";
   xFiles.clear();
   xData.clear();

   // create initializer script
   loaded = Initialize();
   if(!loaded) return;

   // create associate file
   xPath = path + "/";
   int x = system( ("./initTUM.sh " + xPath).c_str() );
   std::ifstream file(xPath + "sequence.txt");
   if(!file) { loaded = false; return; }

   // load associate file
   {
      real_t ts, p[7];
      string rgb, depth;
      while((file >> ts >> p[0] >> p[1] >> p[2] >> p[3] >> p[4] >> p[5] >> p[6] >> ts >> rgb >> ts >> depth)) {
         xFiles.push_front(rgb);
         xData.push_front(Vec7r(p));
      }
   }

   // load camera parameters
   xDistortion = Matrix(1, 5, &freiburg[xID][4]);
   GenerateK(xID, xIntrinsic);

   loaded = true;
}

inline void GenerateK(size_t id, Matrix& K) {
   real_t& fx = freiburg[id][0], cx = freiburg[id][2];
   real_t& fy = freiburg[id][1], cy = freiburg[id][3];
   K <<  fx, 0, cx,
         0, fy, cy,
         0, 0, 1;
}

inline void ConvertPose(const Vec7r& p, Matrix& T){
   // Camera's position relative to the world
   real_t tx = p[0]; real_t ty = p[1]; real_t tz = p[2];
   // Camera's rotation relative to the world in quaternion form
   real_t qx = p[3]; real_t qy = p[4];
   real_t qz = p[5]; real_t qw = p[6];

   real_t xx = qx*qx, yy = qy*qy, zz = qz*qz;
   real_t xy = qx*qy, yz = qy*qz, zx = qz*qx;
   real_t wx = qw*qx, wy = qw*qy, wz = qw*qz;

   // Matrix form
   T <<  1. -2. * (yy + zz),  2. * (xy - wz),      2. * (zx + wy),      tx,
         2. * (xy + wz),      1. -2. * (xx + zz),  2. * (yz - wx),      ty,
         2. * (zx - wy),      2. * (yz + wx),      1. -2. * (xx + yy),  tz,
         0.,                  0.,                  0.,                  1.;
}

inline bool is_empty(std::ifstream& fs) { return (fs.peek() == std::ifstream::traits_type::eof()); }

inline bool Initialize() {
   static string cmd = "TUMRGBD_PATH=$1;\n"
      "if [ ! -f $TUMRGBD_PATH/sequence.txt ]; then\n"
      "   if [ ! -f ./associate.py ]; then\n"
      "      wget -nv https://www.dropbox.com/s/fm4jwt34pi6r9w6/associate.py?dl=0 -O associate.py;\n"
      "      chmod +x ./associate.py;\n"
      "   fi\n"
      "   ./associate.py $TUMRGBD_PATH/groundtruth.txt $TUMRGBD_PATH/rgb.txt >> ./temp.txt;\n"
      "   ./associate.py ./temp.txt $TUMRGBD_PATH/depth.txt >> $TUMRGBD_PATH/sequence.txt;\n"
      "   rm ./temp.txt;\n"
      "fi";
   std::ifstream checker("./initTUM.sh");
   if(!checker || is_empty(checker)) {
      // script does not exists
      checker.close();

      std::ofstream out("./initTUM.sh");
      if(!out) return false;

      // script created
      out << cmd;
      out.close();
   }

   int x = system("chmod +x ./initTUM.sh");
   return true;
}

} // avr
