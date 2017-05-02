#include <View/Viewer.hpp>

namespace avr {

Viewer::Viewer() : Parallelable() {
   pThread = cv::makePtr<std::thread>(&Viewer::Run, this);
}

Viewer::~Viewer() {
   if(pThread->joinable()) {
      if(!isStopped())
         this->Stop();
      pThread->join();
   }
}

// State machine
void Viewer::Run() {
   while(!xStartRequired && !xStopRequired)
      Sleep(1000);

   if(xStartRequired) {
      xState = ST::RUNNING;
      xStartRequired = false;
      this->Initialize();
   }

   while(!xStopRequired) {
      this->Process();

      if(xPauseRequired) {
         xState = ST::WAITING;
         xPauseRequired = false;

         while(!xStartRequired && !xStopRequired)
            Sleep(100);

         if(xStartRequired) {
            xState = ST::RUNNING;
            xStartRequired = false;
         }
      }
   }

   this->Cleanup();
   xState = ST::STOPPED;
   xStopRequired = false;
}

} // avr
