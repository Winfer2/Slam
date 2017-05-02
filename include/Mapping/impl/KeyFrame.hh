#ifdef AVR_MAPPING_KEYFRAME_HPP

//! KeyFrame short methods implementation !//

namespace avr {

inline KeyFrame::KeyFrame(const Frame& frame) : xID(frame.xID), xCamParams(frame.GetParameters()), xFeatures(frame.GetFeatures()) {
   xObservations.resize(xFeatures.size());
}

inline Features& KeyFrame::GetFeatures() {
   return xFeatures;
}

inline const Features& KeyFrame::GetFeatures() const {
   return xFeatures;
}

inline CameraParameters& KeyFrame::GetParameters() {
   return xCamParams;
}

inline const CameraParameters& KeyFrame::GetParameters() const {
   return xCamParams;
}

inline void KeyFrame::SetSelf(const slist<KeyFrame>::iterator& self) {
   pSelf = self;
}

} // avr

#endif // AVR_MAPPING_KEYFRAME_HPP
