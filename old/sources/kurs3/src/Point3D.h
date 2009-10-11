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
#ifndef POINT3D_H
#define POINT3D_H

class Point3D {
  public:
    Point3D();
    Point3D(double x,double y,double z);
    friend const Point3D operator+(const Point3D& lhs, const Point3D& rhs);
    friend const Point3D operator-(const Point3D& lhs, const Point3D& rhs);
    //! Векторное умножение.
    friend const Point3D operator*(const Point3D& lhs, const Point3D& rhs);
    friend const Point3D operator*(const Point3D& lhs, const double rhs);
    friend const Point3D operator/(const Point3D& lhs, const double rhs);
    //! скалярное произведение.
    friend const double operator&(const Point3D& lhs,const Point3D& rhs);
    const Point3D operator-();
    double x()const;
    double y()const;
    double z()const;
    double abs();
    ~Point3D();
  private:
    double xCoord;
    double yCoord;
    double zCoord;
};

#endif
