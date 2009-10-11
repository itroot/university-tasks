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

#include "OctoCube3D.h"

////
#include<QtCore>



OctoCube3D::OctoCube3D() {
  c000=new Cube3D(CUBE_DV,CUBE_DV,CUBE_DV,CUBE_SIZE);
  c001=new Cube3D(CUBE_DV,CUBE_DV,CUBE_DV+CUBE_SIZE,CUBE_SIZE);
  c010=new Cube3D(CUBE_DV,CUBE_DV+CUBE_SIZE,CUBE_DV,CUBE_SIZE);
  c011=new Cube3D(CUBE_DV,CUBE_DV+CUBE_SIZE,CUBE_DV+CUBE_SIZE,CUBE_SIZE);
  c100=new Cube3D(CUBE_DV+CUBE_SIZE,CUBE_DV,CUBE_DV,CUBE_SIZE);
  c101=new Cube3D(CUBE_DV+CUBE_SIZE,CUBE_DV,CUBE_DV+CUBE_SIZE,CUBE_SIZE);
  c110=new Cube3D(CUBE_DV+CUBE_SIZE,CUBE_DV+CUBE_SIZE,CUBE_DV,CUBE_SIZE);
  c111=new Cube3D(CUBE_DV+CUBE_SIZE,CUBE_DV+CUBE_SIZE,CUBE_DV+CUBE_SIZE,CUBE_SIZE);

  cubes.append(c000);
  cubes.append(c001);
  cubes.append(c010);
  cubes.append(c011);
  cubes.append(c100);
  cubes.append(c101);
  cubes.append(c110);
  cubes.append(c111);
  
  octoArray[0][0][0]=c000;
  octoArray[0][0][1]=c001;
  octoArray[0][1][0]=c010;
  octoArray[0][1][1]=c011;
  octoArray[1][0][0]=c100;
  octoArray[1][0][1]=c101;
  octoArray[1][1][0]=c110;
  octoArray[1][1][1]=c111;

  // У всех кубов diags==0;
  // Поэтому начальное значение заданов верно. Хотя лучше синхронизировать.
  octoDiags.externalFaces=0xffffff;
  octoDiags.internalFaces=0xfff;
  //reflectionBits2Cubes();
  reflectionCubes2Bits();
  ///////////
  /*
  QFile statsFile(QString("/home/ivan/readme.txt"));
  if (!statsFile.open(QIODevice::WriteOnly | QIODevice::Text)) return;
  QTextStream out(&statsFile);

  quint32 tmp=1;
  for (int i=0; i<24; ++i) {
    octoDiags.externalFaces=tmp;
    reflectionBits2Cubes();
    out << QString("%1 %2 ")
        .arg(octoDiags.internalFaces,12,2,QLatin1Char('0'))
        .arg(octoDiags.externalFaces,24,2,QLatin1Char('0'));

    out << QString("xyz %1 ").arg(getCubeDiags(0,0,0),6,2,QLatin1Char('0'));
    out << QString("xyZ %1 ").arg(getCubeDiags(0,0,1),6,2,QLatin1Char('0'));
    out << QString("xYz %1 ").arg(getCubeDiags(0,1,0),6,2,QLatin1Char('0'));
    out << QString("xYZ %1 ").arg(getCubeDiags(0,1,1),6,2,QLatin1Char('0'));
    out << QString("Xyz %1 ").arg(getCubeDiags(1,0,0),6,2,QLatin1Char('0'));
    out << QString("XyZ %1 ").arg(getCubeDiags(1,0,1),6,2,QLatin1Char('0'));
    out << QString("XYz %1 ").arg(getCubeDiags(1,1,0),6,2,QLatin1Char('0'));
    out << QString("XYZ %1 ").arg(getCubeDiags(1,1,1),6,2,QLatin1Char('0'));
    out << endl;
    tmp<<=1;
  }
  octoDiags.externalFaces=0;
  tmp=1;
  
  for (int i=0; i<12; ++i) {
    octoDiags.internalFaces=tmp;
    reflectionBits2Cubes();
    out << QString("%1 %2 ")
        .arg(octoDiags.internalFaces,12,2,QLatin1Char('0'))
        .arg(octoDiags.externalFaces,24,2,QLatin1Char('0'));

    out << QString("xyz %1 ").arg(getCubeDiags(0,0,0),6,2,QLatin1Char('0'));
    out << QString("xyZ %1 ").arg(getCubeDiags(0,0,1),6,2,QLatin1Char('0'));
    out << QString("xYz %1 ").arg(getCubeDiags(0,1,0),6,2,QLatin1Char('0'));
    out << QString("xYZ %1 ").arg(getCubeDiags(0,1,1),6,2,QLatin1Char('0'));
    out << QString("Xyz %1 ").arg(getCubeDiags(1,0,0),6,2,QLatin1Char('0'));
    out << QString("XyZ %1 ").arg(getCubeDiags(1,0,1),6,2,QLatin1Char('0'));
    out << QString("XYz %1 ").arg(getCubeDiags(1,1,0),6,2,QLatin1Char('0'));
    out << QString("XYZ %1 ").arg(getCubeDiags(1,1,1),6,2,QLatin1Char('0'));
    out << endl;
    tmp<<=1;
  }
  statsFile.close();
  
  ////////
  
  QFile statsFile(QString("/home/ivan/readme.txt"));
  if (!statsFile.open(QIODevice::WriteOnly | QIODevice::Text)) return;
  QTextStream out(&statsFile);

  quint32 tmp=1;
  for (int i=0; i<24; ++i) {
    octoDiags.externalFaces=tmp;
    reflectionBits2Cubes();
    //out << QString("externalFaces[%1][0]=%2;").arg(i).arg(octoDiags.externalFaces)<<endl;

    out << QString("externalFaces[%1][0]=%2;").arg(i).arg(getCubeDiags(0,0,0))<<endl;
    out << QString("externalFaces[%1][1]=%2;").arg(i).arg(getCubeDiags(0,0,1))<<endl;
    out << QString("externalFaces[%1][2]=%2;").arg(i).arg(getCubeDiags(0,1,0))<<endl;
    out << QString("externalFaces[%1][3]=%2;").arg(i).arg(getCubeDiags(0,1,1))<<endl;
    out << QString("externalFaces[%1][4]=%2;").arg(i).arg(getCubeDiags(1,0,0))<<endl;
    out << QString("externalFaces[%1][5]=%2;").arg(i).arg(getCubeDiags(1,0,1))<<endl;
    out << QString("externalFaces[%1][6]=%2;").arg(i).arg(getCubeDiags(1,1,0))<<endl;
    out << QString("externalFaces[%1][7]=%2;").arg(i).arg(getCubeDiags(1,1,1))<<endl;
    out << endl;
    tmp<<=1;
  }
  octoDiags.externalFaces=0;
  tmp=1;
  
  for (int i=0; i<12; ++i) {
    octoDiags.internalFaces=tmp;
    reflectionBits2Cubes();
    //out << QString("internalFaces[%1][0]=%2;").arg(i).arg(octoDiags.internalFaces)<<endl;

    out << QString("internalFaces[%1][0]=%2;").arg(i).arg(getCubeDiags(0,0,0))>>endl;
    out << QString("internalFaces[%1][1]=%2;").arg(i).arg(getCubeDiags(0,0,1))>>endl;
    out << QString("internalFaces[%1][2]=%2;").arg(i).arg(getCubeDiags(0,1,0))>>endl;
    out << QString("internalFaces[%1][3]=%2;").arg(i).arg(getCubeDiags(0,1,1))>>endl;
    out << QString("internalFaces[%1][4]=%2;").arg(i).arg(getCubeDiags(1,0,0))>>endl;
    out << QString("internalFaces[%1][5]=%2;").arg(i).arg(getCubeDiags(1,0,1))>>endl;
    out << QString("internalFaces[%1][6]=%2;").arg(i).arg(getCubeDiags(1,1,0))>>endl;
    out << QString("internalFaces[%1][7]=%2;").arg(i).arg(getCubeDiags(1,1,1))>>endl;
    out << endl;
    tmp<<=1;
  }
  statsFile.close();
  */
  setVisible(true);
}

