#ifndef VISUALLINE_H_
#define VISUALLINE_H_

#include "VisualEntity.h"
#include "VisualPoint.h"
#include <QtOpenGL>

class VisualLine : public VisualEntity {
  public:
  	VisualLine(VisualPoint in_point1, VisualPoint in_point2);
    void virtual renderMe();
  	virtual ~VisualLine();
  private:
    static const int SLICES=10;
    static const int RINGS=10;
    static const double RADIUS=0.1;
    static const double R_COLOR=0.0;
    static const double G_COLOR=0.0;
    static const double B_COLOR=1.0;
    VisualPoint Point1;
    VisualPoint Point2;
    GLUquadric *quad;
};

#endif /*VISUALLINE_H_*/
