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

#include "dspSound.h"
#include <QtCore>
#include <cmath>

dspSound::dspSound() {
  wavFile=0;
  data=0;
  riffHeader=0;
  fft=new Fft();
  fftSize=2048;
  fftDrawData= new dspFftData();
  k=8000;
  cut=0.1;
}

dspSound::~dspSound() {

}

void dspSound::loadFromFile(const QString& fileName) {
  if (data) {
    data->~QByteArray();
    data=0;
  }
  if (wavFile) {
    wavFile->~QFile();
    wavFile=0;
  }
  if (riffHeader) {
    riffHeader->~QByteArray();
    riffHeader=0;
  }
  writeToLog("--->");
  writeToLog(QString(tr("Opening file \"%1\"")).arg(fileName));
  wavFile = new QFile(fileName);
  if (!wavFile->open(QIODevice::ReadOnly)) {
    writeToLog(tr("<font color=red>Can't open file</color>"));
    delete wavFile;
    return;
  }
  //Reading header of *.wav file
  QByteArray header=wavFile->read(44);

  // 0h CHECKING RIFF
  if (qstrncmp(header,"RIFF",4)==0) {
    writeToLog(tr("RIFF detected"));
  } else {
    writeToLog(tr("<font color=red>No RIFF detected - bad file format</color>"));
    delete wavFile;
    return;
  }
  // 4h reading length of main chunk
  writeToLog(QString(tr("Length of RIFF chunk : %1")).arg(getInt32(header,4)));

  // 8h
  if (qstrncmp(header.data()+8,"WAVE",4)==0) {
    writeToLog(tr("WAVE detected"));
  } else {
    writeToLog(tr("<font color=red>No WAVE detected - bad file format</color>"));
    delete wavFile;
    return;
  }

  // 0ch 
  if (qstrncmp(header.data()+12,"fmt ",4)==0) {
    writeToLog(tr("\"fmt \" sub-chunk detected"));
  } else {
    writeToLog(tr("<font color=red>No \"fmt \" sub-chunk detected - bad file format</color>"));
    delete wavFile;
    return;
  }

  // 10h
  if (getInt32(header,16)==16)  {
    writeToLog(tr("PCM format detected"));
  } else {
    writeToLog(tr("<font color=red>No PCM format detected - bad file format</color>"));
    delete wavFile;
    return;
  }
  // 14h
  if (getInt16(header,20)==1)  {
    writeToLog(tr("PCM = 1 (Linear quantization) detected"));
  } else {
    writeToLog(tr("<font color=red> PCM!=1 - bad file format</color>"));
    delete wavFile;
    return;
  }
  // 16h
  if (getInt16(header,22)==1)  {
    writeToLog(tr("MONO detected"));
    NumChannels=1;
  } else 
    if (getInt16(header,22)==2)  {
      writeToLog(tr("STEREO detected"));
      NumChannels=2;
    } else {
    writeToLog(tr("<font color=red> Not mono, and not stereo - bad file format</color>"));
    delete wavFile;
    return;
    }
  // 18h
    SampleRate=getInt32(header,24);
    if (SampleRate==44100)  {
      writeToLog(tr("Sample rate 44100 detected"));
    } else {
      writeToLog(tr("<font color=red> SampleRate!=44100 - bad file format</color>"));
      delete wavFile;
      return;
    }
    // 1ch
    writeToLog(QString(tr("Approx byte rate: %1")).arg(getInt32(header,28)));
    // 20h
    writeToLog(QString(tr("Block align: %1")).arg(getInt16(header,32)));
    //22h
    if (getInt16(header,34)==16)  {
      writeToLog(tr("Bits per sample = 16  detected"));
      BitsPerSample=16;
    } else {
      writeToLog(tr("<font color=red> Bits per sample != 16 - bad file format</color>"));
      delete wavFile;
      return;
    }
    //24h
    if (qstrncmp(header.data()+36,"data",4)==0) {
      writeToLog(tr("\"data\" sub-chunk detected"));
    } else {
      writeToLog(tr("<font color=red>No \"data\" sub-chunk detected - bad file format</color>"));
      delete wavFile;
      return;
    }
    //28h
    DataSize=getInt32(header,40);
    Nsamples=DataSize/(NumChannels*(BitsPerSample/8));
    writeToLog(QString(tr("Data sub-chunk size: %1 ; Number of samples: %2 ;")).arg(DataSize).arg(Nsamples));
    data=new QByteArray(wavFile->read(DataSize));
    riffHeader=new QByteArray(header);
}

