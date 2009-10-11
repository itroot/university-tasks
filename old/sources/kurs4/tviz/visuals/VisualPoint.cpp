#include "VisualPoint.h"

VisualPoint::VisualPoint(double in_x, double in_y, double in_z) {
  Coords[0]=in_x;
  Coords[1]=in_y;
  Coords[2]=in_z;
  quad=gluNewQuadric();
}

VisualPoint::VisualPoint(const Vector3D<double>& coords) : Coords(coords) {
  quad=gluNewQuadric();
}

VisualPoint::VisualPoint(const Vector3D<int>& coords) {
  Coords[0]=coords[0];
  Coords[1]=coords[1];
  Coords[2]=coords[2];
  quad=gluNewQuadric();
}

VisualPoint::~VisualPoint() {
}

void VisualPoint::renderMe() {
  
  glPushMatrix();
  
  glTranslated(Coords[0],Coords[1],Coords[2]);
  glColor3f(R_COLOR,B_COLOR,G_COLOR);
  gluSphere(quad,RADIUS,SLICES,STACKS);
  
  glPopMatrix();

}

Vector3D<double> VisualPoint::getCoords() const {
  return Coords;
}

double VisualPoint::operator[](int arg) {
  if (arg>=0 && arg<DIMENSION) {
    return Coords[arg];
  } else  {
    // It's a mistake, need an exception here 
    throw;
  }
}
