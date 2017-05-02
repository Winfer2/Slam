#ifdef AVR_TRACKING_FEATURE_EXTRACTOR_HPP

namespace avr {

inline size_t FeatureExtractor::GetLevelsNumber() const {
   return pExtractor->getNLevels();
}
inline size_t FeatureExtractor::GetFeaturesThreshold() const {
   return pExtractor->getMaxFeatures();
}

inline real_t FeatureExtractor::GetScaleFactor() const {
   return real_t(pExtractor->getScaleFactor());
}
inline real_t FeatureExtractor::GetLevelFactor(index_t lvl) const {
   if(lvl < GetLevelsNumber())
      return xScaleFactors[lvl];
   return 0.0;
}
inline const vector<real_t>& FeatureExtractor::GetFactorByLevels() const {
   return xScaleFactors;
}

} // avr

#endif // AVR_TRACKING_FEATURE_EXTRACTOR_HPP
