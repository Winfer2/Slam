#include <Tracking/Frame.hpp>

namespace avr {

size_t Frame::count = 0;

Frame::Frame(const Image& image, const CameraParameters& params, const Features& feats, const vector<real_t>& factors)
   : xID(count++), xCamParams(params), xFeatures(feats), xScaleFactors(factors) {
   if(image.channels() == 3) {
      image.copyTo(xColorImage);
      cv::cvtColor(image, xGrayImage, CV_BGR2GRAY);
   } else {
      image.copyTo(xGrayImage);
      cv::cvtColor(image, xColorImage, CV_GRAY2BGR);
   }
}

//! Statics
Ptr<Frame> Frame::Build(const Image& image, const Matrix& K, Ptr<FeatureExtractor> pExtractor) {
   CameraParameters parameters(K);

   Features features;
   pExtractor->Extract(image, features);

   return Ptr<Frame>(new Frame(image, parameters, features, pExtractor->GetFactorByLevels()));
}

Ptr<Frame> Frame::Build(const Image& image, real_t fx, real_t fy, real_t cx, real_t cy, Ptr<FeatureExtractor> pExtractor) {
   Matrix K(3, 3);
   K << fx,0.0,cx, 0.0,fy,cy, 0.0,0.0,1.0;
   return Frame::Build(image, K, pExtractor);
}

} // avr
