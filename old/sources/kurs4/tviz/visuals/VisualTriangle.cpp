#include "VisualTriangle.h"
#include <QtOpenGL>

VisualTriangle::VisualTriangle(VisualPoint in_point1,
                               VisualPoint in_point2,
                               VisualPoint in_point3):
                               Point1(in_point1),
                               Point2(in_point2),
                               Point3(in_point3),
                               Line12(in_point1,in_point2),
                               Line23(in_point2,in_point3),
                               Line13(in_point1,in_point3)
                                {

  Children.push_back(&Line12);
  Children.push_back(&Line23);
  Children.push_back(&Line13);
  Children.push_back(&Point1);
  Children.push_back(&Point2);
  Children.push_back(&Point3);
  
  setTheyChildPolicy(false);
}

VisualTriangle::~VisualTriangle() {

}


void VisualTriangle::renderMe() {
  glColor3f(R_COLOR,B_COLOR,G_COLOR);
   Vector3D<double> v1=Point1.getCoords()-Point2.getCoords();
   Vector3D<double> v2=Point1.getCoords()-Point3.getCoords();
   Vector3D<double> c_p=v2&v1; // cross product
   // center mass
   Vector3D<double> cm=Point1.getCoords()+Point2.getCoords()+Point3.getCoords();
   cm/=3;
   //glBegin(GL_LINES);
   //  glVertex3f(cm[0],cm[1],cm[2]);
   //  glVertex3f(c_p[0],c_p[1],c_p[2]);
   //  glVertex3f(cm[0],cm[1],cm[2]);
   //  glVertex3f(-c_p[0],-c_p[1],-c_p[2]);
   //glEnd();
   // must be checked
  glBegin(GL_TRIANGLES);
    glNormal3f(c_p[0],c_p[1],c_p[2]);
    glVertex3f(Point1[0],Point1[1],Point1[2]);
    glVertex3f(Point2[0],Point2[1],Point2[2]);
    glVertex3f(Point3[0],Point3[1],Point3[2]);
    // WTF ???
    //glNormal3f(-c_p[0],-c_p[1],-c_p[2]);
    //glVertex3f(Point1[0],Point1[1],Point1[2]);
    //glVertex3f(Point2[0],Point2[1],Point2[2]);
    //glVertex3f(Point3[0],Point3[1],Point3[2]);
  glEnd();
}
