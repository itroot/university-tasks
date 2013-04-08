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

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget> 
#include <QTimer>
#include <QTime>

#include "WorldPhysics.h"

#define TIMER_STEP 20


class GLWidget : public QGLWidget
{
  Q_OBJECT

  public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    WorldPhysics *worldPhysics;


  public slots:
    void animate();

  protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
  private:
    void drawAxises(void);  
    void normalizeAngle(int *angle);

    int fps;
    int cfps;
    int frames;

    int camera; // Type of view
    int back_height;

    QTime fpsTime;
    QPoint lastPos;
    QTimer animationTimer;
    double xRot;
    double yRot;
    double zRot;
    double xMov;
    double yMov;
    double Distance;
    
    GLuint groundtex;
    GLuint woodtex;
    GLuint bulldozertex;

    int enable_axises;
};

#endif




