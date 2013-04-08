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

#include "WorldPhysics.h"
#include "item.h"
#include "boxitem.h"
#include "complexitem.h"

#include "ode/ode.h"
#include <QtGui>
#include <QtOpenGL>

#include <math.h>

void nearCallback(void *data, dGeomID o0, dGeomID o1)
{
  reinterpret_cast<WorldPhysics*>(data)->handleCollisionBetween(o0,o1);
}

dReal near_heightfield_callback( void* data, int x, int z )
{
 return reinterpret_cast<WorldPhysics*>(data)->heightfield_callback(x,z);
}

WorldPhysics::WorldPhysics() {

  enable_complex=0;
  bulldozer_state=1;
  tmp_scalar=0;
  tmp_wait=0;

  qsrand(QTime::currentTime().msec());

  dInitODE();
  world = dWorldCreate();
  space = dHashSpaceCreate (0);
  contactgroup = dJointGroupCreate (0);
  dWorldSetGravity (world,0,0,-9.81);
  //ground_cheat = dCreatePlane (space,0,0,1,0);
  wall1=dCreatePlane (space,-1,0,0,-100);
  wall2=dCreatePlane (space,1,0,0,0);
  wall3=dCreatePlane (space,0,-1,0,-100);
  wall4=dCreatePlane (space,0,1,0,0);
  
  
  
  // our heightfield floor

  dHeightfieldDataID heightid = dGeomHeightfieldDataCreate();

	// Create an finite heightfield.
  dGeomHeightfieldDataBuildCallback( heightid, NULL, near_heightfield_callback,
                                     HFIELD_WIDTH, HFIELD_DEPTH, HFIELD_WSTEP, HFIELD_DSTEP,
                                     REAL( 1.0 ), REAL( 0.0 ), REAL( 0.0 ), 0 );

	// Give some very bounds which, while conservative,
	// makes AABB computation more accurate than +/-INF.
  //dGeomHeightfieldDataSetBounds( heightid, REAL( -4.0 ), REAL( +6.0 ) );

  gheight = dCreateHeightfield( space, heightid, 1 );
  
  
  
  // Rotate so Z is up, not Y (which is the default orientation)
  dMatrix3 R;
  dRSetIdentity( R );
  dRFromAxisAndAngle( R, 1, 0, 0, DEGTORAD * 90 );
  dGeomSetRotation( gheight, R );
  dGeomSetPosition( gheight, 50,50,0 );

//  for (int  i=0;i<MAX_ITEMS;i++) {
  //  items.push_back(generateItem());
  //}
  generateItems();

  bulldozer_space = dSimpleSpaceCreate(space);
  dSpaceSetCleanup (bulldozer_space,0);
  
  bulldozer=new BoxItem(world,bulldozer_space,LENGTH,WIDTH,HEIGHT,CMASS);
  bulldozer->setPosition(STARTX,STARTY,STARTZ);

  bulldozer_cabin=new BoxItem(world,bulldozer_space,LENGTH/2,WIDTH/2,2*HEIGHT,CMASS/3);
  bulldozer_cabin->setPosition(-LENGTH/4+STARTX,STARTY,3.0/2.0*HEIGHT+STARTZ);

  bulldozer_bucket_c=new BoxItem(world,bulldozer_space,BUCKET_LENGTH,BUCKET_WIDTH,BUCKET_HEIGHT,CMASS/10);
  bulldozer_bucket_c->setPosition(LENGTH/2+BUCKET_LENGTH/2+RADIUS+STARTX,STARTY,STARTZ);
  
  bulldozer_bucket_l=new BoxItem(world,bulldozer_space,BUCKET_WIDTH/5,BUCKET_LENGTH,BUCKET_HEIGHT,CMASS/20);
  bulldozer_bucket_l->setPosition(LENGTH/2+BUCKET_LENGTH+RADIUS+BUCKET_WIDTH/10+STARTX,-BUCKET_WIDTH/2+BUCKET_LENGTH/2+STARTY,STARTZ);
  
  
  bulldozer_bucket_r=new BoxItem(world,bulldozer_space,BUCKET_WIDTH/5,BUCKET_LENGTH,BUCKET_HEIGHT,CMASS/20);
  bulldozer_bucket_r->setPosition(LENGTH/2+BUCKET_LENGTH+RADIUS+BUCKET_WIDTH/10+STARTX,BUCKET_WIDTH/2-BUCKET_LENGTH/2+STARTY,STARTZ);
  
  
  for (int i=0; i<4; i++) {
    dQuaternion q;
    dQFromAxisAndAngle(q,1,0,0,M_PI*0.5);
    wheels[i] = new WheelItem(world,bulldozer_space,q,RADIUS,WMASS);
  }
  dBodySetPosition (wheels[0]->body,0.5*LENGTH+STARTX,WIDTH*0.5+STARTY,STARTZ-HEIGHT*0.5);
  dBodySetPosition (wheels[1]->body,0.5*LENGTH+STARTX,-WIDTH*0.5+STARTY,STARTZ-HEIGHT*0.5);
  dBodySetPosition (wheels[2]->body,-0.5*LENGTH+STARTX, WIDTH*0.5+STARTY,STARTZ-HEIGHT*0.5);
  dBodySetPosition (wheels[3]->body,-0.5*LENGTH+STARTX,-WIDTH*0.5+STARTY,STARTZ-HEIGHT*0.5);

  cabin_joint=dJointCreateSlider(world,0);
  dJointAttach(cabin_joint,bulldozer->body,bulldozer_cabin->body);
  dJointSetSliderAxis(cabin_joint,0,0,1);
  dJointSetSliderParam(cabin_joint,dParamLoStop,0);
  dJointSetSliderParam(cabin_joint,dParamHiStop,0);

  bucket_joint_c=dJointCreateSlider(world,0);
  dJointAttach(bucket_joint_c,bulldozer->body,bulldozer_bucket_c->body);
  dJointSetSliderAxis(bucket_joint_c,0,0,1);
  dJointSetSliderParam(bucket_joint_c,dParamLoStop,0);
  dJointSetSliderParam(bucket_joint_c,dParamHiStop,0);
  
  bucket_joint_l=dJointCreateSlider(world,0);
  dJointAttach(bucket_joint_l,bulldozer->body,bulldozer_bucket_l->body);
  dJointSetSliderAxis(bucket_joint_l,0,0,1);
  dJointSetSliderParam(bucket_joint_l,dParamLoStop,0);
  dJointSetSliderParam(bucket_joint_l,dParamHiStop,0);
  
  bucket_joint_r=dJointCreateSlider(world,0);
  dJointAttach(bucket_joint_r,bulldozer->body,bulldozer_bucket_r->body);
  dJointSetSliderAxis(bucket_joint_r,0,0,1);
  dJointSetSliderParam(bucket_joint_r,dParamLoStop,0);
  dJointSetSliderParam(bucket_joint_r,dParamHiStop,0);

  // front and back wheel hinges
  for (int i=0; i<4; i++) {
    wheelJoints[i] = dJointCreateHinge2 (world,0);
    dJointAttach (wheelJoints[i],bulldozer->body,wheels[i]->body);
    const dReal *a = dBodyGetPosition (wheels[i]->body);
    dJointSetHinge2Anchor (wheelJoints[i],a[0],a[1],a[2]);
    dJointSetHinge2Axis1 (wheelJoints[i],0,0,1);
    dJointSetHinge2Axis2 (wheelJoints[i],0,1,0);
  }
  // seeting ERP & CRM
  for (int i=0; i<4; i++) {
    dJointSetHinge2Param (wheelJoints[i],dParamSuspensionERP,0.5);
    dJointSetHinge2Param (wheelJoints[i],dParamSuspensionCFM,0.8);
  }
  // block back axis !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  for (int i=0; i<2; i++) {
    dJointSetHinge2Param (wheelJoints[i],dParamLoStop,0);
    dJointSetHinge2Param (wheelJoints[i],dParamHiStop,0);
  }

}