void OctoCube3D::drawGL() {
  if (!isVisible()) return;
  for (int x=0;x<=1;++x) {
    for (int y=0;y<=1;++y) {
      for (int z=0;z<=1;++z) {
        Point3D tmp=Point3D(1-x,1-y,1-z);
        octoArray[x][y][z]->drawGL(&tmp);
      }
    }
  }
  //for (int i=0;i<cubes.size();++i) {
  //        cubes.at(i)->drawGL();
  //}
}

void OctoCube3D::reflectionCubes2Bits() {
  for (int x=0;x<=1;++x) {
    for (int y=0;y<=1;++y) {
      for (int z=0;z<=1;++z) {

        // Внешние грани.
        setBinaryDigit32(octoDiags.externalFaces,
                         12*x+2*z+y,
                         Cube3D::getBinaryDigit(octoArray[x][y][z]->getTriangulation(),
                                                3*z)
                        );

        setBinaryDigit32(octoDiags.externalFaces,
                         4+12*x+2*z+y,
                         Cube3D::getBinaryDigit(octoArray[x][y][z]->getTriangulation(),
                                               3*y+1)
                        );

        setBinaryDigit32(octoDiags.externalFaces,
                         8+12*x+2*z+y,
                         Cube3D::getBinaryDigit(octoArray[x][y][z]->getTriangulation(),
                                                3*x+2)
                        );

        setBinaryDigit16(octoDiags.internalFaces,
                         2*z+y,
                         Cube3D::getBinaryDigit(octoArray[x][y][z]->getTriangulation(),
                                                3*(1-z))
                        );

        setBinaryDigit16(octoDiags.internalFaces,
                         4+2*z+x,
                         Cube3D::getBinaryDigit(octoArray[x][y][z]->getTriangulation(),
                                                3*(1-y)+1)
                        );

        setBinaryDigit16(octoDiags.internalFaces,
                         8+2*y+x,
                         Cube3D::getBinaryDigit(octoArray[x][y][z]->getTriangulation(),
                                                3*(1-x)+2)
                        );

      }
    }
  }
}

