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
#ifndef DSPSOUND_H
#define DSPSOUND_H

#include <QObject>
#include "FftWrapper.h"
#include "dspFftData.h"

class QFile;

class dspSound : public QObject {

  Q_OBJECT

  public:
    dspSound();
    virtual ~dspSound();
    void loadFromFile(const QString& fileName);
    void saveToFile(const QString& fileName);

    int getK();
    void setK(int kvalue);

    double getCut();
    void setCut(double cutvalue);

    int getFftSize();
    void setFftSize(int fftvalue);

    dspFftData* fftDrawData;
  public slots:
    void processSignal();
    void buildFFT(int length,int windowSize);
  signals:
    void sendLogMessage(QString Message, int IsError);
  private:
    void writeToLog(QString Message, int IsError=0);
    quint16 getInt16(QByteArray array, int offset);
    quint32 getInt32(QByteArray array, int offset);

    Fft *fft;
    QFile *wavFile;
    QByteArray *data;
    QByteArray *riffHeader;

    int k;
    double cut;

    int BitsPerSample;
    int NumChannels;
    int SampleRate;
    int DataSize;
    int Nsamples;

    int fftSize;
};

#endif
