#ifndef AVR_VIEW_VIEWER_HPP
#define AVR_VIEW_VIEWER_HPP

#include <Core/Core.hpp>

namespace avr {

class Viewer : public Parallelable {
public:
   Viewer();
   virtual ~Viewer();

   using Parallelable::Start;
   using Parallelable::Pause;
   using Parallelable::Stop;

protected:
   // Starts the API and initialize data
   virtual void Initialize() = 0;
   // Configure the API for visualization
   virtual void Display() = 0;
   // Finishes the API and cleanup data
   virtual void Cleanup() = 0;

private:
   // State machine implementation
   void Run();

   // Process execution
   inline void Process() {
      this->Display();
   }

   Ptr<Thread> pThread;
};

} // avr

#endif // AVR_VIEW_VIEWER_HPP
