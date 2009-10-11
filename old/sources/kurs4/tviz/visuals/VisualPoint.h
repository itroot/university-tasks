#ifndef VISUALPOINT_H_
#define VISUALPOINT_H_

#include "VisualEntity.h" 
#include "tmath/Vector3D.h"
#include <QtOpenGL>

class VisualPoint : public VisualEntity {
  public:
  	VisualPoint(double in_x, double in_y, double in_z);
    VisualPoint(const Vector3D<double>& coords);
    VisualPoint(const Vector3D<int>& coords);
    virtual void renderMe();
  	virtual ~VisualPoint();
    Vector3D<double> getCoords()const;
    double operator[](int arg);
  private:
    static const double RADIUS=0.3;
    static const int SLICES=10;
    static const int STACKS=10;
    static const double R_COLOR=0.0;
    static const double G_COLOR=0.0;
    static const double B_COLOR=1.0;
    static const int DIMENSION=3;
    Vector3D<double> Coords; 
    GLUquadric *quad;
};

#endif /*VISUALPOINT_H_*/
