#ifdef AVR_TRACKING_FRAME_HPP

namespace avr {

template <typename Tp> inline Vec3b Frame::Pix(Tp x, Tp y) {
   index_t r(y + Tp(0.5)), c(x + Tp(0.5));
   assert(r < xColorImage.rows && c < xColorImage.cols);
   return xColorImage.at<Vec3b>(r, c);
}

template <typename Tp> inline Vec3b Frame::Pix(cv::Point_<Tp>& px) {
   index_t r(px.y + Tp(0.5)), c(px.x + Tp(0.5));
   assert(r < xColorImage.rows && c < xColorImage.cols);
   return xColorImage.at<Vec3b>(r, c);
}

inline Image Frame::GetColorImage() const {
   return xColorImage;
}

inline Image Frame::GetGrayImage() const {
   return xGrayImage;
}

inline Features& Frame::GetFeatures() {
   return xFeatures;
}

inline const Features& Frame::GetFeatures() const {
   return xFeatures;
}

inline CameraParameters& Frame::GetParameters() {
   return xCamParams;
}

inline const CameraParameters& Frame::GetParameters() const {
   return xCamParams;
}

} // avr

#endif // AVR_TRACKING_FRAME_HPP
