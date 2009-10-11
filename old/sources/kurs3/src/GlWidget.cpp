/***************************************************************************
 *   Copyright (C) 2008 by Ivan A. Tolstosheyev   *
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

#include "GlWidget.h"


GlWidget::GlWidget(QWidget *parent):QGLWidget(parent) {
  xRot = 300 * 16;
  yRot = 350*16;
  zRot = 45 * 16;
  xMov=0;
  yMov=-8;
  Distance=-20;

  cube=new Cube3D(6,6,6);
  cube->setVisible(false);

  ocube=new OctoCube3D();
  ocube->setVisible(true);
}

GlWidget::~GlWidget()
{
  delete cube;
  delete ocube;
}


void GlWidget::initializeGL()
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
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    
    glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);
    
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

}

void GlWidget::paintGL() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  /*
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
*/

  
  glPushMatrix();
  glLoadIdentity();
  GLfloat light_position[] = { 5.0, 4.0, 3.0, 0.0 };
  glLightfv (GL_LIGHT0, GL_POSITION, light_position);
  glTranslated(xMov, yMov, Distance);
  glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
  glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
  glRotated(zRot / 16.0, 0.0, 0.0, 1.0);


  

  drawAxises();
  drawCube(cube);
  drawOcto(ocube);

  // Рисуем координаты куба.
  glPopMatrix();

  glColor3f(0.0, 1.0, 0.0);

  //renderText( 0, 10, QString(tr("XR: %1 YR: %2 ZR: %3")).arg(xRot/16,6,' ').arg(yRot/16,6,' ').arg(zRot/16,6,' '));

  
  //renderText ( 0, 20, QString(tr("%1")).arg(Cube3D::getBinaryDigit(3,0)));

}

void GlWidget::resizeGL(int width, int height)
{
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f,static_cast<double>(this->width())/this->height(),0.1f,10000.0f);
  glMatrixMode(GL_MODELVIEW);
}




void GlWidget::drawAxises(void) {
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

void GlWidget::mousePressEvent(QMouseEvent *event)
{
  lastPos = event->pos();
}

 void GlWidget::mouseMoveEvent(QMouseEvent *event)
{
  int dx = event->x() - lastPos.x();
  int dy = event->y() - lastPos.y();

  if (event->buttons() & Qt::LeftButton) {
    setXRotation(static_cast<int>(xRot) + 8 * dy);
    setYRotation(static_cast<int>(yRot) + 8 * dx);
  } else if (event->buttons() & Qt::RightButton) {
    setXRotation(static_cast<int>(xRot) + 8 * dy);
    setZRotation(static_cast<int>(zRot) + 8 * dx);
  } else if (event->buttons() & Qt::MidButton) {
    xMov+=static_cast<double>(dx)/10;
    yMov-=static_cast<double>(dy)/10;
    updateGL();
  } 
  lastPos = event->pos();
}

void GlWidget::wheelEvent(QWheelEvent *event) {
  if (event->delta()>0) Distance+=(Distance*0.1+0.01); else Distance-=(Distance*0.1+0.01);
  updateGL();
}


void GlWidget::setXRotation(int angle)
{
  normalizeAngle(&angle);
  if (angle != xRot) {
    xRot = angle;
    updateGL();
  }
}

 void GlWidget::setYRotation(int angle)
{
  normalizeAngle(&angle);
  if (angle != yRot) {
    yRot = angle;
    updateGL();
  }
}

 void GlWidget::setZRotation(int angle)
{
  normalizeAngle(&angle);
  if (angle != zRot) {
    zRot = angle;
    updateGL();
  }
}

void GlWidget::normalizeAngle(int *angle)
{
  while (*angle < 0)
    *angle += 360 * 16;
  while (*angle > 360 * 16)
    *angle -= 360 * 16;
}

void GlWidget::drawCube(Cube3D *currentCube) {
  if (!currentCube->isVisible()) return;
  currentCube->drawGL();

  QString to_send=QString(tr("%1%2%3%4 - %5 %6"))
      .arg(cube->getNumberOfPower(0))
          .arg(currentCube->getNumberOfPower(1))
          .arg(currentCube->getNumberOfPower(2))
          .arg(currentCube->getNumberOfPower(3))
          .arg(currentCube->getTriangulation())
          .arg(currentCube->getTriangulation(),6,2,QLatin1Char('0'));
  sendInfo(to_send);

  int x=currentCube->getX();
  int y=currentCube->getY();
  int z=currentCube->getZ();
  int size=currentCube->getSize();


  glColor3f(1.0, 1.0, 1.0);
  for(int i=0;i<8;++i) {
    int xd=Cube3D::getBinaryDigit(i,0);
    int yd=Cube3D::getBinaryDigit(i,1);
    int zd=Cube3D::getBinaryDigit(i,2);
    renderText
        (x+xd*size, y+yd*size, z+zd*size,
         QString("%1%2%3 (%4)").arg(xd).arg(yd).arg(zd).arg(currentCube->getVertexPower(xd,yd,zd)));
  }
}

void GlWidget::drawOcto(OctoCube3D *currentOcto) {
  if (!ocube->isVisible()) return;
  ocube->drawGL();
  QString to_send=QString("Ext: %1 Int: %2")
      .arg(ocube->getOctoDiags().externalFaces,24,2,QLatin1Char('0'))
          .arg(ocube->getOctoDiags().internalFaces,12,2,QLatin1Char('0'))+"\n"+
  QString("xyz %1 xyZ %2 xYz %3 xYZ %4 Xyz %5 XyZ %6 XYz %7 XYZ %8")
      .arg(ocube->getCubeDiags(0,0,0),6,2,QLatin1Char('0'))
          .arg(ocube->getCubeDiags(0,0,1),6,2,QLatin1Char('0'))
          .arg(ocube->getCubeDiags(0,1,0),6,2,QLatin1Char('0'))
          .arg(ocube->getCubeDiags(0,1,1),6,2,QLatin1Char('0'))
          .arg(ocube->getCubeDiags(1,0,0),6,2,QLatin1Char('0'))
          .arg(ocube->getCubeDiags(1,0,1),6,2,QLatin1Char('0'))
          .arg(ocube->getCubeDiags(1,1,0),6,2,QLatin1Char('0'))
          .arg(ocube->getCubeDiags(1,1,1),6,2,QLatin1Char('0'));
  sendInfo(to_send);
}

void GlWidget::sendInfo(const QString &text) {
  emit sendInfo_signal(text);
}
