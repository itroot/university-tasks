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

#include <GL/gl.h>
#include "Cube3D.h"


Cube3D::Cube3D() {
  x=1;
  y=1;
  z=1;
  size=10;
  setTriangulation(0);
  setVisible(true);
}

Cube3D::Cube3D(int inX, int inY, int inZ, int inSize) {
  x=inX;
  y=inY;
  z=inZ;
  size=inSize;
  setTriangulation(0);
  setVisible(true);
}

Cube3D::~Cube3D() {

}

void Cube3D::drawGL(Point3D * point){
  if (!isVisible()) return;
  glPushMatrix();
  glTranslatef(x,y,z);

  glColor3f(1.0, 1.0, 1.0);

  glBegin(GL_LINES);

  // рисуем куб
  for (int i=0;i<4;i++){
    glVertex3f(0, getBinaryDigit(i,0)*size, getBinaryDigit(i,1)*size);
    glVertex3f(size, getBinaryDigit(i,0)*size, getBinaryDigit(i,1)*size);

    glVertex3f(getBinaryDigit(i,0)*size, 0, getBinaryDigit(i,1)*size);
    glVertex3f(getBinaryDigit(i,0)*size, size, getBinaryDigit(i,1)*size);

    glVertex3f(getBinaryDigit(i,0)*size, getBinaryDigit(i,1)*size,0);
    glVertex3f(getBinaryDigit(i,0)*size, getBinaryDigit(i,1)*size,size);

  }

  // рисуем диагонали
  glColor3f(1.0, 1.0, 0.0);

  glVertex3f(0, getBinaryDigit(diags,0)*size, size);
  glVertex3f(0, (1-getBinaryDigit(diags,0))*size, 0);

  glVertex3f(size, getBinaryDigit(diags,3)*size, size);
  glVertex3f(size, (1-getBinaryDigit(diags,3))*size, 0);

  glVertex3f( getBinaryDigit(diags,1)*size, 0, size);
  glVertex3f( (1-getBinaryDigit(diags,1))*size, 0, 0);

  glVertex3f(getBinaryDigit(diags,4)*size, size, size);
  glVertex3f((1-getBinaryDigit(diags,4))*size, size, 0);

  glVertex3f(getBinaryDigit(diags,2)*size, size, 0);
  glVertex3f((1-getBinaryDigit(diags,2))*size, 0, 0);

  glVertex3f(getBinaryDigit(diags,5)*size, size, size);
  glVertex3f((1-getBinaryDigit(diags,5))*size, 0, size);

  glEnd();

  // Здесь неплохо бы нарисовать симплексы

  for (int i=0;i<simplexes.size();++i) {
    simplexes[i].drawGL(point);
  }
  glPopMatrix();
}


int Cube3D::getX() {
  return x;
}

int Cube3D::getY() {
  return y;
}

int Cube3D::getZ() {
  return z;
}

int Cube3D::getSize() {
  return size;
}

int Cube3D::getBinaryDigit(int keeper, int position) {
  return (keeper>>position)%2;
}

int Cube3D::getVertexPower(int x, int y, int z) {
  return vertexPower[x+2*y+4*z];
}

void Cube3D::raiseVertexPower(int x, int y, int z) {
  vertexPower[x+2*y+4*z]++;
}

void Cube3D::setTriangulation(int diagonals) {
  if (diagonals>=64) diagonals=0;
  if ((diagonals<0)) diagonals=63;

  diags=diagonals;

  clearVertexPowers();

  raiseVertexPower(0, getBinaryDigit(diags,0), 1);
  raiseVertexPower(0, 1-getBinaryDigit(diags,0), 0);

  raiseVertexPower(1, getBinaryDigit(diags,3), 1);
  raiseVertexPower(1, 1-getBinaryDigit(diags,3), 0);

  raiseVertexPower( getBinaryDigit(diags,1), 0, 1);
  raiseVertexPower( 1-getBinaryDigit(diags,1), 0, 0);

  raiseVertexPower(getBinaryDigit(diags,4), 1, 1);
  raiseVertexPower(1-getBinaryDigit(diags,4), 1, 0);

  raiseVertexPower(getBinaryDigit(diags,2), 1, 0);
  raiseVertexPower(1-getBinaryDigit(diags,2), 0, 0);

  raiseVertexPower(getBinaryDigit(diags,5), 1, 1);
  raiseVertexPower((1-getBinaryDigit(diags,5)), 0, 1);

  for(int i=0;i<8;++i) {
    ++indexOfTriangulation[vertexPower[i]];
  }
  createSimplexes(diagonals);
}


void Cube3D::clearVertexPowers() {
  for (int i=0;i<8;++i) {
    vertexPower[i]=0;
  }
  for(int i=0;i<4;++i) {
    indexOfTriangulation[i]=0;
  }
}

int Cube3D::getNumberOfPower(int i) {
  if ((i>=0) && (i<4)) return indexOfTriangulation[i];
  return 0;
}

int Cube3D::getTriangulation(void) {
  return diags;
}

TypeOfTriangulation Cube3D::getT_ofTriangulation() {
  int tmpT[4]={0};
  for(int i=0;i<4;++i) {
    tmpT[i]=getNumberOfPower(i);
  }
  
  if ((tmpT[0]==0) && (tmpT[1]==4) && (tmpT[2]==4) && (tmpT[3]==0)) return T_0440;
  if ((tmpT[0]==0) && (tmpT[1]==6) && (tmpT[2]==0) && (tmpT[3]==2)) return T_0602;
  if ((tmpT[0]==1) && (tmpT[1]==3) && (tmpT[2]==3) && (tmpT[3]==1)) return T_1331;
  if ((tmpT[0]==2) && (tmpT[1]==0) && (tmpT[2]==6) && (tmpT[3]==0)) return T_2060;
  if ((tmpT[0]==2) && (tmpT[1]==2) && (tmpT[2]==2) && (tmpT[3]==2)) return T_2222;
  if ((tmpT[0]==4) && (tmpT[1]==0) && (tmpT[2]==0) && (tmpT[3]==4)) return T_4004;

  // Есл мы тут, то что-то не в порядке.
  return T_UNKNOWN;
}

