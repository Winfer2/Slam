#ifndef AVR_IO_TUM_DATASET_STREAM_HPP
#define AVR_IO_TUM_DATASET_STREAM_HPP

#include <IO/ImageStream.hpp>

namespace avr {

class TUMDatasetStream : public ImageStream {
public:
   TUMDatasetStream();

   //! @return ground-truth camera pose matrix
   Matrix GetGroundTruth() const {
      return xCurrentGT;
   }

   //! @return camera intrinsic parameters matrix
   Matrix GetIntrinsics() const {
      return xIntrinsic;
   }

   //! @return camera lens distortion coefficients
   Matrix GetDistortion() const {
      return xDistortion;
   }

private:
   inline bool hasNext() const {
      return !xFiles.empty();
   }
   void NextFrame(Image&);
   void LoadStream(const string&, bool&);

private:
   index_t xID;
   string xPath;
   deque<string> xFiles;
   deque<Vec7r> xData;

   Matrix xCurrentGT;
   Matrix xIntrinsic;
   Matrix xDistortion;
};

} // avr

#endif // AVR_IO_TUM_DATASET_STREAM_HPP
