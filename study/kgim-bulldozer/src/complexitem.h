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

#ifndef COMPLEXITEM_H
#define COMPLEXITEM_H

#include "item.h"
#include "boxitem.h"

class ComplexItem : public Item
{
  public:
    ComplexItem(dWorldID world,dSpaceID space,dReal width,dReal height,dReal depth,dReal mass);
    unsigned char color[3];
    ~ComplexItem();
    BoxItem *box1;
    BoxItem *box2;
    BoxItem *box3;
    BoxItem *box4;
    BoxItem *box5;
    BoxItem *box6;
    BoxItem *box7;
    
    dJointID j12;
    dJointID j13;
    dJointID j14;
    dJointID j15;
    dJointID j16;
    dJointID j17;
//     
    void setPosition(dReal x,dReal y,dReal z);
    virtual void render() const;
  protected:
    virtual void renderMe() const;
  private:
    dReal w,h,d;
};


#endif
