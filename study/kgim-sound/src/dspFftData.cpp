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

#include "dspFftData.h"
#include <QtCore>

dspFftData::dspFftData() {
  ready=0;
  currentFftWindowSize=1024;
}

void dspFftData::createFftData(int length, int windowSize) {
  fftData.fill(QVector<audio_real>(windowSize),length);
  ready=1;
}

void dspFftData::addFftWindow(int col,audio_real* fft) {
  int halfWindowSize=fftData[col].size()>>1;
  audio_real* currentCol=fftData[col].data();
  for(int i=0;i<halfWindowSize;++i) {
    currentCol[i]=fft[i];
  }
}