bool Cube3D::isVisible() {
  return visible;
}

void Cube3D::setVisible(bool how) {
  visible=how;
}

void Cube3D::createSimplexes(int diagonals) {
  simplexes.clear();
  if (diagonals==7) { // 000111 - пятый тип.
    simplexes.append(Simplex3D(Point3D(0,0,0),Point3D(1,0,0),Point3D(1,0,1),Point3D(1,1,0),size));
    simplexes.append(Simplex3D(Point3D(0,0,0),Point3D(0,1,0),Point3D(0,1,1),Point3D(1,1,0),size));
    simplexes.append(Simplex3D(Point3D(0,0,0),Point3D(0,0,1),Point3D(0,1,1),Point3D(1,0,1),size));
    simplexes.append(Simplex3D(Point3D(1,0,1),Point3D(1,1,0),Point3D(0,1,1),Point3D(1,1,1),size));
    simplexes.append(Simplex3D(Point3D(0,0,0),Point3D(1,1,0),Point3D(1,0,1),Point3D(0,1,1),size));
  }
  if (diagonals==63) { //111111 - 0602 - первый тип.
    simplexes.append(Simplex3D(Point3D(0,0,0),Point3D(1,0,0),Point3D(1,1,0),Point3D(1,1,1),size));
    simplexes.append(Simplex3D(Point3D(0,0,0),Point3D(1,0,0),Point3D(1,0,1),Point3D(1,1,1),size));
    simplexes.append(Simplex3D(Point3D(0,0,0),Point3D(0,0,1),Point3D(1,0,1),Point3D(1,1,1),size));
    simplexes.append(Simplex3D(Point3D(0,0,0),Point3D(0,1,0),Point3D(1,1,0),Point3D(1,1,1),size));
    simplexes.append(Simplex3D(Point3D(0,0,0),Point3D(0,1,0),Point3D(0,1,1),Point3D(1,1,1),size));
    simplexes.append(Simplex3D(Point3D(0,0,0),Point3D(0,1,1),Point3D(0,0,1),Point3D(1,1,1),size));
  }
  if (diagonals==0) { // Не учитывается главная диагональ!
    simplexes.append(Simplex3D(Point3D(0,0,0),Point3D(1,0,0),Point3D(0,1,0),Point3D(0,0,1),size));
    simplexes.append(Simplex3D(Point3D(1,1,1),Point3D(0,1,1),Point3D(1,0,1),Point3D(1,1,0),size));
    simplexes.append(Simplex3D(Point3D(0,0,1),Point3D(1,0,1),Point3D(0,1,1),Point3D(1,1,0),size));
    simplexes.append(Simplex3D(Point3D(0,0,1),Point3D(1,0,0),Point3D(0,1,0),Point3D(1,1,0),size));
    simplexes.append(Simplex3D(Point3D(0,0,1),Point3D(1,1,0),Point3D(1,0,1),Point3D(1,0,0),size));
    simplexes.append(Simplex3D(Point3D(0,0,1),Point3D(1,1,0),Point3D(0,1,1),Point3D(0,1,0),size));
  }
  
  if (diagonals==1) {  // 1331 не учитывается главная диагональ!!!
    simplexes.append(Simplex3D(Point3D(1,1,1),Point3D(0,1,1),Point3D(1,0,1),Point3D(1,1,0),size));
    simplexes.append(Simplex3D(Point3D(0,0,0),Point3D(0,0,1),Point3D(1,0,0),Point3D(0,1,1),size));
    simplexes.append(Simplex3D(Point3D(0,0,0),Point3D(0,1,0),Point3D(0,1,1),Point3D(1,0,0),size));
    simplexes.append(Simplex3D(Point3D(1,0,0),Point3D(0,0,1),Point3D(0,1,1),Point3D(1,0,1),size));
    // Главная диагональ.
    //simplexes.append(Simplex3D(Point3D(1,0,0),Point3D(0,1,1),Point3D(1,0,1),Point3D(1,1,0),size));
    //simplexes.append(Simplex3D(Point3D(1,0,0),Point3D(1,1,0),Point3D(0,1,1),Point3D(0,1,0),size));
  }
  
  if (diagonals==3) { //2222 не учитывая главной диагонали.
    simplexes.append(Simplex3D(Point3D(0,0,0),Point3D(0,0,1),Point3D(0,1,1),Point3D(1,0,1),size));
    simplexes.append(Simplex3D(Point3D(1,1,1),Point3D(0,1,1),Point3D(1,0,1),Point3D(1,1,0),size));
    // Главная диагональ.
    simplexes.append(Simplex3D(Point3D(0,1,1),Point3D(1,0,1),Point3D(1,0,0),Point3D(1,1,0),size));
    simplexes.append(Simplex3D(Point3D(0,1,1),Point3D(1,0,1),Point3D(1,0,0),Point3D(0,0,0),size));
    simplexes.append(Simplex3D(Point3D(1,0,0),Point3D(0,1,1),Point3D(0,1,0),Point3D(1,1,0),size));
    simplexes.append(Simplex3D(Point3D(1,0,0),Point3D(0,1,1),Point3D(0,1,0),Point3D(0,0,0),size));
  }
}
