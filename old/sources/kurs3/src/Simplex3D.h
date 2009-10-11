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

#ifndef SIMPLEX3D_H
#define SIMPLEX3D_H

#include "Point3D.h"

class Simplex3D {
  public:
    Simplex3D(Point3D p1, Point3D p2, Point3D p3, Point3D p4, int scale);

    void drawGL(Point3D * point=0);
  private:
    void drawTriangle(Point3D *p1, Point3D *p2, Point3D *p3);

    double size;

    Point3D *point1;
    Point3D *point2;
    Point3D *point3;
    Point3D *point4;
};

#endif

