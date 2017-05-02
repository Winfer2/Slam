#ifdef AVR_MAPPING_MAP_HPP

#include <Mapping/MapPoint.hpp>
#include <Mapping/KeyFrame.hpp>

//! Map short methods implementation !//

namespace avr {

using std::unique_lock;
using std::mutex;

inline Map::Map() : xUpdated(false) {
   /* ctor */
}

inline Map::~Map() {
   /* dtor */
}

//! lists iteration (for-each)
inline void Map::Iterate(const function<void(const MapPoint&)>& func) const {
   xPointCloudMutex.lock();
      slist<MapPoint>::const_iterator _begin = xPointCloud.begin();
      slist<MapPoint>::const_iterator _end = xPointCloud.end();
   xPointCloudMutex.unlock();

   for(auto it = _begin; it != _end; it++)
      func(*(*it));
}
inline void Map::Iterate(const function<void(const KeyFrame&)>& func) const {
   xKeyFramesMutex.lock();
      slist<KeyFrame>::const_iterator _begin = xKeyFrames.begin();
      slist<KeyFrame>::const_iterator _end = xKeyFrames.end();
   xKeyFramesMutex.unlock();

   for(auto it = _begin; it != _end; it++)
      func(*(*it));
}

//! Builds in-place a new map point and add it to map
inline Ptr<MapPoint> Map::Emplace(const Vec3r& vw) {
   Ptr<MapPoint> P3D = Ptr<MapPoint>(new MapPoint(vw));
   {
      unique_lock<mutex> lock(xRecentPointsMutex);
      xRecentPoints.push_back(P3D);
   }
   return P3D;
}
inline Ptr<MapPoint> Map::Emplace(const Point3r& pw) {
   Ptr<MapPoint> P3D = Ptr<MapPoint>(new MapPoint(pw));
   {
      unique_lock<mutex> lock(xRecentPointsMutex);
      xRecentPoints.push_back(P3D);
   }
   return P3D;
}
inline Ptr<MapPoint> Map::Emplace(real_t x, real_t y, real_t z) {
   Ptr<MapPoint> P3D = Ptr<MapPoint>(new MapPoint(x, y, z));
   {
      unique_lock<mutex> lock(xRecentPointsMutex);
      xRecentPoints.push_back(P3D);
   }
   return P3D;
}

//! Builds in-place a new keyframe and add it to map
inline Ptr<KeyFrame> Map::Emplace(const Frame& Fc) {
   Ptr<KeyFrame> KFc = Ptr<KeyFrame>(new KeyFrame(Fc));
   {
      unique_lock<mutex> lock(xRecentFramesMutex);
      xRecentFrames.push_back(KFc);
   }
   return KFc;
}

//! Check if map was updated since last check
inline bool Map::Updated() const {
   bool res = xUpdated;
   xUpdated = false;
   return res;
}

//! Makes a link between 3D point and keyframe that observes it
inline bool Map::RegisterObservation(const Ptr<MapPoint>& P3D, const Ptr<KeyFrame>& KFc, index_t idx) {
   assert(!P3D.empty() && !KFc.empty());

   if(idx < KFc->xObservations.size() && KFc->xObservations[idx].empty()) {
      auto res = P3D->xObservations.insert(std::make_pair(KFc, idx));
      if(res.second) {
         KFc->xObservations[idx] = P3D;
         return true;
      }
   } return false;
}

} // avr

#endif // AVR_MAPPING_MAP_HPP
