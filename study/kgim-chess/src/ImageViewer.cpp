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


#include "ImageViewer.h"
#include "ImageProcessor.h"

ImageViewer::ImageViewer()
{
  createWidgets();
  createActions();
  createMenus();

  setWindowTitle(tr("Image Viewer"));

  // Fitting to window by default
  fitToWindowAct->setChecked(true);
  fitToWindow();
  resize(500, 600);
  show();
}

void ImageViewer::createWidgets() {

  // Creating graphic label
  imageLabel = new QLabel;
  imageLabel->setBackgroundRole(QPalette::Base);
  imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  imageLabel->setScaledContents(true);

  // Creating scroll area and putting imageLabel inside it
  scrollArea = new QScrollArea;
  scrollArea->setBackgroundRole(QPalette::Dark);
  scrollArea->setWidget(imageLabel);

  //Creating logArea
  logArea = new QTextEdit;
  logArea->setReadOnly(true);

  // Creating layout and putting there logArea and scrollArea
  hlayout = new QVBoxLayout;
  hlayout->addWidget(scrollArea,0);
  hlayout->addWidget(logArea,0);

  //Creating centralArea and making it central widget
  centralArea = new QWidget;
  centralArea->setLayout(hlayout);
  setCentralWidget(centralArea);
  logArea->setFixedHeight(100);
}

void ImageViewer::open()
{
  //Opening file and loading image to imageLabel

  QString fileName = QFileDialog::getOpenFileName(this,
      tr("Open File"), QDir::currentPath());
  if (!fileName.isEmpty()) {
  //QString fileName = "/home/ivan/Desktop/CG/2/task/images/3.bmp";
    currentImage = QImage(fileName);
    imageProcessor->setImage(currentImage);
    //QRect temprect =
      // !!!! currentImage=imageProcessor->proceed();
    if (currentImage.isNull()) {
      QMessageBox::information(this, tr("Image Viewer"),
                               tr("Cannot load %1.").arg(fileName));
      return;
    }
    imageLabel->setPixmap(QPixmap::fromImage(currentImage));
    scaleFactor = 1.0;

   
    fitToWindowAct->setEnabled(true);
    proceedAct->setEnabled(true);
    proceedByStepAct->setEnabled(true);
    saveAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
      imageLabel->adjustSize();
  }
}

void ImageViewer::save() {
  QString fileName = QFileDialog::getSaveFileName(this,
      tr("Save File"), QDir::currentPath());
  currentImage.save(fileName);
}


void ImageViewer::zoomIn()
{
  scaleImage(1.25);
}

void ImageViewer::zoomOut()
{
  scaleImage(0.8);
}

void ImageViewer::normalSize()
{
  imageLabel->adjustSize();
  scaleFactor = 1.0;
}

void ImageViewer::fitToWindow()
{
  bool fitToWindow = fitToWindowAct->isChecked();
  scrollArea->setWidgetResizable(fitToWindow);
  if (!fitToWindow) {
    normalSize();
  }
  updateActions();
}


void ImageViewer::about()
{
  QMessageBox::about(this, tr("About Image Viewer"),
                     tr("Image Processing program. Written by Ivan Tolstosheyev.")
                      +tr("Realesed under GPL v2. For more information see readme file."));
}

void ImageViewer::proceed() {
  currentImage=imageProcessor->proceed(0);
  proceedAct->setEnabled(false);
  proceedByStepAct->setEnabled(false);
}

void ImageViewer::proceedByStep() {
  currentImage=imageProcessor->proceed(1);
  proceedAct->setEnabled(false);
  proceedByStepAct->setEnabled(false);
}


void ImageViewer::createActions()
{
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

  zoomInAct = new QAction(tr("Zoom &In (25%)"), this);
  zoomInAct->setShortcut(tr("Ctrl++"));
  zoomInAct->setEnabled(false);
  connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

  zoomOutAct = new QAction(tr("Zoom &Out (25%)"), this);
  zoomOutAct->setShortcut(tr("Ctrl+-"));
  zoomOutAct->setEnabled(false);
  connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

  normalSizeAct = new QAction(tr("&Normal Size"), this);
  normalSizeAct->setShortcut(tr("Ctrl+S"));
  normalSizeAct->setEnabled(false);
  connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

  fitToWindowAct = new QAction(tr("&Fit to Window"), this);
  fitToWindowAct->setEnabled(false);
  fitToWindowAct->setCheckable(true);
  fitToWindowAct->setShortcut(tr("Ctrl+F"));
  connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));

  aboutAct = new QAction(tr("&About"), this);
  connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

  aboutQtAct = new QAction(tr("About &Qt"), this);
  connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
  
  proceedAct = new QAction(tr("Proceed image"), this);
  proceedAct->setEnabled(false);
  proceedAct->setShortcut(tr("Ctrl+P"));
  connect(proceedAct, SIGNAL(triggered()),this, SLOT(proceed()));
  
  proceedByStepAct = new QAction(tr("Proceed image by step"), this);
  proceedByStepAct->setEnabled(false);
  connect(proceedByStepAct, SIGNAL(triggered()),this, SLOT(proceedByStep()));

  // Log function
  imageProcessor = new ImageProcessor();
  connect(imageProcessor,SIGNAL(sendLogMessage(QString,int)),
          this,SLOT(writeLog(QString,int)));
  connect(imageProcessor,SIGNAL(sendImage(QImage&)),
         this,SLOT(updateImage(QImage&)));

}

void ImageViewer::createMenus()
{
  fileMenu = new QMenu(tr("&File"), this);
  fileMenu->addAction(openAct);
  fileMenu->addAction(saveAct);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);

  viewMenu = new QMenu(tr("&View"), this);
  viewMenu->addAction(zoomInAct);
  viewMenu->addAction(zoomOutAct);
  viewMenu->addAction(normalSizeAct);
  viewMenu->addSeparator();
  viewMenu->addAction(fitToWindowAct);

  proceedMenu = new QMenu(tr("&Proceed"),this);
  proceedMenu->addAction(proceedAct);
  proceedMenu->addAction(proceedByStepAct);

  helpMenu = new QMenu(tr("&Help"), this);
  helpMenu->addAction(aboutAct);
  helpMenu->addAction(aboutQtAct);

  menuBar()->addMenu(fileMenu);
  menuBar()->addMenu(viewMenu);
  menuBar()->addMenu(proceedMenu);
  menuBar()->addMenu(helpMenu);
}

void ImageViewer::updateActions()
{
  zoomInAct->setEnabled(!fitToWindowAct->isChecked());
  zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
  normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

void ImageViewer::scaleImage(double factor)
{
  Q_ASSERT(imageLabel->pixmap());
  scaleFactor *= factor;
  imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

  adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
  adjustScrollBar(scrollArea->verticalScrollBar(), factor);

  zoomInAct->setEnabled(scaleFactor < 3.0);
  zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
  scrollBar->setValue(int(factor * scrollBar->value()
      + ((factor - 1) * scrollBar->pageStep()/2)));
}

void ImageViewer::writeLog(QString Message, int IsError) {
  logArea->append(Message);
  if (IsError) {
    QMessageBox::critical(this, tr("Error"),tr("The following error occured:\n%1\nTerminating application.").arg(Message));
    //this->close();
    exit(1);
  }
  //qApp->processEvents();
  //logArea->repaint();
}

void ImageViewer::updateImage(QImage& Image) {
  imageLabel->setPixmap(QPixmap::fromImage(Image));
  qApp->processEvents();
  QTime dieTime = QTime::currentTime().addMSecs(300);
  while( QTime::currentTime() < dieTime ) {
    qApp->processEvents();
  }
}


