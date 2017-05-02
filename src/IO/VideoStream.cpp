#include <IO/VideoStream.hpp>

namespace avr {

VideoStream::VideoStream() : ImageStream(), xFrameCounter(0), xFramesNumber(0) {/* ctor */}

void VideoStream::NextFrame(Image& frame) {
   xCap >> frame;
   xFrameCounter++;
}

void VideoStream::LoadStream(const string& config, bool& loaded) {
   // TODO: Criar um parse
   size_t pos = config.find("-dev=");
   if(pos != string::npos) {
      int dev = atoi(config.substr(pos+5, 1).c_str());
      xCap = cv::VideoCapture(dev);
      xFramesNumber = std::numeric_limits<size_t>::max();
   } else {
      const string& filename = config;
      xCap = cv::VideoCapture(filename);
      xFramesNumber = (size_t) xCap.get(cv::CAP_PROP_FRAME_COUNT);
   }
   loaded = xCap.isOpened();
}

} // avr
