#include "Renderer.h"
#include <QMouseEvent>

Renderer::Renderer(QWidget *parent):QGLWidget(parent) {
  DecartAxisesVisible=true;
  PositionTextVisible=true;
  xRot=300;
  yRot=350;
  zRot=45;
  xMov=0;
  yMov=0;
  Distance=-20;	
}

Renderer::~Renderer() {

}

void Renderer::initializeGL()
{
  glEnable(GL_NORMALIZE);
  //glEnable(GL_CULL_FACE);
  
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
  
  {
    glPushMatrix();
    glLoadIdentity();
    GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, 20.0, 1.0 };
    
    glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glPopMatrix();
  }
  
  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f,
                 static_cast<double>(width())/height()
                     ,0.1f,10000.0f);
  glMatrixMode(GL_MODELVIEW);
}

void Renderer::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glPushMatrix();
  glLoadIdentity();
  
  
  GLfloat light_position[] = { 50.0, 40.0, 30.0, 0.0 };
  glLightfv (GL_LIGHT0, GL_POSITION, light_position);

  glTranslated(xMov, yMov, Distance);
  glRotated(xRot, 1.0, 0.0, 0.0);
  glRotated(yRot, 0.0, 1.0, 0.0);
  glRotated(zRot, 0.0, 0.0, 1.0);

  drawDecartAxises();
  renderVisuals();
  renderPositionText();

  glPopMatrix();
}

void Renderer::resizeGL(int width, int height)
{
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f,static_cast<double>(this->width())/this->height(),0.1f,10000.0f);
  glMatrixMode(GL_MODELVIEW);
}

void Renderer::drawDecartAxises() {
  if (DecartAxisesVisible) {
    glBegin(GL_LINES);
  
    glColor3f(1.0, 1.0, 1.0);
  
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(25.0, 0.0, 0.0);
  
  
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 25.0, 0.0);
  
  
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 25.0);
  
  
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    renderText (25.0, 0.0, 0.0, "X");
    glColor3f(0.0, 1.0, 0.0);
    renderText (0.0, 25.0, 0.0, "Y");
    glColor3f(0.0, 0.0, 1.0);
    renderText (0.0, 0.0, 25.0, "Z");
  } 
}

void Renderer::normalizeAngle(int &angle)
{
  while (angle < 0) angle+=360;
  while (angle > 360) angle-=360;
}

void Renderer::setXRotation(int angle)
{
  normalizeAngle(angle);
  if (angle != xRot) {
    xRot = angle;
    updateGL();
  }
}

 void Renderer::setYRotation(int angle)
{
  normalizeAngle(angle);
  if (angle != yRot) {
    yRot = angle;
    updateGL();
  }
}

 void Renderer::setZRotation(int angle)
{
  normalizeAngle(angle);
  if (angle != zRot) {
    zRot = angle;
    updateGL();
  }
}

void Renderer::mousePressEvent(QMouseEvent *event) {
  lastPos = event->pos();
}

 void Renderer::mouseMoveEvent(QMouseEvent *event) {
  double dx = static_cast<double>(event->x()-lastPos.x());
  double dy = static_cast<double>(event->y()-lastPos.y());

  if (event->buttons() & Qt::LeftButton) {
    setXRotation(xRot + dy);
    setYRotation(yRot + dx);
  } else if (event->buttons() & Qt::RightButton) {
    setXRotation(xRot + dy);
    setZRotation(zRot + dx);
  } else if (event->buttons() & Qt::MidButton) {
    xMov+=dx/20;
    yMov-=dy/20;
    updateGL();
  } 
  lastPos = event->pos();
}

void Renderer::wheelEvent(QWheelEvent *event) {
  if (event->delta()>0) Distance+=(Distance*0.1+0.01); 
                   else Distance-=(Distance*0.1+0.01);
  updateGL();
}

void Renderer::renderPositionText() {
  if (PositionTextVisible) {
    glColor3f(1.0, 1.0, 1.0);
    renderText( 0, 10, 
    QString(tr("XR: %1 YR: %2 ZR: %3"))
    .arg(xRot,6,' ')
    .arg(yRot,6,' ')
    .arg(zRot,6,' ')
    );
  }
}

void Renderer::addVisual(VisualEntity* entity) {
  VisualsContainer.push_back(entity);
}

void Renderer::renderVisuals() {
  if (!VisualsContainer.empty()) {
    std::vector<VisualEntity*>::iterator it;
    for(it=VisualsContainer.begin();it<VisualsContainer.end();++it) {
      (*it)->render();
    }
  } 
}
