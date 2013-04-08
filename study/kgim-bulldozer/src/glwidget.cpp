/***************************************************************************
 *   Copyright (C) 2007 by Ivan A. Tolstosheyev   *
 *   ivan.tolstosheyev@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <QtGui>
#include <QtOpenGL>

#include <math.h>

#include "glwidget.h"
GLWidget::GLWidget(QWidget *parent):QGLWidget(parent) {
  worldPhysics = new WorldPhysics();
  xRot = 300 * 16;
  yRot = 350*16;
  zRot = 45 * 16;
  xMov=-10;
  yMov=-30;
  Distance=-70;

  camera=0;
  back_height=5*HEIGHT;
  enable_axises=0;

  frames=0;
  fps=0;
  cfps=1000/(TIMER_STEP+1);
  fpsTime=QTime::currentTime().addMSecs(1000);

  animationTimer.setSingleShot(false);
  connect(&animationTimer, SIGNAL(timeout()), this, SLOT(animate()));
  animationTimer.start(TIMER_STEP);
}

GLWidget::~GLWidget()
{

}


void GLWidget::initializeGL()
{
  glEnable(GL_NORMALIZE);
  //glEnable(GL_MULTISAMPLE);
  glEnable(GL_TEXTURE_2D);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);

  //glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
  //glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
  //glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
  //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  //glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

  /////////////////////////

/* Инициализируем параметры материалов и
         * источника света
  */
         {
           glPushMatrix();
           glLoadIdentity();
           GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
           GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
           GLfloat light_specular[] = { 0.1, 0.1, 0.1, 1.0 };
           GLfloat light_position[] = { 0.0, 0.0, 20.0, 1.0 };
           /* устанавливаем параметры источника света */
           glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
           glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
           glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
           glLightfv (GL_LIGHT0, GL_POSITION, light_position);
           /* включаем освещение и источник света */
           glEnable (GL_LIGHTING);
           glEnable (GL_LIGHT0);
           glPopMatrix();
         }

  /////////////////////////

  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f,
                 static_cast<double>(width())/height()
                 ,0.1f,10000.0f);
  glMatrixMode(GL_MODELVIEW);

  groundtex=bindTexture(QPixmap("./bin/ground.bmp"));
  woodtex=bindTexture(QPixmap("./bin/wood.bmp"));
  bulldozertex=bindTexture(QPixmap("./bin/bulldozer.bmp"));
}

void GLWidget::paintGL() {
  fps++;
  frames++;
  if ((fpsTime<=QTime::currentTime())) {
    fpsTime=QTime::currentTime().addMSecs(1000);
    cfps=fps;
    fps=0;
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  glLoadIdentity();

  switch (camera) {
    case 0: {
      glTranslated(xMov, yMov, Distance);
      glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
      glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
      glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
    } break;
    case 1:{
      const dReal *p = worldPhysics->getBulldozerPosition();
      const dReal *r = worldPhysics->getBulldozerRotation();
      gluLookAt(p[0]-20*r[0],p[1]+20*r[1],p[2]+20*r[2]+back_height,p[0],p[1],p[2],0,0,1);
    } break;
  }

  GLfloat light_position[] = { 80.0, 30.0, 30.0, 1.0 };
  glLightfv (GL_LIGHT0, GL_POSITION, light_position);
  if (enable_axises) drawAxises();
  worldPhysics->drawGL(groundtex,woodtex,bulldozertex);
  glPopMatrix();

  glColor3f(0.0, 1.0, 0.0);
  
  const dReal* p=worldPhysics->getBulldozerPosition();
  const dReal* r=worldPhysics->getBulldozerRotation();
  
  renderText ( 0, 10, QString(tr("XR: %1 YR: %2 ZR: %3")).arg(xRot/16,6,' ').arg(yRot/16,6,' ').arg(zRot/16,6,' '));
  renderText (0, 20, QString(tr("FPS: %1")).arg(cfps));
  renderText (0, 30, QString(tr("Frames: %1")).arg(frames));
  renderText (0, 30, QString(tr("Frames: %1")).arg(frames));
  renderText (0, 40, QString(tr("Pos:%1 %2 %3")).arg(p[0],15,' ').arg(p[1],15,' ').arg(p[2],15,' '));
  renderText (0, 50, QString(tr("Rot:%1 %2 %3")).arg(r[0],15,' ').arg(r[1],15,' ').arg(r[2],15,' '));
  renderText (0, 60, QString(tr("dspeed:%1")).arg(worldPhysics->dspeed,15,' '));
  renderText (0, 70, QString(tr("speed:%1")).arg(worldPhysics->speed,15,' '));
  renderText (0, 80, QString(tr("Enable Complex (C toggle):%1")).arg(worldPhysics->enable_complex));

}

void GLWidget::resizeGL(int width, int height)
{
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f,static_cast<double>(this->width())/this->height(),0.1f,10000.0f);
  glMatrixMode(GL_MODELVIEW);
}