void WorldPhysics::handleCollisionBetween(dGeomID o0, dGeomID o1) {
  int i,n;

  // only collide things with the ground
  //int g1 = (o1 == ground || o1 == ground_box);
  //int g2 = (o2 == ground || o2 == ground_box);
  //if (!(g1 ^ g2)) return;

 // for(int i=0;i<4;i++) {
 //   if (((o0==bulldozer->geom) && (o1==wheels[i]->geom)) ||
 //       ((o0==wheels[i]->geom) && (o1==bulldozer->geom))) return;
 // }
  
  

  const int N = 100;
  dContact contact[N];
  n = dCollide (o0,o1,N,&contact[0].geom,sizeof(dContact));
  if (n > 0) {
    for (i=0; i<n; i++) {
      contact[i].surface.mode = dContactSlip1 | dContactSlip2 |
          dContactSoftERP | dContactSoftCFM | dContactApprox1;
      contact[i].surface.mu = 1.7;
      contact[i].surface.slip1 = 0.1;
      contact[i].surface.slip2 = 0.1;
      contact[i].surface.soft_erp = 0.5;
      contact[i].surface.soft_cfm = 0.3;
      dJointID c = dJointCreateContact (world,contactgroup,&contact[i]);
      dJointAttach (c,
                    dGeomGetBody(contact[i].geom.g1),
                                 dGeomGetBody(contact[i].geom.g2));
    }
  }
}


