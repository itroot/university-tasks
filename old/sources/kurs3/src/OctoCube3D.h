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

#ifndef OCTOCUBE3D_H
#define OCTOCUBE3D_H

#include "Cube3D.h"
#include <QVector>

  //! Структура компактно описывающая диагонали октокуба.
struct OctoDiags {
  /*!
   * Кодирует 24 битами внешние грани куба.
   * Кодирование осуществлется блоками по 4 бита (для каждой грани октокуба)
   * Старшие 8 бит 32-битного числа не используются - они зарезервированы.
   * [] - блок из четырех бит.
   * [резерв][резерв][z=1][y=1][x=1][z=0][y=0][x=0]
   * Каждый блок содержит информцию о диагнолях в четырех гранях кубов, 
   * входящих в грань октокуб в соотвествие с системой координат.
   */
  quint32 externalFaces;
    /*!
   * То же что и для externalFaces;
   * [резерв][z][y][z]
     */
  quint16 internalFaces;
};


class OctoCube3D {
  public:
    OctoCube3D();
    // ~OctoCube3D(); Написать деструктор!
    //! Рисуем октокуб (8 кубиков)
    void drawGL();
    //! Получить бит из keeper на позиции position
    static inline int getBinaryDigit16(quint16 keeper, int position);
    static inline int getBinaryDigit32(quint32 keeper, int position);
    static inline void setBinaryDigit16(quint16 &keeper, int position, int value);
    static inline void setBinaryDigit32(quint32 &keeper, int position, int value);

    OctoDiags getOctoDiags();
    int getCubeDiags(int x, int y, int z);
    void setVisible(bool how);
    bool isVisible();
  private:
    //! Количество используемых бит в предствлении внешних граней
    static const int N_BITS_EXT=24;
    //! Количество используемых бит в предствлении внутренних граней
    static const int N_BITS_INT=12;

    //! Размер кубиков в октокубе.
    static const int CUBE_SIZE=10;
    //! смещение относительно начала координат. (Delta-Vector - DV)
    static const int CUBE_DV=1;

    void reflectionCubes2Bits();
    void reflectionBits2Cubes();


    OctoDiags octoDiags;
    bool visible;

           //xyz
    Cube3D *c000;
    Cube3D *c001;
    Cube3D *c010;
    Cube3D *c011;
    Cube3D *c100;
    Cube3D *c101;
    Cube3D *c110;
    Cube3D *c111;
    

    //! для "перебора" всех кубов.
    QVector<Cube3D*> cubes;
    //! Для упорядочивания кубов в октокубе.
    Cube3D* octoArray[2][2][2];
};

#endif /*OCTOCUBE3D_H*/
