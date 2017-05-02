#include <Mapping/Map.hpp>

namespace avr {

vector<Point2r> Map::Project(const Frame& frame) const {
   // Projection matrix, transforms world coordinates to clip space coordinates
   Matx34r Pcw(frame.GetParameters().GetProjection().ptr<real_t>(0));

   real_t minx, maxx, miny, maxy;
   {
      cv::Size lim = frame.size();
      minx = 0;         miny = 0;
      maxx = lim.width; maxy = lim.height;
   }

   // copy current points in map
   svector<MapPoint> pointCloud;
   {  // points in final list
      unique_lock<mutex> lock(xPointCloudMutex);
      pointCloud.insert(pointCloud.end(), xPointCloud.begin(), xPointCloud.end());
   }
   {  // recent points
      unique_lock<mutex> lock(xRecentPointsMutex);
      pointCloud.insert(pointCloud.end(), xRecentPoints.begin(), xRecentPoints.end());
   }

   vector<Point2r> points;
   for(const Ptr<MapPoint>& P3D : pointCloud) {
      Vec3r p = Pcw * P3D->GetWorld();
      Point2r px(p(0)/p(2), p(1)/(2));
      // clip
      if((minx < px.x && px.x < maxx) && (miny < px.y && px.y < maxy))
         points.push_back(px);
   }

   return points;
}

void Map::Update() {
   // first, insert new map points
   for(size_t k = 0, kmax = xRecentPoints.size(); k < kmax; k++) {
      xRecentPointsMutex.lock();
         Ptr<MapPoint> P3D = xRecentPoints.front();
         xRecentPoints.pop_front();
      xRecentPointsMutex.unlock();
      // if valid point then insert to list
      if(!P3D.empty()) {
         xPointCloudMutex.lock();
            auto it = xPointCloud.insert(xPointCloud.end(), P3D);
         xPointCloudMutex.unlock();
         P3D->SetSelf(it);
      }
   }

   // then, insert new keyframes
   for(size_t k = 0, kmax = xRecentFrames.size(); k < kmax; k++) {
      xRecentFramesMutex.lock();
         Ptr<KeyFrame> KFc = xRecentFrames.front();
         xRecentFrames.pop_front();
      xRecentFramesMutex.unlock();
      // if valid keyframe then insert to list
      if(!KFc.empty()) {
         xKeyFramesMutex.lock();
            auto it = xKeyFrames.insert(xKeyFrames.end(), KFc);
         xKeyFramesMutex.unlock();
         KFc->SetSelf(it);
      }
   }

   xUpdated = true;
}

} // avr
