#ifndef AVR_TRACKING_FEATURES_HPP
#define AVR_TRACKING_FEATURES_HPP

#include <Core/Grid.hpp>

namespace avr {

class Features {
public:
   Features();
   Features(const Features&);

   Mat GetDescriptor(index_t i) const;
   KeyPoint GetKeyPoint(index_t i) const;

   Cell<index_t> GetCell(index_t r, index_t c) const;
   Cell<index_t> GetNeighborsOf(const Point2r&) const;

   size_t size() const { return xDescriptors.rows; }
   bool empty() const { return xDescriptors.empty(); }

   Features& operator = (const Features&);

private:
   Mat xDescriptors;
   vector<KeyPoint> xKeyPoints;
   Grid<index_t, 48, 64> xImageGrid;

   friend class FeatureExtractor;
   friend class FeatureMatcher;
};

} // avr

#include "impl/Features.hh"

#endif // AVR_TRACKING_FEATURES_HPP
