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

#include <QtGui>
#include "dspSpectrogram.h"

dspSpectrogram::dspSpectrogram (QWidget *parent):QWidget(parent) {
  //QTimer *timer = new QTimer(this);
  //connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  //timer->start(1000);
  dataSpectr=0;
}

void dspSpectrogram::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  if (dataSpectr==0) {
    painter.drawText(rect(), Qt::AlignCenter,tr("No data avaible to build a spectrogram."));
  } else 
  if (!dataSpectr->ready) {
    painter.drawText(rect(), Qt::AlignCenter,tr("Spectrogram is not loaded."));
  } else
  {
    QVector<QVector<audio_real> >* tmpdata=&dataSpectr->fftData;
    for (int i=0;i<width();++i) {
      const QVector<audio_real> *tmpdatai=&tmpdata->at(i);
      for (int j=0;j<height();++j) {
        painter.setPen(QPen(QColor(tmpdatai->at(j))));
        painter.drawPoint(i,j);
      }
    }
  }
}

void dspSpectrogram::resizeEvent(QResizeEvent *event) {
  if (event->size().width()!=event->oldSize().width() ||
      event->size().height()!=event->oldSize().height()) {
    emit sizeChanged(width(),height());
  }
}

void dspSpectrogram::setSpectr(dspFftData * spectr){
  dataSpectr=spectr;
}