void dspSound::saveToFile(const QString& fileName) {
  QFile outFile(fileName);
  if (!outFile.open(QIODevice::WriteOnly)) {
    writeToLog(tr("<font color=red>Can't open file to write mode</color>"));
    return;
  }

  if (outFile.write(*riffHeader)==riffHeader->size()) {
    writeToLog(QString(tr("Header written - %1 bytes")).arg(riffHeader->size())); 
  } else {
    writeToLog(QString(tr("<font color=red>Error writing file.</color>")));
  }

  if (outFile.write(*data)==data->size()) {
    writeToLog(QString(tr("Data written - %1 bytes")).arg(data->size())); 
  } else {
    writeToLog(QString(tr("<font color=red>Error writing file.</color>")));
  }
  writeToLog(QString(tr("File %1 successfully written.")).arg(fileName));
  outFile.close();
}

void dspSound::processSignal() {
  char* dataptr=data->data();

  qint16 result[Nsamples];

  audio_real pSignal[fftSize];
  audio_real window[fftSize];
  // building window
  for( int i=0; i<fftSize; ++i ) {
    window[i]=(1-cos(2*M_PI*(i+.5)/fftSize))/sqrt(2*M_PI);
  }


  for(int j=0;j<(Nsamples-fftSize)/(fftSize/4);++j){ // 4=100%/25%
    ///////////////////////
    for( int i=0; i<fftSize; ++i ) {
      pSignal[i]=static_cast<audio_real>(*(reinterpret_cast<qint16*>(dataptr+2*(fftSize/4)*j+2*i)));
      pSignal[i]=pSignal[i]*window[i];
      //writeToLog(QString("%1").arg(pSignal[i]));
    }
    Cmplx pSpec[fftSize];
    audio_real pMags[fftSize];
    fft->SetMode( FFT_REAL, fftSize );
    fft->FftReal( pSignal, pSpec );
    for( int i=0; i<=fftSize>>1; ++i ) {
      pMags[i]= sqrt( pSpec[i].re * pSpec[i].re
          + pSpec[i].im * pSpec[i].im );
      //writeToLog(QString("%1").arg(pMags[i]));
      audio_real fl = 1 - k/pMags[i];
      pSpec[i].re *= fl > 0 ? fl : cut*fl;
      pSpec[i].im *= fl > 0 ? fl : cut*fl;
    }
    fft->InvFftReal( pSpec, pSignal );
    for( int i=0; i<fftSize; ++i ) {
      //writeToLog(QString("%1").arg(pSignal[i]-
          //static_cast<audio_real>(*(reinterpret_cast<qint16*>(dataptr+2*i)))));
      result[(fftSize/4)*j+i]+=qRound(pSignal[i]*window[i]);
    }
    ////////////////////////////
  }
  delete data;
  data=new QByteArray(reinterpret_cast<const char*>(result),DataSize);
}

void dspSound::buildFFT(int length,int windowSize) {
  if (!fftDrawData->ready) {
    return;
  }
  int fftSize=1;
  while (fftSize<2*windowSize) fftSize*=2;
  fftDrawData->currentFftWindowSize=fftSize;
  fftDrawData->createFftData(length,fftSize);
  char* dataptr=data->data();
  audio_real pSignal[fftSize];
  for(int j=0;j<length;++j){
    for( int i=0; i<fftSize; ++i ) {
      pSignal[i]=static_cast<audio_real>(*(reinterpret_cast<qint16*>(dataptr+((Nsamples-fftSize)/length)*j+2*i)));
    }
    Cmplx pSpec[fftSize];
    audio_real pMags[fftSize];
    fft->SetMode( FFT_REAL, fftSize );
    fft->FftReal( pSignal, pSpec );
    for( int i=0; i<=fftSize>>1; ++i ) {
      pMags[i]= sqrt( pSpec[i].re * pSpec[i].re
          + pSpec[i].im * pSpec[i].im );
      fftDrawData->addFftWindow(j,pMags);
    }
  }
}

void dspSound::writeToLog(QString Message, int IsError) {
  emit sendLogMessage(Message,IsError);
}

quint16 dspSound::getInt16(QByteArray array, int offset) {
  return *(reinterpret_cast<quint16*>(array.data()+offset));
}

quint32 dspSound::getInt32(QByteArray array, int offset) {
  return *(reinterpret_cast<quint32*>(array.data()+offset));
}

int dspSound::getK(){
  return k;
}
void dspSound::setK(int kvalue) {
  k=kvalue;
}

int dspSound::getFftSize(){
  return fftSize;
}
void dspSound::setFftSize(int fftvalue) {
  fftSize=fftvalue;
}

double dspSound::getCut(){
  return cut;
}
void dspSound::setCut(double cutvalue) {
  cut=cutvalue;
}