void WorldPhysics::mainLoop ()
{
  for (int i=0;i<4;i++) {
    if (i%2) {
      dJointSetHinge2Param (wheelJoints[i],dParamVel2,-speed+dspeed);
      dJointSetHinge2Param (wheelJoints[i],dParamFMax2,10);
    } else
    {
      dJointSetHinge2Param (wheelJoints[i],dParamVel2,-speed-dspeed);
      dJointSetHinge2Param (wheelJoints[i],dParamFMax2,10);
    }
    if (i>=2) { 
      dJointSetHinge2Param (wheelJoints[i],dParamVel,0);
      dJointSetHinge2Param (wheelJoints[i],dParamFMax,100);
      dJointSetHinge2Param (wheelJoints[i],dParamLoStop,0);
      dJointSetHinge2Param (wheelJoints[i],dParamHiStop,0);
      dJointSetHinge2Param (wheelJoints[i],dParamFudgeFactor,0.1);
    }
  
    if (i<2) {
      // steering
      dReal v = steer - dJointGetHinge2Angle1 (wheelJoints[i]);
      if (v > 0.1) v = 0.1;
      if (v < -0.1) v = -0.1;
      v *= 10.0;
      dJointSetHinge2Param (wheelJoints[i],dParamVel,v);
      dJointSetHinge2Param (wheelJoints[i],dParamFMax,5);
      dJointSetHinge2Param (wheelJoints[i],dParamLoStop,-1);
      dJointSetHinge2Param (wheelJoints[i],dParamHiStop,1);
      dJointSetHinge2Param (wheelJoints[i],dParamFudgeFactor,0.1);
    }
  }
  dSpaceCollide (space,this,&nearCallback);
  dWorldStep (world,0.05);

    // remove all contact joints
  dJointGroupEmpty (contactgroup);
}

