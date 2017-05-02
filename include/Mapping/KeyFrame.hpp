#ifndef AVR_MAPPING_KEYFRAME_HPP
#define AVR_MAPPING_KEYFRAME_HPP

#include <Core/Grid.hpp>
#include <Mapping/Map.hpp>

namespace avr {

class Map::KeyFrame {
public:
   const size_t xID;

   Features& GetFeatures();
   const Features& GetFeatures() const;

   CameraParameters& GetParameters();
   const CameraParameters& GetParameters() const;

private:
   // construct keyframe given frame
   KeyFrame(const Frame&);
   // set reference to itself in map
   void SetSelf(const slist<KeyFrame>::iterator&);

private:
   Features xFeatures;
   CameraParameters xCamParams;

   svector<MapPoint> xObservations;
   sset<KeyFrame> xNeighbors;

   // reference to itself in map
   slist<KeyFrame>::iterator pSelf;

   friend class Map;
};

} // avr

#include "impl/KeyFrame.hh"

#endif // AVR_MAPPING_KEYFRAME_HPP