void OctoCube3D::reflectionBits2Cubes() {
  // x y z - координаты куба в октокубе.
  for (int x=0;x<=1;++x) {
    for (int y=0;y<=1;++y) {
      for (int z=0;z<=1;++z) {
        int diags[6]; // временное решение.
        // Внешние грани
        diags[3*x]=getBinaryDigit32(octoDiags.externalFaces,12*x+2*z+y);
        diags[3*y+1]=getBinaryDigit32(octoDiags.externalFaces,12*y+4+2*z+x);
        diags[3*z+2]=getBinaryDigit32(octoDiags.externalFaces,12*z+8+2*y+x);
        // Внутренние грани
        diags[3*(1-x)]=getBinaryDigit16(octoDiags.internalFaces,2*z+y);
        diags[3*(1-y)+1]=getBinaryDigit16(octoDiags.internalFaces,4+2*z+x);
        diags[3*(1-z)+2]=getBinaryDigit16(octoDiags.internalFaces,8+2*y+x);
        octoArray[x][y][z]->setTriangulation(diags[0]+2*diags[1]+4*diags[2]+8*diags[3]+16*diags[4]+32*diags[5]);
      }
    }
  }
}

int OctoCube3D::getBinaryDigit16(quint16 keeper, int position) {
  return (keeper>>position)%2;
}

int OctoCube3D::getBinaryDigit32(quint32 keeper, int position) {
  return (keeper>>position)%2;
}

void OctoCube3D::setBinaryDigit16(quint16 &keeper, int position, int value) {
  quint16 tmp=1;
  tmp<<=position;
  if (value) {
    keeper|=tmp;
  } else {
    keeper&=!tmp;
  }
}

void OctoCube3D::setBinaryDigit32(quint32 &keeper, int position, int value) {
  quint32 tmp=1;
  tmp<<=position;
  if (value) {
    keeper|=tmp;
  } else {
    keeper&=!tmp;
  }
}

OctoDiags OctoCube3D::getOctoDiags() {
  return octoDiags;
}

int OctoCube3D::getCubeDiags(int x, int y, int z) {
  return octoArray[x][y][z]->getTriangulation();
}

void OctoCube3D::setVisible(bool how) {
  visible=how;
  for (int i=0;i<cubes.size();++i) {
    cubes[i]->setVisible(how);
  }
}

bool OctoCube3D::isVisible() {
  return visible;
}
