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

#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include "ImageProcessor.h"

class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QTextEdit;
class QVBoxLayout;
class QWidget;
class QImage;


/*!
 * This class is used to draw a window, to communicate with user.
 * It is just load picture and then give it to ImageProcessor and then show the result.
 */

class ImageViewer : public QMainWindow
{
  Q_OBJECT

  public:
    ImageViewer();

  public slots:
    void writeLog(QString Message,int Error=0);
    void updateImage(QImage& Image);
  private slots:
    void open();
    void save();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();
    void proceed();
    void proceedByStep();

  private:
    void createWidgets();
    void createActions();
    void createMenus();
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QTextEdit *logArea;
    QVBoxLayout *hlayout;
    QWidget *centralArea;
    QImage currentImage;
    double scaleFactor;

    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *proceedAct;
    QAction *proceedByStepAct;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *proceedMenu;
    QMenu *helpMenu;

    ImageProcessor *imageProcessor;
};

#endif