void WorldPhysics::drawGL(GLuint floortex, GLuint woodtex,  GLuint bulldozertex) {
  glBindTexture(GL_TEXTURE_2D,woodtex);
  for (int i=0;i<items.size();i++) {
    items[i]->render();
  }
  glBindTexture(GL_TEXTURE_2D,bulldozertex);
  drawBulldozer();
  
  const dReal* p = dGeomGetPosition( gheight );

  const dReal* r = dGeomGetRotation( gheight );

  //
	// Draw Heightfield
  //

	// Set ox and oz to zero for DHEIGHTFIELD_CORNER_ORIGIN mode.
  int ox = (int) ( -HFIELD_WIDTH/2 );
  int oz = (int) ( -HFIELD_DEPTH/2 );

//	for ( int tx = -1; tx < 2; ++tx )
//	for ( int tz = -1; tz < 2; ++tz )
  {

    for ( int i = 0; i < HFIELD_WSTEP - 1; ++i )
      for ( int j = 0; j < HFIELD_DSTEP - 1; ++j )
    {
      dReal a[3], b[3], c[3], d[3];

      a[ 0 ] = ox + ( i ) * HFIELD_WSAMP;
      a[ 1 ] = heightfield_callback( i, j );
      a[ 2 ] = oz + ( j ) * HFIELD_DSAMP;

      b[ 0 ] = ox + ( i + 1 ) * HFIELD_WSAMP;
      b[ 1 ] = heightfield_callback( i + 1, j );
      b[ 2 ] = oz + ( j ) * HFIELD_DSAMP;

      c[ 0 ] = ox + ( i ) * HFIELD_WSAMP;
      c[ 1 ] = heightfield_callback( i, j + 1 );
      c[ 2 ] = oz + ( j + 1 ) * HFIELD_DSAMP;

      d[ 0 ] = ox + ( i + 1 ) * HFIELD_WSAMP;
      d[ 1 ] = heightfield_callback(  i + 1, j + 1 );
      d[ 2 ] = oz + ( j + 1 ) * HFIELD_DSAMP;

     
      if (
          (a[0]>-50 || b[0]>-50 || c[0]>-50 || d[0]>-50) &&
          (a[0]<50 || b[0]<50 || c[0]<50 || d[0]<50) &&
          (a[2]>-50 || b[2]>-50 || c[2]>-50 || d[2]>-50) &&
          (a[2]<50 || b[2]<50 || c[2]<50 || d[2]<50)
         ) {
      
        glPushMatrix();
        
        float m[16];
        m[ 0] = r[ 0];m[ 1] = r[ 4];m[ 2] = r[ 8];m[ 3] = 0;
        m[ 4] = r[ 1];m[ 5] = r[ 5];m[ 6] = r[ 9];m[ 7] = 0;
        m[ 8] = r[ 2];m[ 9] = r[ 6];m[10] = r[10];m[11] = 0;
        m[12] = p[ 0];m[13] = p[ 1];m[14] = p[ 2];m[15] = 1;
        glMultMatrixf(m);
  ///////////////
#ifdef o
        glBegin(GL_LINES);
        glColor3f(0.0, 1.0, 0.0);
        
        glVertex3f(a[0],a[1],a[2]);
        glVertex3f(a[0]-normal(0,a[0]-b[0],a[1]-b[1],a[2]-b[2],a[0]-d[0],a[1]-d[1],a[2]-d[2]),
                   a[1]-normal(1,a[0]-b[0],a[1]-b[1],a[2]-b[2],a[0]-d[0],a[1]-d[1],a[2]-d[2]),
                   a[2]-normal(2,a[0]-b[0],a[1]-b[1],a[2]-b[2],a[0]-d[0],a[1]-d[1],a[2]-d[2])
                  );
        glEnd();
  ///////////////    
        ///////////////
        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        
        glVertex3f(a[0],a[1],a[2]);
        glVertex3f(a[0]+normal(0,a[0]-c[0],a[1]-c[1],a[2]-c[2],a[0]-d[0],a[1]-d[1],a[2]-d[2]),
                   a[1]+normal(1,a[0]-c[0],a[1]-c[1],a[2]-c[2],a[0]-d[0],a[1]-d[1],a[2]-d[2]),
                   a[2]+normal(2,a[0]-c[0],a[1]-c[1],a[2]-c[2],a[0]-d[0],a[1]-d[1],a[2]-d[2])
                  );
        glEnd();
        ///////////////
#endif   
        glColor3f(0.5, 0.5, 0.5);
        glBindTexture(GL_TEXTURE_2D,floortex);
        glBegin(GL_TRIANGLES);
  
  
        const GLfloat amb[]={0.3,0.3,0.3,1.0};
        const GLfloat dif[]={0.7,0.7,0.7,1.0};
        
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,dif);
        glNormal3f(-normal(0,a[0]-b[0],a[1]-b[1],a[2]-b[2],a[0]-d[0],a[1]-d[1],a[2]-d[2]),
                  -normal(1,a[0]-b[0],a[1]-b[1],a[2]-b[2],a[0]-d[0],a[1]-d[1],a[2]-d[2]),
                  -normal(2,a[0]-b[0],a[1]-b[1],a[2]-b[2],a[0]-d[0],a[1]-d[1],a[2]-d[2])
                  );
        //glNormal3f(0,0,1);
        //glColor3f(0.5, 0.5, 0.5);
        glTexCoord2d(0, 0);
        glVertex3f(a[0],a[1],a[2]);
        //glVertex3f(b[0], b[1], b[2]);
        glTexCoord2d(1,0);
        glVertex3f(b[0],b[1],b[2]);
        //glVertex3f(c[0], c[1], c[2]);
        glTexCoord2d(1, 1);
        glVertex3f(d[0],d[1],d[2]);
        //glVertex3f(a[0], a[1], a[2]);
        //glTexCoord2d(0, 1);
        //glVertex3f(c[0],c[1],c[2]);
        //glVertex3f(d[0], d[1], d[2]);
  
        glNormal3f(normal(0,a[0]-c[0],a[1]-c[1],a[2]-c[2],a[0]-d[0],a[1]-d[1],a[2]-d[2]),
                 normal(1,a[0]-c[0],a[1]-c[1],a[2]-c[2],a[0]-d[0],a[1]-d[1],a[2]-d[2]),
                  normal(2,a[0]-c[0],a[1]-c[1],a[2]-c[2],a[0]-d[0],a[1]-d[1],a[2]-d[2])
                  );
        glTexCoord2d(0, 0);
        glVertex3f(a[0],a[1],a[2]);
        //glVertex3f(b[0], b[1], b[2]);
        glTexCoord2d(0,1);
        glVertex3f(c[0],c[1],c[2]);
        //glVertex3f(c[0], c[1], c[2]);
        glTexCoord2d(1, 1);
        glVertex3f(d[0],d[1],d[2]);

        glEnd();
        glPopMatrix();
      
        
        //dsDrawTriangle( pReal, RReal, a, c, b, 1 );
        //dsDrawTriangle( pReal, RReal, b, c, d, 1 );
      }
    }
  }
  
}

