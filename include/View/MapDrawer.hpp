#ifndef AVR_MAP_DRAWER_HPP
#define AVR_MAP_DRAWER_HPP

#include <Core/Core.hpp>
#include <Mapping/Map.hpp>

namespace avr {

class Map;

class MapDrawer {
public:
   MapDrawer(const cv::Ptr<Map>&);

   void DrawAxis(float length = 1.0f) const;
   void DrawMapPoints(bool textured = true) const;
   void DrawTrajectory(bool showGraph = false) const;
   void DrawCurrentCamera() const;

   void SetCurrentPose(const Matrix& Twc);
   void GetCurrentPose(Matrix& Twc) const;

private:
   cv::Ptr<Map> pMap;
   Matrix xCameraPose; // Twc

   mutable std::mutex xPoseMutex;
};

} // avr

#endif // AVR_MAP_DRAWER_HPP
