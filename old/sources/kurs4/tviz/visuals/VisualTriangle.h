#ifndef VISUALTRIANGLE_H_
#define VISUALTRIANGLE_H_

//#include "VisualEntity.h"
//#include "VisualPoint.h"
#include "VisualLine.h"


class VisualTriangle : public VisualEntity {
  public:
  	VisualTriangle(VisualPoint in_point1,
                   VisualPoint in_point2,
                   VisualPoint in_point3);
    virtual void renderMe();
  	virtual ~VisualTriangle();
  private:   
    static const double R_COLOR=1.0;
    static const double G_COLOR=0.0;
    static const double B_COLOR=0.0;
 
    VisualPoint Point1;
    VisualPoint Point2;
    VisualPoint Point3;
    
    VisualLine Line12;
    VisualLine Line23;
    VisualLine Line13;
};

#endif /*VISUALTRIANGLE_H_*/
