#ifndef AVR_VIEW_MAPVIEWER_HPP
#define AVR_VIEW_MAPVIEWER_HPP

#include <View/Viewer.hpp>
#include <View/MapDrawer.hpp>
#include <Mapping/Map.hpp>

namespace avr {

class MapViewer : public Viewer {
public:
   MapViewer(const Ptr<Map>&);
   ~MapViewer();

   const Ptr<MapDrawer>& GetDrawer() const { return pDrawer; }

private:
   // Starts the API and initialize data
   void Initialize();
   // Configure the API for visualization
   void Display();
   // Finishes the API and cleanup data
   void Cleanup();

private:
   Ptr<Map> pMap;
   Ptr<MapDrawer> pDrawer;

   abool_t xFollow;
   abool_t xSleep;

   // inner classes
   class Toggle;
   class CameraState;

   // lateral menu options
   std::map<string, Ptr<Toggle>> xMenu;
   // virtual camera state
   Ptr<CameraState> xCamera;
};

} // avr

#endif // AVR_VIEW_MAPVIEWER_HPP
