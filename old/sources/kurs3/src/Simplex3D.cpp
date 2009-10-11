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


#include "Simplex3D.h"
#include <GL/gl.h>

//!!!!!!!!!!!
#include <QtDebug>

Simplex3D::Simplex3D(Point3D p1, Point3D p2, Point3D p3, Point3D p4, int scale){
  point1=new Point3D(p1);
  point2=new Point3D(p2);
  point3=new Point3D(p3);
  point4=new Point3D(p4);
  size=scale;
}

void Simplex3D::drawGL(Point3D * point) {
  
  if (point) {
    Point3D dp1=*point1-*point;
    Point3D dp2=*point2-*point;
    Point3D dp3=*point3-*point;
    Point3D dp4=*point4-*point;
    if ( (dp1.abs()>0.5) &&
         (dp2.abs()>0.5) &&
         (dp3.abs()>0.5) &&
         (dp4.abs()>0.5)
       ) return;
  }
  
  //glColor3f(0.0,1.0,1.0);
  //glPushMatrix();
  //Point3D tPoint=(*point1+*point2+*point3+*point4)/4*size*2;
  //glTranslated(tPoint.x(),tPoint.y(),tPoint.z());
  drawTriangle(point2,point3,point4);
  //glColor3f(1.0,0.0,1.0);
  drawTriangle(point1,point3,point4);
  //glColor3f(1.0,1.0,0.0);
  drawTriangle(point1,point2,point4);
  //glColor3f(0.0,1.0,0.0);
  drawTriangle(point1,point2,point3);
  //glPopMatrix();
}

void Simplex3D::drawTriangle(Point3D *p1, Point3D *p2, Point3D *p3) {
  Point3D cMass3=(*point1+*point2+*point3+*point4)/4*size;
  Point3D cMass2=(*p1+*p2+*p3)/3*size;
  Point3D vectorFromCenter=(cMass2-cMass3);
  Point3D vMult=(*p2-*p1)*(*p3-*p1)*size;
  

  if ((vectorFromCenter&vMult)<0) vMult=-vMult;

  //qDebug() << vMult.x() << vMult.y() << vMult.z() << endl <<
    //  vectorFromCenter.x()<< vectorFromCenter.y()<< vectorFromCenter.z() << (vectorFromCenter&vMult);

 // glBegin(GL_LINES);{
 //   glColor3f(1.0, 0.0, 0.0);
 //   glVertex3f(cMass2.x(),cMass2.y(),cMass2.z());
 //   glVertex3f(cMass2.x()+vMult.x(),cMass2.y()+vMult.y(),cMass2.z()+vMult.z());
 // }glEnd();


  glBegin(GL_TRIANGLES);{
    glColor3f(0.0, 1.0, 0.0);
    glNormal3f(vMult.x(),vMult.y(),vMult.z());

    glVertex3f(p1->x()*size, p1->y()*size, p1->z()*size);
    glVertex3f(p2->x()*size, p2->y()*size, p2->z()*size);
    glVertex3f(p3->x()*size, p3->y()*size, p3->z()*size);
    
    //glNormal3f(-vMult.x(),-vMult.y(),-vMult.z());
    //glVertex3f(p1->x()*size, p1->y()*size, p1->z()*size);
    //glVertex3f(p2->x()*size, p2->y()*size, p2->z()*size);
    //glVertex3f(p3->x()*size, p3->y()*size, p3->z()*size);
    
  }glEnd();
}

