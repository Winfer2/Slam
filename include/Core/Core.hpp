#ifndef AVR_CORE_SLAM_HPP
#define AVR_CORE_SLAM_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <functional>
#include <iostream>
#include <utility>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>

// containers
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>

typedef int_fast8_t     byte_t;
typedef uint_fast8_t    ubyte_t;
typedef uint_fast32_t   index_t;

#ifdef AVR_DOUBLE_PRECISION
   typedef double  real_t;
#else
   typedef float real_t;
#endif // AVR_DOUBLE_PRECISION

#define MATRIX_TYPE    cv::DataType<real_t>::type
#define MATRIX_DEPTH   cv::DataDepth<real_t>::value

typedef std::atomic<bool>           abool_t;
typedef std::atomic<char>           achar_t;
typedef std::atomic<unsigned char>  auchar_t;
typedef std::atomic<int_fast8_t>    abyte_t;
typedef std::atomic<uint_fast8_t>   aubyte_t;
typedef std::atomic<int_fast16_t>   ashort_t;
typedef std::atomic<uint_fast16_t>  aushort_t;
typedef std::atomic<int_fast32_t>   aint_t;
typedef std::atomic<uint_fast32_t>  auint_t;
typedef std::atomic<int_fast64_t>   along_t;
typedef std::atomic<uint_fast64_t>  aulong_t;

namespace avr {

////////////////////// Point //////////////////////
using cv::Point;
using cv::Point2i;
using cv::Point3i;

typedef cv::Point                Pixel;
typedef cv::Point_<real_t>       Point2r;
typedef cv::Point3_<real_t>      Point3r;

/////////////////////// Vec //////////////////////
using cv::Vec2i;
using cv::Vec2b;
using cv::Vec3i;
using cv::Vec3b;

typedef cv::Vec<real_t, 2>       Vec2r;
typedef cv::Vec<real_t, 3>       Vec3r;
typedef cv::Vec<real_t, 4>       Vec4r;
typedef cv::Vec<real_t, 5>       Vec5r;
typedef cv::Vec<real_t, 6>       Vec6r;
typedef cv::Vec<real_t, 7>       Vec7r;

////////////////////// Matx //////////////////////
typedef cv::Matx<real_t, 2, 2>   Matx22r;
typedef cv::Matx<real_t, 3, 3>   Matx33r;
typedef cv::Matx<real_t, 3, 4>   Matx34r;
typedef cv::Matx<real_t, 4, 4>   Matx44r;

/////////////////////// Mat //////////////////////
using cv::Mat;

typedef cv::Mat                  Image;
typedef cv::Mat_<real_t>         Matrix;

namespace MATRIX {
   //! Matrix initializations
   inline Matrix Eye(size_t rows, size_t cols)     { return Matrix(cv::Mat::eye(rows, cols, MATRIX_TYPE)); }
   inline Matrix Eye(const cv::Size& sz)           { return Matrix(cv::Mat::eye(sz, MATRIX_TYPE)); }
   inline Matrix Ones(size_t rows, size_t cols)    { return Matrix(cv::Mat::ones(rows, cols, MATRIX_TYPE)); }
   inline Matrix Ones(const cv::Size& sz)          { return Matrix(cv::Mat::ones(sz, MATRIX_TYPE)); }
   inline Matrix Zeros(size_t rows, size_t cols)   { return Matrix(cv::Mat::zeros(rows, cols, MATRIX_TYPE)); }
   inline Matrix Zeros(const cv::Size& sz)         { return Matrix(cv::Mat::zeros(sz, MATRIX_TYPE)); }
} // MATRIX

namespace IMAGE {
   //! Projects an image over the other giving a parallax effect
   Image Parallax(const Image& P, const Image& Q);
} // IMAGE

//////////////////// Containers ////////////////////
using std::vector;
using std::deque;
using std::list;
using std::set;
using std::map;
// aliases for container of safe pointers
template <class T> using svector  = std::vector<cv::Ptr<T>>;
template <class T> using sdeque   = std::deque<cv::Ptr<T>>;
template <class T> using slist    = std::list<cv::Ptr<T>>;
template <class T> using sset     = std::set<cv::Ptr<T>>;
template <class K, class V> using smap = std::map<cv::Ptr<K>, V>;

////////////////// Miscellaneous //////////////////
using cv::Ptr;
using cv::Scalar;
using cv::Scalar_;
using cv::KeyPoint;

using std::string;   using std::function;
using std::cin;      using std::cout;
using std::cerr;     using std::endl;

typedef std::thread  Thread;
typedef std::mutex   Mutex;

//////////////////////////////////////////// Original Types ////////////////////////////////////////////

//! Interface of Builder design pattern to build complex objects
template <class T> class Builder {
public:
   virtual ~Builder() {/* dtor */}

   //! Build the object
   virtual cv::Ptr<T> Build() const = 0;

   //! Checks if builder is ready to build the object
   virtual bool isReady() const = 0;

   //! Returns the builder state log (use it to know why (when) builder is not ready)
   virtual string Log() const = 0;
};

/**
 * @brief Interface to control parallelable objects
 * This class implements a standart state machine control that can be overwrited
 * Standard State Machine:
 *    --> (Waiting) -- Start --> (Running) -- Stop ---> (Stopped) --> x
 *    --> (Waiting) -- Start --> (Running) -- Pause --> (Waiting) ...
 *    --> (Waiting) -- Stop ---> (Stopped) --> x
 * Actions:
 *    Waiting: it sleeps
 *    Running: it runs
 *    Stopped: it finishes
 */
class Parallelable {
public:
   Parallelable();
   virtual ~Parallelable();

   // Thread run control
   virtual void Start();
   virtual void Pause();
   virtual void Stop();

   // Thread state check
   virtual bool isWaiting() const;
   virtual bool isRunning() const;
   virtual bool isStopped() const;

   // Thread sleeps for ms milliseconds
   void Sleep(size_t ms) const;

protected:
   // State machine implementation
   virtual void Run();
   // Process execution (one iteration)
   virtual void Process() = 0;

protected:
   aubyte_t xState;
   abool_t  xStartRequired, xPauseRequired, xStopRequired;

   enum ST : ubyte_t { WAITING, RUNNING, STOPPED };
};

} // avr

#include "impl/Core.hh"

#endif // AVR_CORE_SLAM_HPP
