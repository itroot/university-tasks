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

#include "MainWindow.h"
#include <QtGui>

MainWindow::MainWindow() {
  resize(800,600);
  setWindowTitle(tr("Cubes"));

  createWidgets();
  createActions();
  createMenus();

  viewCube();
}

void MainWindow::createActions() {
  saveFBAct = new QAction(tr("Save Framebuffer..."), this);
  saveFBAct->setShortcut(tr("Ctrl+S"));
  connect(saveFBAct, SIGNAL(triggered()), this, SLOT(saveFB()));

  setTriangulationAct = new QAction(tr("&Set triangulation..."), this);
  setTriangulationAct->setShortcut(tr("Ctrl+T"));
  connect(setTriangulationAct, SIGNAL(triggered()), this, SLOT(getTriangulationNumber()));

  nextTriangulationAct = new QAction(tr("&Next triangulation"), this);
  nextTriangulationAct->setShortcut(tr("Ctrl+N"));
  connect(nextTriangulationAct, SIGNAL(triggered()), this, SLOT(nextTriangulationNumber()));

  prevTriangulationAct = new QAction(tr("&Previous triangulation"), this);
  prevTriangulationAct->setShortcut(tr("Ctrl+P"));
  connect(prevTriangulationAct, SIGNAL(triggered()), this, SLOT(prevTriangulationNumber()));

  selectCubeAct = new QAction(tr("View cube"), this);
  selectCubeAct->setShortcut(tr("Ctrl+C"));
  selectCubeAct->setCheckable(true);
  selectCubeAct->setChecked(false);
  connect(selectCubeAct, SIGNAL(triggered()), this, SLOT(viewCube()));

  selectOctoAct = new QAction(tr("View octocube"), this);
  selectOctoAct->setShortcut(tr("Ctrl+O"));
  selectOctoAct->setCheckable(true);
  selectOctoAct->setChecked(true);
  connect(selectOctoAct, SIGNAL(triggered()), this, SLOT(viewOcto()));

  getStatsAct = new QAction(tr("Sav&e cube statistics into dir..."), this);
  getStatsAct->setShortcut(tr("Ctrl+D"));
  connect(getStatsAct, SIGNAL(triggered()), this, SLOT(saveStats()));

  aboutAct = new QAction(tr("&About"), this);
  connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

  aboutQtAct = new QAction(tr("About &Qt"), this);
  connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

  connect (glWidget,SIGNAL(sendInfo_signal(const QString&)),
           infoLabel,SLOT(setText(const QString&)));
}

void MainWindow::createMenus() {

  fileMenu = new QMenu(tr("&File"), this);
  fileMenu->addAction(saveFBAct);

  triangulationMenu = new QMenu(tr("&Triangulation"), this);
  triangulationMenu->addAction(setTriangulationAct);
  triangulationMenu->addAction(nextTriangulationAct);
  triangulationMenu->addAction(prevTriangulationAct);

  selectMenu=new QMenu(tr("&Select"),this);
  selectMenu->addAction(selectCubeAct);
  selectMenu->addAction(selectOctoAct);

  statsMenu = new QMenu(tr("St&atistics"), this);
  statsMenu->addAction(getStatsAct);

  helpMenu = new QMenu(tr("&Help"), this);
  helpMenu->addAction(aboutAct);
  helpMenu->addAction(aboutQtAct);

  menuBar()->addMenu(fileMenu);
  menuBar()->addMenu(triangulationMenu);
  menuBar()->addMenu(selectMenu);
  menuBar()->addMenu(statsMenu);
  menuBar()->addMenu(helpMenu);
}

void MainWindow::createWidgets() {
  glWidget = new GlWidget();
  setCentralWidget(glWidget);
  glWidget->setFocusPolicy(Qt::StrongFocus);

  infoLabel=new QLabel();
  infoLabel->setFixedHeight(100);

  hlayout = new QVBoxLayout;
  hlayout->addWidget(glWidget,0);
  hlayout->addWidget(infoLabel,0);

  centralArea = new QWidget;
  centralArea->setLayout(hlayout);
  setCentralWidget(centralArea);
}

void MainWindow::getTriangulationNumber() {
  glWidget->cube->setTriangulation(
  QInputDialog::getInteger (this,tr("Set Triangulation"), tr("Enter Triangulation Number"), 0, 0, 63)
                                  );
  glWidget->updateGL();
}

void MainWindow::nextTriangulationNumber() {
  glWidget->cube->setTriangulation(glWidget->cube->getTriangulation()+1);
  glWidget->updateGL();
}

void MainWindow::prevTriangulationNumber() {
  glWidget->cube->setTriangulation(glWidget->cube->getTriangulation()-1);
  glWidget->updateGL();
}

