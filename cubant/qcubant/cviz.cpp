#include "cviz.h"
#include "reper.h"

#include <QtGui>
#include <QFile>
#include <QTextStream>

// FIXME
#include <iostream>

#include <cubant/Cubant.hpp>

CViz::CViz() {
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    createActions();
    createMenus();

    setWindowTitle(tr("QCubant Visualizer"));
    resize(900, 700);
    image.reset(new QImage(800, 600, QImage::Format_ARGB32));
    image->fill(0);
    painter.reset(new QPainter(image.get()));
    adjustImage();
}

void CViz::adjustImage() {
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
	drawCubants();
  adjustImage();
}

void CViz::drawCubants() {
	for (size_t i=0;i<filecontents.size();++i) {
		executeLine(filecontents[i]);
	}
}

// dumb function does something
void CViz::executeLine(const std::string& line) {
  if ('#'==line[0]) {
    return;
  }
	if ("REPER"==line.substr(0,5)) {
    reper.reset(new Reper(9));
    std::cout << "Initiailizing reper" << std::endl;
    return;
  }
	if ("COLOR"==line.substr(0,5)) {
		return;
	}
  if (NULL==reper.get()) {
    throw std::runtime_error("No reper specified");
  }
	drawCubant(line);
}

void CViz::drawCubant(const std::string& cubant) {
  const int X=400;
  const int Y=500;
  using namespace CubantCore;
  cubant_t c(cubant);
  int num2=0;
  vector<int> start_point(2,0);
  vector<size_t> pos;
  for (size_t i=0;i<c.size();++i) {
      if (CubantType::Spread==c[i].getType()) {
          ++num2;
          pos.push_back(i);
      } else if (CubantType::Shift==c[i].getType()) {
          start_point[0]+=reper->getVectorProjection(i,0);
          start_point[1]+=reper->getVectorProjection(i,1);
      }
  }
  std::cerr << pos.size() << "\n";
  std::cout << "Start point " << start_point[0] << " " << start_point[1] << std::endl;
  if (0==num2) {
      painter->drawPoint(X+start_point[0],Y+start_point[1]);
  } else if (1==num2) {
      painter->drawLine(X+start_point[0],Y+start_point[1],
                        X+start_point[0]+reper->getVectorProjection(pos[0],0),
                        Y+start_point[1]+reper->getVectorProjection(pos[0],1));
  } else {
      for (size_t i=0;i<pos.size();++i) {
          cubant_t cubant_part=c;
          cubant_part[pos[i]]=CubantType::NoShift;
          std::cout << cubant_part.toString() << std::endl;
          // optimize FIXME
          drawCubant(cubant_part.toString());
          cubant_part[pos[i]]=CubantType::Shift;
          drawCubant(cubant_part.toString());
      }
  }
}



