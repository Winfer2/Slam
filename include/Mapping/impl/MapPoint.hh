#ifdef AVR_MAPPING_MAPPOINT_HPP

//! MapPoint short methods implemention !//

namespace avr {

template <typename Tp> inline MapPoint::MapPoint(Tp x, Tp y, Tp z)
   : xWorld(real_t(x), real_t(y), real_t(z), 1.0) {/* ctor */}
template <typename Tp> inline MapPoint::MapPoint(const cv::Point3_<Tp>& pw)
   : xWorld(real_t(pw.x), real_t(pw.y), real_t(pw.z), 1.0) {/* ctor */}
template <typename Tp> inline MapPoint::MapPoint(const cv::Vec<Tp, 3>& vw)
   : xWorld(real_t(vw(0)), real_t(vw(1)), real_t(vw(2)), 1.0) {/* ctor */}

inline Vec4r MapPoint::GetWorld() const {
   return xWorld;
}
inline Vec3b MapPoint::GetColor() const {
   return xColor;
}

inline void MapPoint::SetColor(ubyte_t r, ubyte_t g, ubyte_t b) {
   xColor = Vec3b(r, g, b);
}
inline void MapPoint::SetColor(const Vec3b& rgb) {
   xColor = rgb;
}
template <typename Tp> inline void MapPoint::SetWorld(Tp x, Tp y, Tp z) {
   xWorld = Vec4r(real_t(x), real_t(y), real_t(z), 1.0);
}
template <typename Tp> inline void MapPoint::SetWorld(const cv::Point3_<Tp>& pw) {
   xWorld = Vec4r(real_t(pw.x), real_t(pw.y), real_t(pw.z), 1.0);
}
template <typename Tp> inline void MapPoint::SetWorld(const cv::Vec<Tp, 3>& vw) {
   xWorld = Vec4r(real_t(vw(0)), real_t(vw(1)), real_t(vw(2)), 1.0);
}

inline void MapPoint::SetSelf(const slist<MapPoint>::iterator& self) {
   pSelf = self;
}

} // avr

#endif // AVR_MAPPING_MAPPOINT_HPP
