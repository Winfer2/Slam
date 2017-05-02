#ifdef AVR_CORE_CAMERA_PARAMETERS_HPP

namespace avr {

inline CameraParameters::CameraParameters()
   : K(MATRIX::Eye(3, 3)), Tcw(MATRIX::Eye(4, 4)), Twc(MATRIX::Eye(4, 4)) {/* ctor */}
inline CameraParameters::CameraParameters(const Matrix& _K)
   : K(_K), Tcw(MATRIX::Eye(4, 4)), Twc(MATRIX::Eye(4, 4)) {/* ctor */}
inline CameraParameters::CameraParameters(real_t fx, real_t fy, real_t cx, real_t cy, real_t skew)
   : K(MATRIX::Eye(3, 3)), Tcw(MATRIX::Eye(4, 4)), Twc(MATRIX::Eye(4, 4)) { this->Set(fx, fy, cx, cy, skew); }


inline Matrix CameraParameters::GetPose() const {
   return Twc;
}
inline Matrix CameraParameters::GetRotation() const {
   return Twc.rowRange(0, 3).colRange(0, 3);
}
inline Matrix CameraParameters::GetTranslation() const {
   return Twc.rowRange(0, 3).col(3);
}
inline Matrix CameraParameters::GetOpticalCenter() const {
   return this->GetTranslation();
}


inline Matrix CameraParameters::GetPoseInv() const {
   return Tcw;
}
inline Matrix CameraParameters::GetRotationInv() const {
   return Tcw.rowRange(0, 3).colRange(0, 3);
}
inline Matrix CameraParameters::GetTranslationInv() const {
   return Tcw.rowRange(0, 3).col(3);
}


inline Matrix CameraParameters::GetIntrinsics() const {
   return K;
}
inline Matrix CameraParameters::GetProjection() const {
   return K * Tcw.rowRange(0, 3);
}


inline void CameraParameters::Get(real_t& fx, real_t& fy, real_t& cx, real_t& cy) {
   fx = K.at<real_t>(0, 0);
   fy = K.at<real_t>(1, 1);
   cx = K.at<real_t>(0, 2);
   cy = K.at<real_t>(1, 2);
}
inline void CameraParameters::Get(real_t& fx, real_t& fy, real_t& cx, real_t& cy, real_t& skew) {
   fx = K.at<real_t>(0, 0);
   fy = K.at<real_t>(1, 1);
   cx = K.at<real_t>(0, 2);
   cy = K.at<real_t>(1, 2);
   skew = K.at<real_t>(0, 1);
}


inline CameraParameters& CameraParameters::SetPose(const Matrix& _Twc) {
   assert(_Twc.size() == cv::Size(4, 4));
   // copy matrix
   _Twc.copyTo(Twc);
   this->UpdateInverse();
   return * this;
}
inline CameraParameters& CameraParameters::SetRotation(const Matrix& _Rwc) {
   assert(_Rwc.size() == cv::Size(3, 3));
   // copy matrix
   _Rwc.copyTo(Twc.rowRange(0, 3).colRange(0, 3));
   this->UpdateInverse();
   return * this;

}
inline CameraParameters& CameraParameters::SetTranslation(const Matrix& _twc) {
   assert(_twc.size() == cv::Size(1, 3) || _twc.size() == cv::Size(3, 1));
   Matrix twc = (_twc.cols == 3) ? _twc.t() : _twc;
   // copy matrix
   twc.copyTo(Twc.rowRange(0, 3).col(3));
   this->UpdateInverse();
   return * this;
}


inline CameraParameters& CameraParameters::SetPoseInv(const Matrix& _Tcw) {
   assert(_Tcw.size() == cv::Size(4, 4));
   // copy matrix
   _Tcw.copyTo(Tcw);
   this->UpdateMatrix();
   return * this;
}
inline CameraParameters& CameraParameters::SetRotationInv(const Matrix& _Rcw) {
   assert(_Rcw.size() == cv::Size(3, 3));
   // copy matrix
   _Rcw.copyTo(Tcw.rowRange(0, 3).colRange(0, 3));
   this->UpdateMatrix();
   return * this;
}
inline CameraParameters& CameraParameters::SetTranslationInv(const Matrix& _tcw) {
   assert(_tcw.size() == cv::Size(1, 3) || _tcw.size() == cv::Size(3, 1));
   Matrix tcw = (_tcw.cols == 3) ? _tcw.t() : _tcw;
   // copy matrix
   tcw.copyTo(Tcw.rowRange(0, 3).col(3));
   this->UpdateMatrix();
   return * this;
}


inline CameraParameters& CameraParameters::Set(real_t fx, real_t fy, real_t cx, real_t cy, real_t skew) {
   K.at<real_t>(0, 0) = fx;
   K.at<real_t>(1, 1) = fy;
   K.at<real_t>(0, 2) = cx;
   K.at<real_t>(1, 2) = cy;
   K.at<real_t>(0, 1) = skew;
   return * this;
}


inline void CameraParameters::UpdateMatrix() {
   // update rotation inverse
   Matrix Rwc = GetRotationInv().t();
   Rwc.copyTo(Twc.rowRange(0, 3).colRange(0, 3));
   // update translation inverse
   Matrix twc = -Rwc * GetTranslationInv();
   twc.copyTo(Twc.rowRange(0, 3).col(3));
}

inline void CameraParameters::UpdateInverse() {
   // update rotation inverse
   Matrix Rcw = GetRotation().t();
   Rcw.copyTo(Tcw.rowRange(0, 3).colRange(0, 3));
   // update translation inverse
   Matrix tcw = -Rcw * GetTranslation();
   tcw.copyTo(Tcw.rowRange(0, 3).col(3));
}

} // avr

#endif // AVR_CORE_CAMERA_PARAMETERS_HPP
