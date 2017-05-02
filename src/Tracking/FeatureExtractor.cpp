#include <Tracking/FeatureExtractor.hpp>

namespace avr {

static const size_t NUM_FEATS    = 5000;
static const size_t NUM_LEVELS   = 4;
static const size_t EDGE_TH      = 20;
static const float  SCALE_F      = 1.5;

FeatureExtractor::FeatureExtractor() {
   pExtractor = cv::ORB::create(NUM_FEATS, NUM_LEVELS, SCALE_F, EDGE_TH);

   xScaleFactors.resize(NUM_LEVELS, 1.0);
   for(size_t i = 1; i < NUM_LEVELS; i++)
      xScaleFactors[i] = SCALE_F * xScaleFactors[i - 1];
}

//! Extract image features
void FeatureExtractor::Extract(const Image& image, Features& features) {
   Image gray;
   if(image.channels() >= 3)
      cv::cvtColor(image, gray, CV_BGR2GRAY);
   else gray = image;

   pExtractor->detectAndCompute(gray, cv::noArray(), features.xKeyPoints, features.xDescriptors);
   {
      size_t wCell = size_t(image.cols/64.0);
      size_t hCell = size_t(image.rows/48.0);
      features.xImageGrid = Grid<index_t, 48, 64>(wCell, hCell);
   }

   for(size_t i = 0, imax = features.size(); i < imax; i++) {
      KeyPoint kp = features.GetKeyPoint(i);
      features.xImageGrid(kp.pt) = index_t(i);
   }
}

} // avr
