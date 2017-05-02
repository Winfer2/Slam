#ifndef AVR_MAPPING_MAP_HPP
#define AVR_MAPPING_MAP_HPP

#include <Core/Core.hpp>
#include <Tracking/Frame.hpp>

namespace avr {

class Map {
public:
   // inner classes
   class MapPoint;
   class KeyFrame;

public:
   Map();
   ~Map();

   //! lists iteration (for-each)
   void Iterate(const function<void(const MapPoint&)>&) const;
   void Iterate(const function<void(const KeyFrame&)>&) const;

   //! Builds in-place a new map point and add it to map
   Ptr<MapPoint> Emplace(const Vec3r&);
   Ptr<MapPoint> Emplace(const Point3r&);
   Ptr<MapPoint> Emplace(real_t x, real_t y, real_t z);

   //! Builds in-place a new keyframe and add it to map
   Ptr<KeyFrame> Emplace(const Frame&);

   //! Makes a link between 3D point and keyframe that observes it
   //! @param idx Correspondent keypoint index
   //! @return true if the link was done
   bool RegisterObservation(const Ptr<MapPoint>&, const Ptr<KeyFrame>&, index_t idx);

   //! Project current map points in given frame
   //! @return vector of 2D projected points
   vector<Point2r> Project(const Frame& frame) const;

   //! Check if map was updated since last check
   bool Updated() const;

public:
   //! Promotes recent points and keyframes
   void Update();

private:
   slist<MapPoint> xPointCloud;
   slist<KeyFrame> xKeyFrames;

   sdeque<MapPoint> xRecentPoints;
   sdeque<KeyFrame> xRecentFrames;

   mutable abool_t xUpdated;

   mutable std::mutex xPointCloudMutex;
   mutable std::mutex xKeyFramesMutex;
   mutable std::mutex xRecentPointsMutex;
   mutable std::mutex xRecentFramesMutex;

   friend class Mapping;
};

typedef Map::MapPoint MapPoint;
typedef Map::KeyFrame KeyFrame;

} // avr

#include "impl/Map.hh"

#endif // AVR_MAPPING_MAP_HPP
