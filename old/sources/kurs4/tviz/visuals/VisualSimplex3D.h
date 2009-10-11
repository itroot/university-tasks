#ifndef VISUALSIMPLEX3D_H_
#define VISUALSIMPLEX3D_H_

#include "VisualTriangle.h"

class VisualSimplex3D : public VisualEntity {
  public:
  	VisualSimplex3D(VisualPoint in_point1,
                    VisualPoint in_point2,
                    VisualPoint in_point3,
                    VisualPoint in_point4);
    virtual void renderMe();
  	virtual ~VisualSimplex3D();
  private:
    VisualPoint Point1;
    VisualPoint Point2;
    VisualPoint Point3;
    VisualPoint Point4;
    
    VisualLine Line12;
    VisualLine Line13;
    VisualLine Line14;
    VisualLine Line23;
    VisualLine Line24;
    VisualLine Line34;
    
    VisualTriangle Triangle123;
    VisualTriangle Triangle124;
    VisualTriangle Triangle134;
    VisualTriangle Triangle234;
};

#endif /*VISUALSIMPLEX3D_H_*/
