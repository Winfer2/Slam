#ifdef AVR_TRACKING_FEATURES_HPP

namespace avr {

inline Features::Features() {/* ctor */}

inline Features::Features(const Features& feats) {
   xImageGrid = feats.xImageGrid;
   feats.xDescriptors.copyTo(xDescriptors);
   xKeyPoints.assign(feats.xKeyPoints.begin(), feats.xKeyPoints.end());
}

inline Mat Features::GetDescriptor(index_t i) const {
   assert(i < size());
   return xDescriptors.row(i);
}
inline KeyPoint Features::GetKeyPoint(index_t i) const {
   assert(i < size());
   return xKeyPoints.at(i);
}

inline Cell<index_t> Features::GetCell(index_t r, index_t c) const {
   assert(r < xImageGrid.nRows && c < xImageGrid.nCols);
   return xImageGrid(r, c);
}
inline Cell<index_t> Features::GetNeighborsOf(const Point2r& pt) const {
   try {
      return xImageGrid(pt);
   } catch(const std::out_of_range&) {
      return Cell<index_t>();
   }
}

inline Features& Features::operator = (const Features& feats) {
   xImageGrid = feats.xImageGrid;
   feats.xDescriptors.copyTo(xDescriptors);
   xKeyPoints.assign(feats.xKeyPoints.begin(), feats.xKeyPoints.end());
   return * this;
}

} // avr

#endif // AVR_TRACKING_FEATURES_HPP
