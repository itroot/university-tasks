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


#include "complexitem.h"
#include "boxitem.h"
#include <GL/glut.h>
#include <QtGui>
#include <QtOpenGL>

ComplexItem::ComplexItem(dWorldID world,dSpaceID space,dReal width,dReal height,dReal depth,dReal mass)
{
  w=width;
  h=height;
  d=depth;

  box1=new BoxItem(world,space,width/2,height/2,depth/2,mass/5.0);
  body=box1->body;
  geom=box1->geom;
  
  
  box2=new BoxItem(world,space,width/2,height/2,depth/2,mass/5.0);
  box2->setPosition(width/2,0,0);

  box3=new BoxItem(world,space,width/2,height/2,depth/2,mass/5.0);
  box3->setPosition(-width/2,0,0);

  box4=new BoxItem(world,space,width/2,height/2,depth/2,mass/5.0);
  box4->setPosition(0,height/2,0);

  box5=new BoxItem(world,space,width/2,height/2,depth/2,mass/5.0);
  box5->setPosition(0,-height/2,0);
  
  box6=new BoxItem(world,space,width/2,height/2,depth/2,mass/5.0);
  box6->setPosition(0,0,depth/2);
  
  box7=new BoxItem(world,space,width/2,height/2,depth/2,mass/5.0);
  box7->setPosition(0,0,-depth/2);
  
  j12=dJointCreateSlider(world,0);
  dJointAttach(j12,box1->body,box2->body);
  dJointSetSliderAxis(j12,0,0,1);
  dJointSetSliderParam(j12,dParamLoStop,0);
  dJointSetSliderParam(j12,dParamHiStop,0);
  
  j13=dJointCreateSlider(world,0);
  dJointAttach(j13,box1->body,box3->body);
  dJointSetSliderAxis(j13,0,0,1);
  dJointSetSliderParam(j13,dParamLoStop,0);
  dJointSetSliderParam(j13,dParamHiStop,0);
  
  j14=dJointCreateSlider(world,0);
  dJointAttach(j14,box1->body,box4->body);
  dJointSetSliderAxis(j14,0,0,1);
  dJointSetSliderParam(j14,dParamLoStop,0);
  dJointSetSliderParam(j14,dParamHiStop,0);
  
  j15=dJointCreateSlider(world,0);
  dJointAttach(j15,box1->body,box5->body);
  dJointSetSliderAxis(j15,0,0,1);
  dJointSetSliderParam(j15,dParamLoStop,0);
  dJointSetSliderParam(j15,dParamHiStop,0);
  
  j16=dJointCreateSlider(world,0);
  dJointAttach(j16,box1->body,box6->body);
  dJointSetSliderAxis(j16,0,0,1);
  dJointSetSliderParam(j16,dParamLoStop,0);
  dJointSetSliderParam(j16,dParamHiStop,0);
  
  j17=dJointCreateSlider(world,0);
  dJointAttach(j17,box1->body,box7->body);
  dJointSetSliderAxis(j17,0,0,1);
  dJointSetSliderParam(j17,dParamLoStop,0);
  dJointSetSliderParam(j17,dParamHiStop,0);
  
}
void ComplexItem::renderMe() const
{
  box1->render();
  box2->render();
  box3->render();
  box4->render();
  box5->render();
  box6->render();
  box7->render();
}
void ComplexItem::render() const{
  renderMe();
}

void ComplexItem::setPosition(dReal x,dReal y,dReal z) {
  box1->setPosition(x,y,z);
  box2->setPosition(x+w/2,y,z);
  box3->setPosition(x-w/2,y,z);
  box4->setPosition(x,y+h/2,z);
  box5->setPosition(x,y-h/2,z);
  box6->setPosition(x,y,z+d/2);
  box7->setPosition(x,y,z-d/2);
}

ComplexItem::~ComplexItem() {
  dJointDestroy(j12);
  dJointDestroy(j13);
  dJointDestroy(j14);
  dJointDestroy(j15);
  dJointDestroy(j16);
  dJointDestroy(j17);
  
  delete box1;
  delete box2;
  delete box3;
  delete box4;
  delete box5;
  delete box6;
  delete box7;
}



