#include "VisualLine.h"
#include "math.h"

VisualLine::VisualLine(VisualPoint in_point1, VisualPoint in_point2) :
  Point1(in_point1),
  Point2(in_point2) {
  Children.push_back(&Point1);
  Children.push_back(&Point2);
  setTheyChildPolicy(false);
  quad=gluNewQuadric();
}

VisualLine::~VisualLine() {
  
}


void VisualLine::renderMe() {
  // drawing a line (cylinder) between 2 points(children).
  glPushMatrix();
  
  Vector3D<double> delta_coords=Point2.getCoords()-Point1.getCoords();
  double cylinder_size=delta_coords.norm_2();
  double rotation_angle=180/M_PI*acos(delta_coords[2]/cylinder_size);
  // Calculating cross product
  double rotation_x=-delta_coords[1];
  double rotation_y=delta_coords[0];
  glTranslated(Point1.getCoords()[0],
               Point1.getCoords()[1],
               Point1.getCoords()[2]);
  glRotated(rotation_angle,
            rotation_x,
            rotation_y,
            0.0);
  glColor3f(R_COLOR,G_COLOR,B_COLOR);
  
  gluCylinder(quad,RADIUS,RADIUS,cylinder_size,SLICES,RINGS);
  
  glPopMatrix();
}
