#ifndef RENDERER_H_
#define RENDERER_H_

#include <QGLWidget>
#include "visuals/VisualEntity.h"
#include <vector>

/**
 * Class renders via OpenGL different objects.
 */ 
class Renderer : public QGLWidget {
	public:
	  Renderer(QWidget *parent = 0);
    ~Renderer();
    // Set angle of view
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    // Add visuals
    void addVisual(VisualEntity* entity);
  protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
  private:
    void drawDecartAxises();
    void renderPositionText();
    void renderVisuals();
    void normalizeAngle(int &angle);
  private:
    std::vector<VisualEntity*> VisualsContainer;
  // Visual Options
    bool DecartAxisesVisible;
    bool PositionTextVisible;
  // Internal Variables
    double xRot;
    double yRot;
    double zRot;
    double xMov;
    double yMov;
    double Distance;
    
    QPoint lastPos;
};

#endif /*RENDERER_H_*/
