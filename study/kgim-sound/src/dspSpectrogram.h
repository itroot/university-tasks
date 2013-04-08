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

#ifndef DSPSPECTROGRAM_H
#define DSPSPECTROGRAM_H

#include "FftWrapper.h"
#include "dspFftData.h"
#include <QWidget>
#include <QImage>



class dspSpectrogram : public QWidget {

  Q_OBJECT
  public:
    dspSpectrogram(QWidget *parent=0);
    void setSpectr(dspFftData * spectr);
  signals:
    void sizeChanged(int length,int width);
  protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
  private:
    dspFftData * dataSpectr;
};

#endif
