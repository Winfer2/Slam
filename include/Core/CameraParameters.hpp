#ifndef AVR_CORE_CAMERA_PARAMETERS_HPP
#define AVR_CORE_CAMERA_PARAMETERS_HPP

#include <Core/Core.hpp>

namespace avr {

class CameraParameters {
public:
   CameraParameters();
   CameraParameters(const Matrix& K);
   CameraParameters(real_t fx, real_t fy, real_t cx, real_t cy, real_t skew = 0.0);

   // camera pose matrix
   Matrix GetPose() const;
   Matrix GetRotation() const;
   Matrix GetTranslation() const;
   Matrix GetOpticalCenter() const;

   // camera extrinsic parameters
   Matrix GetPoseInv() const;
   Matrix GetRotationInv() const;
   Matrix GetTranslationInv() const;

   // camera intrinsic parameters
   Matrix GetIntrinsics() const;
   void Get(real_t& fx, real_t& fy, real_t& cx, real_t& cy);
   void Get(real_t& fx, real_t& fy, real_t& cx, real_t& cy, real_t& skew);

   // camera projection matrix (K[R|t])
   Matrix GetProjection() const;

   // camera pose matrix
   CameraParameters& SetPose(const Matrix& Twc);
   CameraParameters& SetRotation(const Matrix& Rwc);
   CameraParameters& SetTranslation(const Matrix& twc);

   // camera extrinsic parameters
   CameraParameters& SetPoseInv(const Matrix& Tcw);
   CameraParameters& SetRotationInv(const Matrix& Rcw);
   CameraParameters& SetTranslationInv(const Matrix& tcw);

   // camera intrinsic parameters
   CameraParameters& Set(real_t fx, real_t fy, real_t cx, real_t cy, real_t skew = 0.0);

private:
   Matrix K;   //< intrinsic parameters
   Matrix Tcw; //< extrinsic parameters
   Matrix Twc; //< camera pose inv(Tcw)

private:
   void UpdateMatrix();
   void UpdateInverse();
};

} // avr

// short implementation
#include "impl/CameraParameters.hh"

#endif // AVR_CORE_CAMERA_PARAMETERS_HPP