void WorldPhysics::drawBulldozer() {

  bulldozer->render();
  bulldozer_cabin->render();
  bulldozer_bucket_c->render();
  bulldozer_bucket_l->render();
  bulldozer_bucket_r->render();
  for (int i=0;i<4;i++) {
    wheels[i]->render();
  }
}

const dReal* WorldPhysics::getBulldozerPosition() {
  return dBodyGetPosition(bulldozer->body);
}

const dReal* WorldPhysics::getBulldozerRotation() {
  return dBodyGetRotation(bulldozer->body);
}


Item* WorldPhysics::generateItem() {
  Item* temp;

  switch (qrand()%3) {
    case 0: {
      temp=new BoxItem(world,space,3,3,3,.2);
    } break;
    case 1: {
      dQuaternion q;
      dQFromAxisAndAngle(q,1,0,0,M_PI*0.5);
      temp = new WheelItem(world,space,q,2,.2);
    } break;
    case 2: {
      if (enable_complex) temp=new ComplexItem(world,space,3,3,3,.2);
        else temp=new BoxItem(world,space,3,3,3,.3);
    } break;
  }
  temp->state=0;
  temp->setPosition(qrand()%30+50,qrand()%30+50,qrand()%30+10);
  return temp;
}

dReal WorldPhysics::heightfield_callback( int x, int y )
{
  dIASSERT( x < HFIELD_WSTEP );
  dIASSERT( y < HFIELD_DSTEP );

  dReal fx = ( ((dReal)x) - ( HFIELD_WSTEP-1 )/2 ) / (dReal)( HFIELD_WSTEP-1 );
  dReal fy = ( ((dReal)y) - ( HFIELD_DSTEP-1 )/2 ) / (dReal)( HFIELD_DSTEP-1 );

	// Create an interesting 'hump' shape
  dReal h = //sin(x*y/100.0);
  REAL( 1.0 ) + ( REAL( -16.0 ) * ( fx*fx*fx + fy*fy*fy ) );


  //h=h>0?h:-h;

  if ((x>=35) && (y>=35)) {
  return (5*h+70 -1*(x+y));
  }
  else 
    return //(y/2.0)
        5*h
      //5*sin(5*x);
        ;
}

