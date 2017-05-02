#include <View/MapDrawer.hpp>

#include <pangolin/pangolin.h>

using namespace std;
using namespace cv;

namespace avr {

MapDrawer::MapDrawer(const Ptr<Map>& _map) : pMap(_map), xCameraPose(MATRIX::Eye(4, 4)) {/* ctor */}

void MapDrawer::GetCurrentPose(Matrix& Twc) const {
   std::unique_lock<mutex> lock(xPoseMutex);
   Twc = xCameraPose.clone();
}

void MapDrawer::SetCurrentPose(const Matrix& Twc) {
   std::unique_lock<mutex> lock(xPoseMutex);
   xCameraPose = Twc.clone();
}

static Matrix inv(const Matrix& Tij) {
   Matrix Rji = Tij.rowRange(0, 3).colRange(0, 3).t();
   Matrix tji = -Rji * Tij.rowRange(0, 3).col(3);

   Matrix Tji = MATRIX::Eye(4, 4);
   Rji.copyTo(Tji.rowRange(0, 3).colRange(0, 3));
   tji.copyTo(Tji.rowRange(0, 3).col(3));

   return Tji;
}

void MapDrawer::DrawCurrentCamera() const {
   Matrix Twc;
   GetCurrentPose(Twc);
   Twc = Twc.t();

   const float w = 0.08;
   const float h = 0.75*w;
   const float z = 0.60*w;

   glPushMatrix();
      #ifdef AVR_DOUBLE_PRECISION
         glMultMatrixd(Twc.ptr<double>(0));
      #else
         glMultMatrixf(Twc.ptr<float>(0));
      #endif

      glLineWidth(3);
      glColor3f(0.0f,1.0f,0.0f);
      glBegin(GL_LINES);
         glVertex3f(0,0,0);
         glVertex3f(w,h,z);
         glVertex3f(0,0,0);
         glVertex3f(w,-h,z);
         glVertex3f(0,0,0);
         glVertex3f(-w,-h,z);
         glVertex3f(0,0,0);
         glVertex3f(-w,h,z);

         glVertex3f(w,h,z);
         glVertex3f(w,-h,z);

         glVertex3f(-w,h,z);
         glVertex3f(-w,-h,z);

         glVertex3f(-w,h,z);
         glVertex3f(w,h,z);

         glVertex3f(-w,-h,z);
         glVertex3f(w,-h,z);
      glEnd();
      DrawAxis();
   glPopMatrix();
}

void MapDrawer::DrawMapPoints(bool textured) const {
   glPointSize(5);
   glBegin(GL_POINTS);
      if(textured) {
         pMap->Iterate([] (const MapPoint& p) {
            glColor3ubv(p.GetColor().val);
            glVertex4fv(p.GetWorld().val);
         });
      } else {
         glColor3ub(40, 40, 40);
         pMap->Iterate([] (const MapPoint& p){
            glVertex4fv(p.GetWorld().val);
         });
      }
   glEnd();
}

void MapDrawer::DrawTrajectory(bool) const {
   const float w = 0.05;
   const float h = 0.75*w;
   const float z = 0.60*w;

   pMap->Iterate([w, h, z] (const KeyFrame& KF) {
      Matrix Twc = KF.GetParameters().GetPose().t();

      glPushMatrix();
         #ifdef AVR_DOUBLE_PRECISION
            glMultMatrixd(Twc.ptr<double>(0));
         #else
            glMultMatrixf(Twc.ptr<float>(0));
         #endif

         glLineWidth(2);
         glColor3f(0.0f,0.0f,1.0f);
         glBegin(GL_LINES);
            glVertex3f(0,0,0);
            glVertex3f(w,h,z);
            glVertex3f(0,0,0);
            glVertex3f(w,-h,z);
            glVertex3f(0,0,0);
            glVertex3f(-w,-h,z);
            glVertex3f(0,0,0);
            glVertex3f(-w,h,z);

            glVertex3f(w,h,z);
            glVertex3f(w,-h,z);

            glVertex3f(-w,h,z);
            glVertex3f(-w,-h,z);

            glVertex3f(-w,h,z);
            glVertex3f(w,h,z);

            glVertex3f(-w,-h,z);
            glVertex3f(w,-h,z);
         glEnd();
      glPopMatrix();
   });
}

void MapDrawer::DrawAxis(float length) const {
   float l2 = length/2.0f;

   glLineWidth(2);
   glBegin(GL_LINES);
      glColor3f(0.5f, 0.0f, 0.0f);
      glVertex3f(-l2, 0.0f, 0.0f);
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex3f(+l2, 0.0f, 0.0f);
   glEnd();

   glBegin(GL_LINES);
      glColor3f(0.0f, 0.5f, 0.0f);
      glVertex3f(0.0f, -l2, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex3f(0.0f, +l2, 0.0f);
   glEnd();

   glBegin(GL_LINES);
      glColor3f(0.0f, 0.0f, 0.5f);
      glVertex3f(0.0f, 0.0f, -l2);
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3f(0.0f, 0.0f, +l2);
   glEnd();
}

} // avr
