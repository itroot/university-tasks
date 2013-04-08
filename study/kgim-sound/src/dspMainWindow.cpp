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

#include "dspMainWindow.h"
#include <QtGui>

dspMainWindow::dspMainWindow() {
  createWidgets();
  createActions();
  createMenus();
  createEtc();
  resize(400, 300);
  setWindowTitle(tr("Task5: Noise reduction"));
  writeToLog("Program started.");
}

void dspMainWindow::createWidgets() {
  logArea = new QTextEdit;
  logArea->setReadOnly(true);

  spectrArea=new dspSpectrogram();

  hlayout = new QVBoxLayout;
  hlayout->addWidget(spectrArea,1);
  hlayout->addWidget(logArea,1);

  centralArea = new QWidget;
  centralArea->setLayout(hlayout);

  setCentralWidget(centralArea);
  logArea->setFixedHeight(100);
};

void dspMainWindow::createActions() {
  openAct = new QAction(tr("&Open..."), this);
  openAct->setShortcut(tr("Ctrl+O"));
  connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

  saveAct = new QAction(tr("&Save..."), this);
  saveAct->setShortcut(tr("Ctrl+S"));
  connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));
  saveAct->setEnabled(false);

  exitAct = new QAction(tr("E&xit"), this);
  exitAct->setShortcut(tr("Ctrl+Q"));
  connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

  getKAct = new QAction(tr("&Set K"), this);
  connect(getKAct, SIGNAL(triggered()), this, SLOT(getk()));

  getFftSizeAct = new QAction(tr("&Set Fft window size"), this);
  connect(getFftSizeAct, SIGNAL(triggered()), this, SLOT(getfftsize()));

  getCutAct = new QAction(tr("&Set cut treshold : 0.1"), this);
  connect(getCutAct, SIGNAL(triggered()), this, SLOT(getcut()));

  processAct = new QAction(tr("&Process..."), this);
  processAct->setShortcut(tr("Ctrl+P"));
  connect(processAct, SIGNAL(triggered()), this, SLOT(process()));
  processAct->setEnabled(false);

  drawSpectrogramAct = new QAction(tr("&Draw Spectrogram"), this);
  drawSpectrogramAct->setShortcut(tr("Ctrl+D"));
  drawSpectrogramAct->setCheckable(true);
  connect(drawSpectrogramAct, SIGNAL(triggered()), this, SLOT(drawSpectrogram()));
  drawSpectrogramAct->setEnabled(false);

  aboutAct = new QAction(tr("&About"), this);
  connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

  aboutQtAct = new QAction(tr("About &Qt"), this);
  connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
};

void dspMainWindow::createMenus() {
  fileMenu = new QMenu(tr("&File"), this);
  fileMenu->addAction(openAct);
  fileMenu->addAction(saveAct);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);

  processMenu = new QMenu(tr("&Process"), this);
  processMenu->addAction(getKAct);
  processMenu->addAction(getFftSizeAct);
  processMenu->addAction(getCutAct);
  processMenu->addSeparator();
  processMenu->addAction(processAct);
  processMenu->addAction(drawSpectrogramAct);

  aboutMenu = new QMenu(tr("&Help"), this);
  aboutMenu->addAction(aboutAct);
  aboutMenu->addAction(aboutQtAct);

  menuBar()->addMenu(fileMenu);
  menuBar()->addMenu(processMenu);
  menuBar()->addMenu(aboutMenu);
};

void dspMainWindow::createEtc() {
  sound = new dspSound();
  connect(sound,SIGNAL(sendLogMessage(QString,int)),this,SLOT(writeToLog(QString,int)));
  connect(spectrArea,SIGNAL(sizeChanged(int,int)),sound,SLOT(buildFFT(int,int)));
  ///////////////
  //sound->loadFromFile("/home/ivan/kdevelop/task5/bin/Music.wav");
  //saveAct->setEnabled(true);
  //processAct->setEnabled(true);
  //processAct->setText(QString("Process with K: %1 FFT: %2").arg(sound->getK()).arg(sound->getFftSize()));
  
  //sound->fftDrawData->ready=1;
  //spectrArea->setSpectr(sound->fftDrawData);
  //process();
  //sound->saveToFile("/home/ivan/kdevelop/task5/bin/huh.wav");
  //exit(0);
  ///////////////
}


void dspMainWindow::open() {
  QString fileName = QFileDialog::getOpenFileName(this,
      tr("Open *.wav File"), QDir::currentPath(), tr("Wav files (*.wav)"));
  if (!fileName.isEmpty()) {
    sound->loadFromFile(fileName);
  }
  saveAct->setEnabled(true);
  processAct->setEnabled(true);
  processAct->setText(QString("Process with K: %1 FFT: %2").arg(sound->getK()).arg(sound->getFftSize()));
  spectrArea->setSpectr(sound->fftDrawData);
  drawSpectrogramAct->setEnabled(true);
}

void dspMainWindow::save() {
  QString fileName = QFileDialog::getSaveFileName(this,
      tr("Save *.wav File"), QDir::currentPath(),tr("Wav files (*.wav)"));
  sound->saveToFile(fileName);
}

void dspMainWindow::process() {
  processAct->setEnabled(false);
  sound->processSignal();
  if (sound->fftDrawData->ready) {
    sound->buildFFT(spectrArea->width(),spectrArea->height());
    spectrArea->repaint();
  }
}

void dspMainWindow::about() {
  QMessageBox::about(this, tr("About DSP - Task5."),
                     tr("Noise reduction program. Written by <b>Ivan Tolstosheyev</b>.<br>")
                         +tr("Using FftWrapper written by <b>Alexey Lukin</b>.<br>")
                    +tr("Realesed under GPL v2. For more information see readme file."));
}

void dspMainWindow::getk() {
  sound->setK(QInputDialog::getInteger (this,tr("Enter K"), tr("Enter K "), 8000, 0));
  processAct->setText(QString("Process with K: %1 FFT: %2").arg(sound->getK()).arg(sound->getFftSize()));
}

void dspMainWindow::getfftsize() {
  int tmp=QInputDialog::getInteger (this,tr("Enter FFT"), tr("Enter FFT window size "), 16, 0);
  int power2tmp=4;
  while (power2tmp<tmp) power2tmp*=2;
  sound->setFftSize(power2tmp);
  processAct->setText(QString("Process with K: %1 FFT: %2").arg(sound->getK()).arg(sound->getFftSize()));
}

void dspMainWindow::getcut() {
  sound->setCut(QInputDialog::getDouble (this,tr("Enter cut treshold"),
                tr("Cut is used agains music noises, it doesn't delete all noises"),0,0));
  getCutAct->setText(QString(tr("&Set cut treshold : %1")).arg(sound->getCut()));
}

void dspMainWindow::drawSpectrogram() {
  if (drawSpectrogramAct->isChecked()) {
    sound->fftDrawData->ready=1;
    sound->buildFFT(spectrArea->width(),spectrArea->height());
  } else {
    sound->fftDrawData->ready=0;
  }
  spectrArea->repaint();
}

void dspMainWindow::writeToLog(QString Message, int IsError) {
  if (IsError) {
    QMessageBox::critical(this,
                          tr("Error"),
                             tr("The following error occured:\n%1\nTerminating application.")
                                 .arg(Message));
    exit(1);
  }
  logArea->append((QTime::currentTime()).toString("[ hh:mm:ss.zzz ] ")+Message);
}