void WorldPhysics::AI() {
  if (tmp_wait>0) {tmp_wait--;return;}
  if (bulldozer_state==8) speed=0;
  
  const dReal* BPosition=bulldozer->getPosition();
//  const dReal* BRotation=bulldozer->getRotation();
  dReal minDistance=150; //~100 * sqrt(2)

  Item* tmp;
  int currentItemN=-1;
  if (items.size()==0) return;
  for (int i=0;i<items.size();i++) {
    const dReal* ItemPosition=items[i]->getPosition();
    if (ItemPosition[2]<0) items[i]->state=2;
    if (items[i]->state==2) continue;
    if (items[i]->state==1) {currentItemN=i;break;}
    if (items[i]->state==0) {
      dReal tmpmin=sqrt((ItemPosition[0]-BPosition[0])*
            (ItemPosition[0]-BPosition[0]) + 
            (ItemPosition[1]-BPosition[1])*
            (ItemPosition[1]-BPosition[1]));
      if (tmpmin<minDistance) {
        minDistance=tmpmin;
        currentItemN=i;
      }
    }
  }
  if (currentItemN==-1) {
    //bulldozer_state=0;
    generateItems();
    return;
  }
  /*
  for (int i=0;i<items.size();i++) {
    const dReal* tmp_pos=items[i]->getPosition();
    if (tmp_pos[2]<0) items[i]->state=2;

    if (items[i]->state==1) {
      currentItemN=i;
      break;
    }
    if (items[i]->state==2) currentItemN++;
  }
  if (currentItemN>=items.size()) return;
  */
  tmp=items[currentItemN];
  const dReal* ItemPosition=tmp->getPosition();
  switch (tmp->state) {
    case 0: { // Выбрали нужный кубик
      tmp->state=1;
      bulldozer_state=1; // Поворот до кубика
    } break;
    case 1: {  // Надо к нему подъехать
    switch (bulldozer_state) {
        
        case 1:{
          speed=0;
          if (RotateTo(ItemPosition[0]-BPosition[0],ItemPosition[1]-BPosition[1])) bulldozer_state=2;
        } break;
        
        case 2: {
          if (RotateTo(ItemPosition[0]-BPosition[0],ItemPosition[1]-BPosition[1])) {
            speed=3;
            if (((ItemPosition[0]-BPosition[0])*
              (ItemPosition[0]-BPosition[0]) + 
              (ItemPosition[1]-BPosition[1])*
              (ItemPosition[1]-BPosition[1]))<50) {
              speed=0;
              bulldozer_state=3;
              }
                
          } else {
            speed=0;
            bulldozer_state=1;
          }
        } break;
        case 3: {
          cheat_joint=dJointCreateSlider(world,0);
          dJointAttach(cheat_joint,bulldozer->body,tmp->body);
          dJointSetSliderAxis(cheat_joint,0,0,1);
          //dJointSetSliderParam (cheat_joint, dParamCFM, 0.5);
          bulldozer_state=4;
        }break;
        case 4: {
          if (RotateTo(100-BPosition[0],0-BPosition[1])) bulldozer_state=5;
        }break;
        case 5: {
          if (RotateTo(100-BPosition[0],0-BPosition[1])) {
            speed=3;
            if (sqrt((100-BPosition[0])*
                  (100-BPosition[0]) + 
                  (0-BPosition[1])*
                  (0-BPosition[1]))<(sqrt(2)*25+LENGTH/2+RADIUS)) {
              speed=0;
              bulldozer_state=6;
                  }
                
          } else {
            speed=0;
            bulldozer_state=4;
          }
        } break;
        
      case 6: {
        dJointDestroy(cheat_joint);
        dBodyAddForce(tmp->body,100-BPosition[0],0-BPosition[1], 5);
        bulldozer_state=7;
      } break;
      case 7: {
        speed=-10;
        tmp_wait=70;
        bulldozer_state=8;
      } break;
      case 8: {
        speed=0;
        tmp->state=2;
      } break;
        
      
      
      
      }
    } break;
  }
  
}

int WorldPhysics::RotateTo(dReal directionx, dReal directiony) {
//  const dReal* BPosition=bulldozer->getPosition();
  const dReal* BRotation=bulldozer->getRotation();

  dReal brot[2];

  dReal path[2];
  path[0]=directionx;
  path[1]=directiony;
      
  dReal norm=sqrt(path[0]*path[0]+path[1]*path[1]);
  path[0]=path[0]/norm;
  path[1]=path[1]/norm;
      
  norm=sqrt(BRotation[0]*BRotation[0]+BRotation[1]*BRotation[1]);
  brot[0]=BRotation[0]/norm;
  brot[1]=-BRotation[1]/norm;
      
      
  //dReal cur_scalar=path[0]*brot[0]+
    //  path[1]*brot[1];
      
  dReal cur_scalar=path[0]*brot[0]+
      path[1]*brot[1];
      
  if (cur_scalar>.99) {
    dspeed=0;
    return 1;
  } else {
    cur_scalar=path[0]*brot[1]-
        path[1]*brot[0];
    if (cur_scalar>0) dspeed=2; else dspeed=-2;
  //  dspeed =2;
  }
  /*
  if (cur_scalar<=tmp_scalar) {
    dspeed=-dspeed;
        //sleep(1);
    tmp_wait=10;
  }
  tmp_scalar=cur_scalar;*/
  return 0;
}

void WorldPhysics::generateItems() {
  if (!items.empty()) {
    for (int  i=0;i<items.size();i++) {
      delete items[i];
    }
    items.clear();
  }
  for (int  i=0;i<MAX_ITEMS;i++) {
    items.push_back(generateItem());
  }
}

dReal WorldPhysics::normal(int XYZ,dReal x1,dReal y1,dReal z1,
                                   dReal x2,dReal y2,dReal z2) {
  switch (XYZ) {
    case 0: {
      return (y1*z2-y2*z1);
    } break;
    case 1: {
      return -(x1*z2-x2*z1);
          //((x1*z2-x2*z1)>0)?(x1*z2-x2*z1):-(x1*z2-x2*z1);
    } break;
    case 2: {
      return (x1*y2-x2*y1);
    } break;
    default: exit(1);
  }
}
