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

#include "wheelitem.h"
#include "WorldPhysics.h"
#include <QtOpenGL>

WheelItem::WheelItem(dWorldID world,dSpaceID space,dQuaternion q,dReal radius,dReal mass)
{
  body = dBodyCreate(world);
  geom = dCreateSphere(space,radius);
  dBodySetQuaternion(body,q);

  dMass m;
  dMassSetSphere(&m,1,radius);
  dMassAdjust(&m,mass);
  dBodySetMass(body,&m);

  dGeomSetBody(geom,body);	
}

void WheelItem::renderMe() const
{
  dReal radius=dGeomSphereGetRadius (geom);

  GLUquadric *quad;
  quad= gluNewQuadric();
  

  glColor3f(0.2, 0.3, 0.4);
  gluSphere(quad , radius , 10 ,10 );
  
}

WheelItem::~WheelItem() {
  dGeomDestroy(geom);
  dBodyDestroy(body);
}
