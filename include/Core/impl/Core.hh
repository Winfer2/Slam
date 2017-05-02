#ifdef AVR_CORE_SLAM_HPP

//! Core short functions and methods implementation !//

namespace avr {

inline Image IMAGE::Parallax(const Image& P, const Image& Q) {
   Image Gp, Bp;
   cv::extractChannel(P, Gp, 1);
   cv::extractChannel(P, Bp, 0);

   Image Rq, Gq, Bq;
   cv::extractChannel(Q, Rq, 2);
   cv::extractChannel(Q, Gq, 1);
   cv::extractChannel(Q, Bq, 0);

   Image B, G;
   cv::addWeighted(Bp, 0.5, Bq, 0.5, 0.0, B);
   cv::addWeighted(Gp, 0.5, Gq, 0.5, 0.0, G);

   std::vector<Image> images(3);
   images[0] = B; images[1] = G; images[2] = Rq;

   Image view;
   cv::merge(images, view);
   return view;
}

//////////////////////////////////////////// Parallelable ////////////////////////////////////////////

inline Parallelable::Parallelable() : xState(ST::WAITING), xStartRequired(false), xPauseRequired(false), xStopRequired(false) {
   /* ctor */
}
inline Parallelable::~Parallelable() {
   /* dtor */
}

// Thread run control
inline void Parallelable::Start() { if(isWaiting()) xStartRequired = true; }
inline void Parallelable::Pause() { if(isRunning()) xPauseRequired = true; }
inline void Parallelable::Stop()  { if(isWaiting() || isRunning()) xStopRequired = true; }

// Thread state check
inline bool Parallelable::isWaiting() const { return xState == ST::WAITING; }
inline bool Parallelable::isRunning() const { return xState == ST::RUNNING; }
inline bool Parallelable::isStopped() const { return xState == ST::STOPPED; }

// Thread sleep
inline void Parallelable::Sleep(size_t ms) const {
   std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

// State machine
inline void Parallelable::Run() {
   while(!xStartRequired && !xStopRequired)
      Sleep(1000);

   if(xStartRequired) {
      xState = ST::RUNNING;
      xStartRequired = false;
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

   xState = ST::STOPPED;
   xStopRequired = false;
}
} // avr

#endif // AVR_CORE_SLAM_HPP
