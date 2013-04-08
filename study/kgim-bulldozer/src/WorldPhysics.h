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

#ifndef WORLD_PHYSICS_H
#define WORLD_PHYSICS_H

#include "item.h"
#include "boxitem.h"
#include "wheelitem.h"

#include "ode/ode.h"
#include <QObject>
#include <QVector>
#include <QtOpenGL>

#define LENGTH 5.7 // chassis length
#define WIDTH 4.5 // chassis width
#define HEIGHT 1.0 // chassis height
#define RADIUS 1.5 // wheel radius
#define STARTZ 15.0 // starting height of chassis
#define CMASS 0.4 // chassis mass
#define WMASS 0.2 // wheel mass

#define BUCKET_LENGTH (LENGTH/10.0)
#define BUCKET_WIDTH (WIDTH*2.0)
#define BUCKET_HEIGHT (HEIGHT+RADIUS*3/4)

#define MAX_ITEMS 7

#define STARTX (LENGTH+WIDTH)
#define STARTY (LENGTH+WIDTH+20)

// Heightfield dimensions

#define HFIELD_WSTEP			50
#define HFIELD_DSTEP			50

#define HFIELD_WIDTH			REAL( 120.0 )
#define HFIELD_DEPTH			REAL( 120.0 )

#define HFIELD_WSAMP			( HFIELD_WIDTH / ( HFIELD_WSTEP-1 ) )
#define HFIELD_DSAMP			( HFIELD_DEPTH / ( HFIELD_DSTEP-1 ) )

#define	DEGTORAD			0.01745329251994329577f



class WorldPhysics : public QObject {

  Q_OBJECT

  public:
    WorldPhysics();
    void mainLoop();
    void handleCollisionBetween(dGeomID o0, dGeomID o1);
    dReal heightfield_callback( int x, int z );
    void drawGL(GLuint floortex, GLuint woodtex, GLuint bulldozertex);
    //~WorldPhysics();

    const dReal* getBulldozerPosition();
    const dReal* getBulldozerRotation();
    int RotateTo(dReal directionx,dReal directiony);
    void generateItems();

    void AI();
    
    dReal normal(int XYZ,dReal x1,dReal y1, dReal z1,dReal x2,dReal y2,dReal z2);
    

    dReal speed;
    dReal steer;
    dReal dspeed;
    

    int bulldozer_state;
    
  //private:


    void drawBulldozer();
    Item* generateItem();

    QVector<Item*> items;

    // Our heightfield geom
    dGeomID gheight;

    dWorldID world;
    dSpaceID space;
    dSpaceID bulldozer_space;

    BoxItem *bulldozer;
    BoxItem *bulldozer_cabin;
    WheelItem *wheels[4];
    BoxItem *bulldozer_bucket_c;
    BoxItem *bulldozer_bucket_l;
    BoxItem *bulldozer_bucket_r;

    dJointID bucket_joint_c;
    dJointID bucket_joint_l;
    dJointID bucket_joint_r;

    dJointID cabin_joint;
    dJointID wheelJoints[4];

    dJointID cheat_joint;
    
    dJointGroupID contactgroup;

    dGeomID ground_cheat;
    
    dGeomID wall1;
    dGeomID wall2;
    dGeomID wall3;
    dGeomID wall4;

    dReal tmp_scalar;
    int tmp_wait;
    
    int enable_complex;



};

#endif