void MainWindow::about() {
  QMessageBox::about(this, tr("About this"),
                     tr("Triangulation visualization program. Written by Ivan Tolstosheyev.")
                         +tr("<br><a href=\"mailto:ivan.tolstosheyev@gmail.com\">ivan.tolstosheyev@gmail.com</a>")
                         +tr("<br><i>Released under GPL v2.</i><br>")
                         +tr("Types:  0440(1), 0602(2), 1331(3), 2060(4), 2222(5), 4004(6,7 - bad)")
                    );
}

void MainWindow::saveStats() {
  const QChar fillChar='0';
  QDir saveDir=QDir(QFileDialog::getExistingDirectory (this,tr("Choose dir to save stats")));
  if ((saveDir.entryList().empty()) &&
      (QMessageBox::Cancel==QMessageBox::question(this,
       tr("Confirm, please"),
       tr("Dir is not empty. Proceed anyway?"),
       QMessageBox::Ok|QMessageBox::Cancel))) return;

  QFile statsFile(saveDir.absolutePath()+QDir::separator()+QString("readme.txt"));
  if (!statsFile.open(QIODevice::WriteOnly | QIODevice::Text)) return;
  QTextStream out(&statsFile);

  int numOf_0440=0;
  int numOf_0602=0;
  int numOf_1331=0;
  int numOf_2060=0;
  int numOf_2222=0;
  int numOf_4004=0;
  int numOf_U=0;

  for(int i=0;i<64;++i) {
    QImage tmp=glWidget->grabFrameBuffer();
    tmp.save(saveDir.absolutePath()+QDir::separator()+QString("%1.bmp").arg(i,2,10,fillChar));
    
    out << QString(tr("%1%2%3%4 - %5"))
        .arg(glWidget->cube->getNumberOfPower(0))
        .arg(glWidget->cube->getNumberOfPower(1))
        .arg(glWidget->cube->getNumberOfPower(2))
        .arg(glWidget->cube->getNumberOfPower(3))
        .arg(glWidget->cube->getTriangulation()) << endl;
    

    /*
    out << QString(tr("cubes[%5]=T_%1%2%3%4;"))
        .arg(glWidget->cube->getNumberOfPower(0))
        .arg(glWidget->cube->getNumberOfPower(1))
        .arg(glWidget->cube->getNumberOfPower(2))
        .arg(glWidget->cube->getNumberOfPower(3))
        .arg(glWidget->cube->getTriangulation()) << endl;
    */

    switch (glWidget->cube->getT_ofTriangulation()) {
      case T_0440 : {++numOf_0440;} break;
      case T_0602 : {++numOf_0602;} break;
      case T_1331 : {++numOf_1331;} break;
      case T_2060 : {++numOf_2060;} break;
      case T_2222 : {++numOf_2222;} break;
      case T_4004 : {++numOf_4004;} break;
      case T_UNKNOWN : {++numOf_U;} break;
    }
    nextTriangulationNumber();
  }

  out << endl
      << "0440 " << numOf_0440 << endl 
      << "0602 " << numOf_0602 << endl
      << "1331 " << numOf_1331 << endl
      << "2060 " << numOf_2060 << endl
      << "2222 " << numOf_2222 << endl
      << "4004 " << numOf_4004 << endl
      << "Unknown " << numOf_U << endl;


  statsFile.close();
}

void MainWindow::viewCube() {
  glWidget->cube->setVisible(true);
  glWidget->ocube->setVisible(false);
  selectCubeAct->setChecked(true);
  selectOctoAct->setChecked(false);

  setTriangulationAct->setEnabled(true);
  nextTriangulationAct->setEnabled(true);
  prevTriangulationAct->setEnabled(true);
  getStatsAct->setEnabled(true);
  triangulationMenu->setEnabled(true);
  statsMenu->setEnabled(true);

  glWidget->updateGL();
}

void MainWindow::viewOcto() {
  glWidget->ocube->setVisible(true);
  glWidget->cube->setVisible(false);
  selectOctoAct->setChecked(true);
  selectCubeAct->setChecked(false);

  setTriangulationAct->setEnabled(false);
  nextTriangulationAct->setEnabled(false);
  prevTriangulationAct->setEnabled(false);
  getStatsAct->setEnabled(false);
  triangulationMenu->setEnabled(false);
  statsMenu->setEnabled(false);

  glWidget->updateGL();
}

void MainWindow::saveFB() {
  QString fileName = QFileDialog::getSaveFileName(this,
      tr("Save File"), QDir::currentPath()+QDir::separator()+QString("Untitled.bmp"));
  QImage tmp=glWidget->grabFrameBuffer();
  tmp.save(fileName);
}

