#include "cviz.h"
#include <QtGui>

CViz::CViz() {
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    createActions();
    createMenus();

    setWindowTitle(tr("QCubant Visualizer"));
    //resize(900, 700);
    QImage* image=new QImage(800, 600, QImage::Format_ARGB32);
    image->fill(0);
    imageLabel->setPixmap(QPixmap::fromImage(*image));
    imageLabel->adjustSize();
}

void CViz::createActions() {

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void CViz::createMenus() {

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(helpMenu);
}




