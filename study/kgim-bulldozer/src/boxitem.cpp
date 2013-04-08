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

#include "boxitem.h"
#include <QtGui>
#include <QtOpenGL>

BoxItem::BoxItem(dWorldID world,dSpaceID space,dReal width,dReal height,dReal depth,dReal mass)
{
  body = dBodyCreate(world);
  geom = dCreateBox(space,width,height,depth);

  dMass m;
  dMassSetBox(&m,1.0f,width,height,depth);
  dMassAdjust(&m,mass);
  dBodySetMass(body,&m);

  dGeomSetBody(geom,body);	
}
void BoxItem::renderMe() const
{
  dVector3 lengths;
  dGeomBoxGetLengths(geom,lengths);
  glScalef(lengths[0]/2,lengths[1]/2,lengths[2]/2);
  glColor3f(1.0,1.0,1.0);
  glPushMatrix();

  glBegin(GL_QUADS);

  //glColor3f(0.0f,1.0f,0.0f);
  glNormal3f(0,1,0);
  glTexCoord2d(0, 1);
  glVertex3f( 1.0f, 1.0f,-1.0f);
  glTexCoord2d(0, 0);
  glVertex3f(-1.0f, 1.0f,-1.0f);
  glTexCoord2d(1, 0);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glTexCoord2d(1, 1);
  glVertex3f( 1.0f, 1.0f, 1.0f);

  //glColor3f(1.0f,0.5f,0.0f);
  glNormal3f(0,-1,0);
  glTexCoord2d(1, 1);
  glVertex3f( 1.0f,-1.0f, 1.0f);
  glTexCoord2d(0, 1);
  glVertex3f(-1.0f,-1.0f, 1.0f);
  glTexCoord2d(0, 0);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2d(1, 0);
  glVertex3f( 1.0f,-1.0f,-1.0f);

  //glColor3f(1.0f,0.0f,0.0f);
  glNormal3f(0,0,1);
  glTexCoord2d(1, 1);
  glVertex3f( 1.0f, 1.0f, 1.0f);
  glTexCoord2d(0, 1);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glTexCoord2d(0, 0);
  glVertex3f(-1.0f,-1.0f, 1.0f);
  glTexCoord2d(1, 0);
  glVertex3f( 1.0f,-1.0f, 1.0f);

  //glColor3f(1.0f,1.0f,0.0f);
  glNormal3f(0,0,-1);
  glTexCoord2d(1, 0);
  glVertex3f( 1.0f,-1.0f,-1.0f);
  glTexCoord2d(0, 0);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2d(0, 1);
  glVertex3f(-1.0f, 1.0f,-1.0f);
  glTexCoord2d(1, 1);
  glVertex3f( 1.0f, 1.0f,-1.0f);

  //glColor3f(0.0f,0.0f,1.0f);
  glNormal3f(-1,0,0);
  glTexCoord2d(1, 1);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glTexCoord2d(1, 0);
  glVertex3f(-1.0f, 1.0f,-1.0f);
  glTexCoord2d(0, 0);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2d(0, 1);
  glVertex3f(-1.0f,-1.0f, 1.0f);

  //glColor3f(1.0f,0.0f,1.0f);
  glNormal3f(1,0,0);
  glTexCoord2d(1, 0);
  glVertex3f( 1.0f, 1.0f,-1.0f);
  glTexCoord2d(1, 1);
  glVertex3f( 1.0f, 1.0f, 1.0f);
  glTexCoord2d(0, 1);
  glVertex3f( 1.0f,-1.0f, 1.0f);
  glTexCoord2d(0, 0);
  glVertex3f( 1.0f,-1.0f,-1.0f);

  glEnd();

  glPopMatrix();
}

BoxItem::~BoxItem() {
  dGeomDestroy(geom);
  dBodyDestroy(body);
}