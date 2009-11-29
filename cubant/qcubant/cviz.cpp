#include "cviz.h"
#include "reper.h"

#include <QtGui>
#include <QFile>
#include <QTextStream>

// FIXME
#include <iostream>
#include <sstream>

#include <cubant/Cubant.hpp>
#include <stdlib.h>
namespace {
  using namespace std;
  void initVrml(std::string& vrml) {
    vrml="#VRML V2.0 utf8\n\nBackground { skyColor [ 1 1 1 ] }\n";
  }
  
  void addPoint(std::string& vrml, int x, int y, int z=0) {
    stringstream ss;
    ss << "Transform { translation " <<
    x << " " << y << " " << z << 
    " children [Shape {appearance Appearance {material Material {diffuseColor 0.2 0.2 0.2}}geometry Sphere{radius 3}}]}\n";
    vrml+=ss.str();
  }
  
  void addLine(std::string& vrml, int x1, int x2, int y1, int y2, int z1=0, int z2=0) { 
    stringstream ss;
    ss << "Shape { geometry IndexedLineSet { coord Coordinate { point [ " <<
    x1 << " " << y1 << " " << z1 << " , " <<  
    x2 << " " << y2 << " " << z2 << " " <<
    " ] } coordIndex [ 0, 1] color Color { color [ 0 0 0, 0 0 0 ] } } }\n";
    vrml+=ss.str();
  }
}

CViz::CViz() {
  /*
    std::string str;
    initVrml(str);
    addPoint(str, 0,0);
    addPoint(str, 10,0);
    addPoint(str, 10,10);
    addLine(str, 0,0,10,10);
    std::cout << str ;
   */
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
    
    saveVRMLAct = new QAction(tr("Save VRML..."), this);
    saveVRMLAct->setShortcut(tr("Ctrl+S"));
    connect(saveVRMLAct, SIGNAL(triggered()), this, SLOT(saveVRML()));
    
		
    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void CViz::setColor(const std::string& line) {
  size_t pos=0;
  pos=line.find(":");
  if (std::string::npos==pos) {
    return;
  }
  int r=atoi(line.c_str()+pos+1);
  
  pos=line.find(",");
  if (std::string::npos==pos) {
    return;
  }
  int g=atoi(line.c_str()+pos+1);

  pos=line.find(",",pos+1);
  if (std::string::npos==pos) {
    return;
  }
  int b=atoi(line.c_str()+pos+1);
  
  painter->setPen(QColor(r,g,b));
}

void CViz::setReper(const std::string& line) {
  size_t pos=line.find(":");
  if (std::string::npos==pos) {
    return;
  }
  unsigned int dim=atoi(line.c_str()+pos+1);
  reper.reset(new Reper(dim));
}

void CViz::createMenus() {

		fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveVRMLAct);

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
  image->fill(0); // FIXME clear image
  drawedCubants.clear();
	drawCubants();
  adjustImage();
}

void CViz::drawCubants() {
  initVrml(vrmlString); // FIXME
	for (size_t i=0;i<filecontents.size();++i) {
		executeLine(filecontents[i]);
	}
  std::cout << vrmlString << std::endl;
}

// dumb function does something
void CViz::executeLine(const std::string& line) {
  if ('#'==line[0]) {
    return;
  }
	if ("REPER"==line.substr(0,5)) {
    setReper(line);
    drawReper();
    std::cout << "Initiailizing reper" << std::endl;
    return;
  }
	if ("COLOR"==line.substr(0,5)) {
    setColor(line);
		return;
	}
  if (NULL==reper.get()) {
    throw std::runtime_error("No reper specified");
  }
	drawCubant(line);
}

void CViz::saveVRML() {
    QString fileName = QFileDialog::getSaveFileName(this,
      tr("Save VRML"), QDir::currentPath()+QDir::separator()+QString("Untitled.wrl"));

    QFile file(fileName);
      if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
      }

    QTextStream out(&file);
    out << QString(vrmlString.c_str()) << "\n";
}

void CViz::drawReper() {
  const int X=140;
  const int Y=580;
  for (size_t i=0; i<reper->getNum(); ++i) {
    painter->drawLine(X,Y,
                        X+reper->getVectorProjection(i,0),
                        Y+reper->getVectorProjection(i,1));
  }
}

void CViz::drawCubant(const std::string& cubant) {
  if (drawedCubants.end()!=drawedCubants.find(cubant)) {
    return;
  } else {
    drawedCubants.insert(cubant);
  }
  const int X=400;
  const int Y=580;
  using namespace CubantCore;
  cubant_t c(cubant);
  int num2=0;
  vector<int> start_point(2,0);
  vector<int> start_point3d(3,0);
  vector<size_t> pos;
  for (size_t i=0;i<c.size();++i) {
      if (CubantType::Spread==c[i].getType()) {
          ++num2;
          pos.push_back(i);
      } else if (CubantType::Shift==c[i].getType()) {
          start_point[0]+=reper->getVectorProjection(i,0);
          start_point[1]+=reper->getVectorProjection(i,1);
          
          start_point3d[0]+=reper->getVectorProjection3D(i,0);
          start_point3d[1]+=reper->getVectorProjection3D(i,1);
          start_point3d[2]+=reper->getVectorProjection3D(i,2);
      }
  }
  std::cerr << pos.size() << "\n";
  std::cout << "Start point " << start_point[0] << " " << start_point[1] << std::endl;
  if (0==num2) {
      painter->drawPoint(X+start_point[0],Y+start_point[1]);
      //addPoint(vrmlString, X+start_point[0], Y+start_point[1]);
      addPoint(vrmlString, start_point3d[0], start_point3d[1], start_point3d[2]);
      return;
  } else if (1==num2) {
      //addLine(vrmlString,X+start_point[0], X+start_point[0]+reper->getVectorProjection(pos[0],0),
      //                   Y+start_point[1], Y+start_point[1]+reper->getVectorProjection(pos[0],1));
      addLine(vrmlString,start_point3d[0], start_point3d[0]+reper->getVectorProjection3D(pos[0],0),
                         start_point3d[1], start_point3d[1]+reper->getVectorProjection3D(pos[0],1),
                         start_point3d[2], start_point3d[2]+reper->getVectorProjection3D(pos[0],2));
      painter->drawLine(X+start_point[0],Y+start_point[1],
                        X+start_point[0]+reper->getVectorProjection(pos[0],0),
                        Y+start_point[1]+reper->getVectorProjection(pos[0],1));
  } //else {
      for (size_t i=0;i<pos.size();++i) {
          cubant_t cubant_part=c;
          cubant_part[pos[i]]=CubantType::NoShift;
          std::cout << cubant_part.toString() << std::endl;
          // optimize FIXME
          drawCubant(cubant_part.toString());
          cubant_part[pos[i]]=CubantType::Shift;
          drawCubant(cubant_part.toString());
     // }
  }
}



