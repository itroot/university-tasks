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


#include "item.h"
#include <GL/gl.h>

Item::~Item()
{
}
void Item::render() const
{
  glPushMatrix();

  const dReal *p = dBodyGetPosition(body);
  const dReal *r = dBodyGetRotation(body);
  float m[16];
  m[ 0] = r[ 0];m[ 1] = r[ 4];m[ 2] = r[ 8];m[ 3] = 0;
  m[ 4] = r[ 1];m[ 5] = r[ 5];m[ 6] = r[ 9];m[ 7] = 0;
  m[ 8] = r[ 2];m[ 9] = r[ 6];m[10] = r[10];m[11] = 0;
  m[12] = p[ 0];m[13] = p[ 1];m[14] = p[ 2];m[15] = 1;
  glMultMatrixf(m);
	
  renderMe();
  glPopMatrix();
}
void Item::setPosition(dReal x,dReal y,dReal z)
{
	// Equivalent to dGeomSetPosition(geom,x,y,z);
  dBodySetPosition(body,x,y,z);
}

const dReal* Item::getPosition() {
  return dBodyGetPosition(body);
}

const dReal* Item::getRotation() {
  return dBodyGetRotation(body);
}