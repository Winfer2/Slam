#include <IO/TUMDatasetStream.hpp>

#include <Core/Grid.hpp>
#include <Core/CameraParameters.hpp>

#include <Tracking/Frame.hpp>
#include <Tracking/FeatureExtractor.hpp>

#include <Mapping/Map.hpp>

#include <View/MapViewer.hpp>

#include <stdlib.h>
#include <time.h>

#define DATAPATH  "/home/rodrigocoelho/Desktop/TUM/"

using std::cout;
using std::cerr;
using std::endl;

using namespace avr;

int main(int argc, char *argv[])
{
   TUMDatasetStream cap;
   if(!cap(DATAPATH"freiburg3_long_office")) {
      cerr << "Sequence not found\n";
      return 1;
   }

   Ptr<Map> pMap = cv::makePtr<Map>();
   Ptr<MapViewer> pViewer = cv::makePtr<MapViewer>(pMap);

   Ptr<FeatureExtractor> pExtractor = cv::makePtr<FeatureExtractor>();

   const size_t R = 1;
   const real_t PI = 4.0 * std::atan(1);
   const real_t TO_RAD = PI / 180.0;

   srand(time(0));
   char key;

   pViewer->Start();

   do {
      Image image; cap >> image;

      Ptr<Frame> pFrame = Frame::Build(image, cap.GetIntrinsics(), pExtractor);
      // update pose
      pFrame->GetParameters().SetPose(cap.GetGroundTruth());
      pViewer->GetDrawer()->SetCurrentPose(cap.GetGroundTruth());

      // add frame to map
      pMap->Emplace(*pFrame);
      // add random points in map
      for(size_t i = 0, imax = rand() % 80 + 20; i < imax; i++) {
         real_t theta = real_t(rand() % 360) * TO_RAD;
         real_t phi = real_t(rand() % 180 - 90) * TO_RAD;

         real_t x = R * std::cos(theta) * std::sin(phi);
         real_t y = R * std::sin(theta) * std::sin(phi);
         real_t z = R * std::cos(phi);

         pMap->Emplace(x, y, z);
      }
      // promote points and frame
      pMap->Update();

      cv::imshow("Video", image);
      key = cv::waitKey(0);

   } while(key != 27);

   pViewer->Stop();

   return 0;
}
