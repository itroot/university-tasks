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


#ifndef DSPMAINWINDOW_H
#define DSPMAINWINDOW_H

#include <QMainWindow>
#include "dspSound.h"
#include "dspSpectrogram.h"

class QAction;
class QMenu;
class QTextEdit;
class QVBoxLayout;
class QWidget;


class dspMainWindow : public QMainWindow {
  Q_OBJECT

  public:
    dspMainWindow();
  public slots:
    void writeToLog(QString Message, int IsError=0);
  private slots:
    void open();
    void save();
    void about();
    void process();
    void drawSpectrogram();
    void getk();
    void getfftsize();
    void getcut();
  private:
    void createWidgets();
    void createActions();
    void createMenus();
    void createEtc();

    QVBoxLayout *hlayout;

    QWidget *centralArea;
    QTextEdit *logArea;
    dspSpectrogram* spectrArea;

    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *processAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *drawSpectrogramAct;
    QAction *getKAct;
    QAction *getFftSizeAct;
    QAction *getCutAct;

    QMenu *fileMenu;
    QMenu *processMenu;
    QMenu *aboutMenu;

    dspSound* sound;
};

#endif
