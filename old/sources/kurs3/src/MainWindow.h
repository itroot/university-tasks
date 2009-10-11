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



#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "GlWidget.h"

class QLabel;
class QVBoxLayout;

class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
    MainWindow();
  private slots:
    void getTriangulationNumber(); 
    void nextTriangulationNumber();
    void prevTriangulationNumber();
    void viewCube();
    void viewOcto();
    void saveStats();
    void about();
    void saveFB();
  private:
    void createWidgets();
    void createActions();
    void createMenus();

    GlWidget *glWidget;
    QLabel *infoLabel;
    QVBoxLayout *hlayout;
    QWidget *centralArea;

    QAction *saveFBAct;

    QAction *setTriangulationAct;
    QAction *nextTriangulationAct;
    QAction *prevTriangulationAct;

    QAction *selectCubeAct;
    QAction *selectOctoAct;

    QAction *getStatsAct;

    QAction *aboutAct;
    QAction *aboutQtAct;

    QMenu *fileMenu;
    QMenu *triangulationMenu;
    QMenu *selectMenu;
    QMenu *statsMenu;
    QMenu *helpMenu;
};


#endif
