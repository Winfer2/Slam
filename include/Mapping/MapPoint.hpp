#ifndef AVR_MAPPING_MAPPOINT_HPP
#define AVR_MAPPING_MAPPOINT_HPP

#include <Core/Core.hpp>
#include <Mapping/Map.hpp>

namespace avr {

class Map::MapPoint {
public:
   Vec4r GetWorld() const;
   Vec3b GetColor() const;

   void SetColor(ubyte_t r, ubyte_t g, ubyte_t b);
   void SetColor(const Vec3b& rgb);

   template <typename Tp> void SetWorld(Tp x, Tp y, Tp z);
   template <typename Tp> void SetWorld(const cv::Point3_<Tp>&);
   template <typename Tp> void SetWorld(const cv::Vec<Tp, 3>&);

private:
   template <typename Tp> MapPoint(Tp x, Tp y, Tp z);
   template <typename Tp> MapPoint(const cv::Point3_<Tp>& pw);
   template <typename Tp> MapPoint(const cv::Vec<Tp, 3>& pw);

   void SetSelf(const slist<MapPoint>::iterator&);

private:
   Vec4r xWorld;  // 3D homogeneous world coordinate
   Vec3b xColor;  // RGB color space coordinate

   // save all keyframes that observer this point and the correspondent keypoint index
   std::map<Ptr<KeyFrame>, index_t> xObservations;
   // Reference to itself
   slist<MapPoint>::iterator pSelf;

   friend class Map;
};

} // avr

#include "impl/MapPoint.hh"

#endif // AVR_MAPPING_MAPPOINT_HPP