void GLWidget::drawAxises(void) {
  glBegin(GL_LINES);

  glColor3f(1.0, 1.0, 1.0);

  for (int i=1;i<11;i++) {
    for (int j=1;j<11;j++) {
      glVertex3f(10*i,0.0,0.0);
      glVertex3f(10*i,100.0,0.0);
      glVertex3f(0,10*j,0.0);
      glVertex3f(100.0,10*j,0.0);
    }
  }
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(100.0, 0.0, 0.0);

  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 100.0, 0.0);

  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 100.0);

  glEnd();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
  lastPos = event->pos();
}

 void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
  int dx = event->x() - lastPos.x();
  int dy = event->y() - lastPos.y();

  if (event->buttons() & Qt::LeftButton) {
    setXRotation(xRot + 8 * dy);
    setYRotation(yRot + 8 * dx);
  } else if (event->buttons() & Qt::RightButton) {
    setXRotation(xRot + 8 * dy);
    setZRotation(zRot + 8 * dx);
  } else if (event->buttons() & Qt::MidButton) {
    xMov+=static_cast<double>(dx)/10;
    yMov-=static_cast<double>(dy)/10;
    updateGL();
  } 
  lastPos = event->pos();
}

void GLWidget::wheelEvent(QWheelEvent *event) {
  if (event->delta()>0) Distance+=(Distance*0.1+0.01); else Distance-=(Distance*0.1+0.01);
  updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Left:{
      worldPhysics->steer-=0.1;
      if (worldPhysics->steer>0) worldPhysics->steer=0;
    } break;
    case Qt::Key_Right:{
      worldPhysics->steer+=0.1;
      if (worldPhysics->steer<0) worldPhysics->steer=0;
    } break;
    case Qt::Key_Up:{
      worldPhysics->speed+=1;
      if (worldPhysics->speed<0) worldPhysics->speed=0;
    } break;
    case Qt::Key_Down:{
      worldPhysics->speed-=1;
      if (worldPhysics->speed>0) worldPhysics->speed=0;
    } break;
    case Qt::Key_W:{
      back_height++;
    } break;
    case Qt::Key_S:{
      back_height--;
    } break;
    case Qt::Key_A:{
      worldPhysics->dspeed-=1;
      if (worldPhysics->dspeed>0) worldPhysics->dspeed=0;
    } break;
    case Qt::Key_D:{
      worldPhysics->dspeed+=1;
      if (worldPhysics->dspeed<0) worldPhysics->dspeed=0;
    } break;
    case Qt::Key_0:{
      camera=0;
    } break;
    case Qt::Key_1:{
      camera=1;
    } break;
    case Qt::Key_Space:{
      worldPhysics->bulldozer_state=1;
      worldPhysics->generateItems();
    } break;
    case Qt::Key_I:{
      worldPhysics->generateItems();
      worldPhysics->bulldozer_state=0;
      worldPhysics->speed=0;
      worldPhysics->dspeed=0;
    } break;
    case Qt::Key_C:{
      if (worldPhysics->enable_complex==0) 
        worldPhysics->enable_complex=1; 
      else
        worldPhysics->enable_complex=0; 
    } break;
    case Qt::Key_Q:{
      if (enable_axises==0) 
        enable_axises=1; 
      else
        enable_axises=0; 
    } break;
    default:
      QGLWidget::keyPressEvent(event);
  }
}

void GLWidget::setXRotation(int angle)
{
     normalizeAngle(&angle);
     if (angle != xRot) {
         xRot = angle;
         //emit xRotationChanged(angle);
         updateGL();
}
}

 void GLWidget::setYRotation(int angle)
{
     normalizeAngle(&angle);
     if (angle != yRot) {
         yRot = angle;
         //emit yRotationChanged(angle);
         updateGL();
}
}

 void GLWidget::setZRotation(int angle)
{
     normalizeAngle(&angle);
     if (angle != zRot) {
         zRot = angle;
         //emit zRotationChanged(angle);
         updateGL();
}
}

void GLWidget::normalizeAngle(int *angle)
{
  while (*angle < 0)
    *angle += 360 * 16;
  while (*angle > 360 * 16)
    *angle -= 360 * 16;
}

void GLWidget::animate() {
  if (worldPhysics->bulldozer_state) worldPhysics->AI();
  worldPhysics->mainLoop();
  update();
}

