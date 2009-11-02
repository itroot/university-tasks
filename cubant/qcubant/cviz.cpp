#include "cviz.h"
#include "reper.h"

#include <QtGui>
#include <QFile>
#include <QTextStream>

// FIXME
#include <iostream>

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
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
		
    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void CViz::createMenus() {

		fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutQtAct);

		menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(helpMenu);
}

void CViz::open() {
	QString fileName=QFileDialog::getOpenFileName(this,
                   tr("Open File"), QDir::currentPath());
	if (!fileName.isEmpty()) {
		filecontents.clear();
		QFile file(fileName);
		if (file.open(QIODevice::ReadOnly)) {
			QTextStream textStream(&file);
			while (!textStream.atEnd()) {
				std::string result=textStream.readLine().toStdString();
				if (!result.empty()) {
					filecontents.push_back(result);
				}
				std::cerr << result << std::endl;
			}
		}
	}
}




