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


#ifndef CUBE3D_H
#define CUBE3D_H

#include <vector>
#include "Simplex3D.h"
#include <QList>



//! Тип триангуляции.
enum TypeOfTriangulation {
    T_0440, // Неправильный тип, все остальные правильные.
    T_0602, 
    T_1331,
    T_2060,
    T_2222,
    T_4004,
    T_UNKNOWN // Для отслеживания ошибок.
};

class Cube3D {

  public:
    Cube3D();
    Cube3D(int inX, int inY, int inZ, int inSize=10 );
    ~Cube3D();

    //! рисует кубик и диагонали
    void drawGL(Point3D * point=0);

    //! X - координата куба
    int getX();
    //! Y - координата куба
    int getY();
    //! Z - координата куба
    int getZ();
    //! Размер куба
    int getSize();
    //! Возвращает бит в двоичном представлении числа keeper в позиции position
    static int getBinaryDigit(int keeper, int position);
    //! Возвращает мощность вершины - количество проходящих через нее диагоналей
    int getVertexPower(int x, int y, int z);
    //! Задает тип триангуляции(битовое представление диагоналей).
    void setTriangulation(int diagonals);
    //! Возвращает значение триангуляции(битовый формат).
    int getTriangulation(void);
    //! Возвращает тип триангуляции в виде enum.
    TypeOfTriangulation getT_ofTriangulation();
    //! Возвращает количество вершин в кубе с мощностью i.
    int getNumberOfPower(int i/*i=0,1,2,3*/);
    
    bool isVisible();
    void setVisible(bool how);

  private:

    void createSimplexes(int diagonals);

    //! Список симплексов.
    QList<Simplex3D> simplexes;
    //! Увеличивает мощность вершины на 1
    void raiseVertexPower(int x, int y, int z);
    //! Очищает мощности вершин.
    void clearVertexPowers();

    int x;
    int y;
    int z;
    int size;

    int vertexPower[8];
    int indexOfTriangulation[4];

    /*! 0 0 z=1 y=1 x=1 z=0 y=0 x=0
    *   биты означают ориентацию диагоналей в каждой из плоскостей
    *   1- направлена в "большую сторону" (разница сумм координат противоположных вершин максимальна)
    *   0- направлена в "меньшую сторону" (разница сумм координат противоположных вершин максимальна)
    */
    int diags;
    bool visible;
};

#endif
