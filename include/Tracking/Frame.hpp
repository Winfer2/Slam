#ifndef AVR_TRACKING_FRAME_HPP
#define AVR_TRACKING_FRAME_HPP

#include <Core/CameraParameters.hpp>
#include <Tracking/FeatureExtractor.hpp>

namespace avr {

class Frame {
public:
   const size_t xID;

   static Ptr<Frame> Build(const Image&, const Matrix& K, Ptr<FeatureExtractor> = Ptr<FeatureExtractor>());
   static Ptr<Frame> Build(const Image&, real_t fx, real_t fy, real_t cx, real_t cy, Ptr<FeatureExtractor> = Ptr<FeatureExtractor>());

   template <typename Tp> Vec3b Pix(Tp x, Tp y);
   template <typename Tp> Vec3b Pix(cv::Point_<Tp>&);

   Image GetColorImage() const;
   Image GetGrayImage() const;

   Features& GetFeatures();
   const Features& GetFeatures() const;

   CameraParameters& GetParameters();
   const CameraParameters& GetParameters() const;

   cv::Size size() const { return xColorImage.size(); }
   bool empty() const { return xColorImage.empty(); }

   Frame(const Frame&) = delete;
   Frame& operator= (const Frame&) = delete;

private:
   Frame(const Image&, const CameraParameters&, const Features&, const vector<real_t>&);

private:
   Image xColorImage;
   Image xGrayImage;

   Features xFeatures;
   CameraParameters xCamParams;

   vector<real_t> xScaleFactors;

   static size_t count;
};

} // avr

#include "impl/Frame.hh"

#endif // AVR_TRACKING_FRAME_HPP
