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

#include "Point3D.h"
#include <math.h>

Point3D::Point3D() {
  xCoord=0;
  yCoord=0;
  zCoord=0;
}

Point3D::Point3D(double x, double y, double z) {
  xCoord=x;
  yCoord=y;
  zCoord=z;
}

Point3D::~Point3D() {

}

double Point3D::x() const {
  return xCoord;
}

double Point3D::y() const {
  return yCoord;
}

double Point3D::z() const {
  return zCoord;
}

const Point3D operator+(const Point3D& lhs,const Point3D& rhs) {
  return Point3D(lhs.x()+rhs.x(),lhs.y()+rhs.y(),lhs.z()+rhs.z());
}

const Point3D operator-(const Point3D& lhs,const Point3D& rhs) {
  return Point3D(lhs.x()-rhs.x(),lhs.y()-rhs.y(),lhs.z()-rhs.z());
}

const Point3D operator*(const Point3D& lhs,const Point3D& rhs) {
  return Point3D(
                 lhs.y()*rhs.z()-rhs.y()*lhs.z(),
                 rhs.x()*lhs.z()-lhs.x()*rhs.z(),
                 lhs.x()*rhs.y()-rhs.x()*lhs.y()
                );
}

const Point3D operator*(const Point3D& lhs, const double rhs) {
  return Point3D(lhs.x()*rhs,lhs.y()*rhs,lhs.z()*rhs);
}


const double operator&(const Point3D& lhs,const Point3D& rhs) {
  return lhs.x()*rhs.x()+lhs.y()*rhs.y()+lhs.z()*rhs.z();
}


const Point3D operator/(const Point3D& lhs, const double rhs) {
  return Point3D(lhs.x()/rhs,lhs.y()/rhs,lhs.z()/rhs);
}

const Point3D Point3D::operator-() {
  return Point3D(-this->x(),-this->y(),-this->z());;
}

double Point3D::abs() {
  return sqrt(this->x()*this->x()+this->y()*this->y()+this->z()*this->z());
}
