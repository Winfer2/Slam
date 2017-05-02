#include <View/MapViewer.hpp>
// Graphic library
#include <pangolin/pangolin.h>

namespace avr {

using pangolin::GLprecision;
using pangolin::OpenGlMatrix;

///////////////////////////////////////// INNER CLASSES ///////////////////////////////////////////

class MapViewer::Toggle : public pangolin::Var<bool> {
public:
   Toggle(const string& name, bool value)
      : pangolin::Var<bool>(name, value, true) {/* ctor */}
};

class MapViewer::CameraState : public pangolin::OpenGlRenderState {
public:
   CameraState()
      : pangolin::OpenGlRenderState() {/* ctor */}
   CameraState(const OpenGlMatrix& projection_matrix)
      : pangolin::OpenGlRenderState(projection_matrix) {/* ctor */}
   CameraState(const OpenGlMatrix& projection_matrix, const OpenGlMatrix& modelview_matrix)
      : pangolin::OpenGlRenderState(projection_matrix, modelview_matrix) {/* ctor */}
};

////////////////////////////////////////// MAP VIEWER /////////////////////////////////////////////

static OpenGlMatrix& Mat2GL(const Matrix& Tcw, OpenGlMatrix& Twc);
static Matrix&       GL2Mat(const OpenGlMatrix& Twc, Matrix& Tcw);

MapViewer::MapViewer(const Ptr<Map>& _map) : Viewer(),
   pMap(_map), pDrawer(new MapDrawer(_map)), xFollow(false), xSleep(true) {/* ctor */}

MapViewer::~MapViewer() {
   this->Stop();
   // wait cleanup execution
   while(xSleep)
      this->Sleep(100);
}

// Starts the API and initialize data
void MapViewer::Initialize() {
   pangolin::CreateWindowAndBind("Map Viewer", 1024, 768);

   // 3D Mouse handler requires depth testing to be enabled
   glEnable(GL_DEPTH_TEST);
   // Issue specific OpenGl we might need
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   // create menu
   pangolin::CreatePanel("menu").SetBounds(0.0,1.0,0.0, pangolin::Attach::Pix(175));
   xMenu["FollowCamera"]   = cv::makePtr<Toggle>("menu.Follow Camera", true);
   xMenu["ShowPoints"]     = cv::makePtr<Toggle>("menu.Show 3D Points", true);
   xMenu["ShowTexture"]    = cv::makePtr<Toggle>("menu.Show Texture", true);
   xMenu["ShowKeyFrames"]  = cv::makePtr<Toggle>("menu.Show KeyFrames", true);
   xMenu["ShowPoseGraph"]  = cv::makePtr<Toggle>("menu.Show Pose Graph", false);

   // Define Camera Render Object (for view / scene browsing)
   xCamera = cv::makePtr<CameraState>(
      pangolin::ProjectionMatrix(1024,768, 500,500, 512,389, 0.1,1000),
      pangolin::ModelViewLookAt(0.0,-0.7,-1.8, 0.0,0.0,0.0, 0.0,-1.0,0.0)
   );

   // Add named OpenGL viewport to window and provide 3D Handler
   pangolin::Display("Map Display")
      .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175), 1.0, -1024.0f/768.0f)
      .SetHandler(new pangolin::Handler3D(*xCamera));
}

// Configure the API for visualization
void MapViewer::Display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // get current camera pose
   Matrix Twc;
   pDrawer->GetCurrentPose(Twc);
   // convert pose to opengl matrix
   OpenGlMatrix GLwc;
   Mat2GL(Twc, GLwc);
   xCamera->Follow(GLwc);

   // configure virtual camera mode
   if((*xMenu["FollowCamera"]) && !xFollow) {
      xCamera->SetModelViewMatrix(pangolin::ModelViewLookAt(0.0,-0.7,-1.8, 0.0,0.0,0.0, 0.0,-1.0,0.0));
      xCamera->Follow(GLwc);
      xFollow = true;
   }
   else if((*xMenu["FollowCamera"]) && xFollow)
      xCamera->Follow(GLwc);
   else if(!(*xMenu["FollowCamera"]) && xFollow)
      xFollow = false;

   // active display to render
   pangolin::Display("Map Display").Activate(*xCamera);
   glClearColor(1.0f,1.0f,1.0f,1.0f);

   // render
   pDrawer->DrawAxis(5.0);
   pDrawer->DrawCurrentCamera();
   if(*xMenu["ShowKeyFrames"])
      pDrawer->DrawTrajectory();
   if(*xMenu["ShowPoints"])
      pDrawer->DrawMapPoints(bool(*xMenu["ShowTexture"]));
   // show
   pangolin::FinishFrame();
}

// Finishes the API and cleanup data
void MapViewer::Cleanup() {
   pangolin::DestroyWindow("Map Viewer");
   xSleep = false;
}

////////////////////////////////////////// STATICS //////////////////////////////////////////

inline OpenGlMatrix& Mat2GL(const Matrix& Twc, OpenGlMatrix& GLwc) {
   GLwc.SetIdentity();

   if(!Twc.empty()) {
      Matrix Rwc(Twc.rowRange(0,3).colRange(0,3));
      Matrix twc(Twc.rowRange(0,3).col(3));

      GLwc.m[0] = GLprecision(Rwc.at<real_t>(0,0));
      GLwc.m[1] = GLprecision(Rwc.at<real_t>(1,0));
      GLwc.m[2] = GLprecision(Rwc.at<real_t>(2,0));

      GLwc.m[4] = GLprecision(Rwc.at<real_t>(0,1));
      GLwc.m[5] = GLprecision(Rwc.at<real_t>(1,1));
      GLwc.m[6] = GLprecision(Rwc.at<real_t>(2,1));

      GLwc.m[8] = GLprecision(Rwc.at<real_t>(0,2));
      GLwc.m[9] = GLprecision(Rwc.at<real_t>(1,2));
      GLwc.m[10] = GLprecision(Rwc.at<real_t>(2,2));

      GLwc.m[12] = GLprecision(twc.at<real_t>(0));
      GLwc.m[13] = GLprecision(twc.at<real_t>(1));
      GLwc.m[14] = GLprecision(twc.at<real_t>(2));
   }

   return GLwc;
}

inline Matrix& GL2Mat(const OpenGlMatrix& GLwc, Matrix& Twc) {
   Twc = MATRIX::Eye(4, 4);

   Twc.at<real_t>(0,0) = real_t(GLwc.m[0]);
   Twc.at<real_t>(1,0) = real_t(GLwc.m[1]);
   Twc.at<real_t>(2,0) = real_t(GLwc.m[2]);

   Twc.at<real_t>(0,1) = real_t(GLwc.m[4]);
   Twc.at<real_t>(1,1) = real_t(GLwc.m[5]);
   Twc.at<real_t>(2,1) = real_t(GLwc.m[6]);

   Twc.at<real_t>(0,2) = real_t(GLwc.m[8]);
   Twc.at<real_t>(1,2) = real_t(GLwc.m[9]);
   Twc.at<real_t>(2,2) = real_t(GLwc.m[10]);

   Twc.at<real_t>(0,3) = real_t(GLwc.m[12]);
   Twc.at<real_t>(1,3) = real_t(GLwc.m[13]);
   Twc.at<real_t>(2,3) = real_t(GLwc.m[14]);

   return Twc;
}


} // avr
