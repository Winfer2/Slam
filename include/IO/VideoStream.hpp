#ifndef AVR_IO_VIDEO_STREAM_HPP
#define AVR_IO_VIDEO_STREAM_HPP

#include <IO/ImageStream.hpp>
#include <opencv2/videoio.hpp>

namespace avr {

class VideoStream : public ImageStream {
public:
   VideoStream();

private:
   inline bool hasNext() const {
      return (xFrameCounter < xFramesNumber);
   }
   void NextFrame(Image&);
   void LoadStream(const string&, bool&);

private:
   cv::VideoCapture xCap;
   size_t xFrameCounter, xFramesNumber;
};

} // avr

#endif // AVR_IO_VIDEO_STREAM_HPP
