#include "VisualSimplex3D.h"
#include <QtOpenGL>

VisualSimplex3D::VisualSimplex3D(
                   VisualPoint in_point1,
                   VisualPoint in_point2,
                   VisualPoint in_point3,
                   VisualPoint in_point4): 
                     Point1(in_point1),
                     Point2(in_point2),
                     Point3(in_point3),
                     Point4(in_point4),
                     Line12(in_point1,in_point2),
                     Line13(in_point1,in_point3),
                     Line14(in_point1,in_point4),
                     Line23(in_point2,in_point3),
                     Line24(in_point2,in_point4),
                     Line34(in_point3,in_point4),
                     Triangle123(in_point1,in_point2,in_point3),
                     Triangle124(in_point1,in_point2,in_point4),
                     Triangle134(in_point1,in_point3,in_point4),
                     Triangle234(in_point2,in_point3,in_point4)
                   {
  Children.push_back(&Point1);
  Children.push_back(&Point2);
  Children.push_back(&Point3);
  Children.push_back(&Point4);
  
  Children.push_back(&Line12);
  Children.push_back(&Line13);
  Children.push_back(&Line14);
  Children.push_back(&Line23);
  Children.push_back(&Line24);
  Children.push_back(&Line34);
  
  Children.push_back(&Triangle123);
  Children.push_back(&Triangle124);
  Children.push_back(&Triangle134);
  Children.push_back(&Triangle234);
  
  setTheyChildPolicy(false);
}

VisualSimplex3D::~VisualSimplex3D() {
  
}

void VisualSimplex3D::renderMe() {
  // Nothing to render. Logically, we must fill the shape with color.
  // But I decide to render pyramid (4 triangles)
  return; //temporary
  glColor3f(1.0,0.0,0.0);
  glBegin(GL_TRIANGLES);
    glVertex3f(Point1[0],Point1[1],Point1[2]);
    glVertex3f(Point2[0],Point2[1],Point2[2]);
    glVertex3f(Point3[0],Point3[1],Point3[2]);
    
    glVertex3f(Point1[0],Point1[1],Point1[2]);
    glVertex3f(Point2[0],Point2[1],Point2[2]);
    glVertex3f(Point4[0],Point4[1],Point4[2]);
    
    glVertex3f(Point1[0],Point1[1],Point1[2]);
    glVertex3f(Point3[0],Point3[1],Point3[2]);
    glVertex3f(Point4[0],Point4[1],Point4[2]);
    
    glVertex3f(Point2[0],Point2[1],Point2[2]);
    glVertex3f(Point3[0],Point3[1],Point3[2]);
    glVertex3f(Point4[0],Point4[1],Point4[2]);
  glEnd();
}
