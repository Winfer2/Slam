#ifndef AVR_TRACKING_FEATURE_EXTRACTOR_HPP
#define AVR_TRACKING_FEATURE_EXTRACTOR_HPP

#include <Core/Core.hpp>
#include <Tracking/Features.hpp>

namespace avr {

class FeatureExtractor {
public:
   FeatureExtractor();

   //! Extract image features
   void Extract(const Image&, Features&);

   size_t GetLevelsNumber() const;
   size_t GetFeaturesThreshold() const;

   real_t GetScaleFactor() const;
   real_t GetLevelFactor(index_t lvl) const;
   const vector<real_t>& GetFactorByLevels() const;

private:
   Ptr<cv::ORB> pExtractor;
   vector<real_t> xScaleFactors;
};

} // avr

#include "impl/FeatureExtractor.hh"

#endif // AVR_TRACKING_FEATURE_EXTRACTOR_HPP
