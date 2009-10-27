#include <QtGui>

#include "imageviewer.h"
#include <iostream>
    using namespace std;
    vector<vector<int> > reper;
    const int X=400;
    const int Y=500;

namespace {
    void initReper() {
        reper.clear();
        for (size_t i=0;i<9;++i) {
            vector<int> a;
            a.push_back(20*(i-4));
            a.push_back(-50);
            reper.push_back(a);
        }
    }
    void drawReper(QPainter& painter) {
    const int X=100;
    const int Y=500;
        for (size_t i=0;i<9;++i) {
                painter.drawLine(X,Y,X+reper[i][0],Y+reper[i][1]);
        }
    }
    void drawCubant(QPainter& painter, const vector<int>& cubant) {
        int num2=0;
        vector<int> start_point(2,0);
        vector<size_t> pos;
        for (size_t i=0;i<cubant.size();++i) {
            if (2==cubant[i]) {
                ++num2;
                pos.push_back(i);
            } else if (1==cubant[i]) {
                start_point[0]+=reper[i][0];
                start_point[1]+=reper[i][1];
            }
        }
        cerr << pos.size() << "\n";
        if (0==num2) {
            painter.drawPoint(X+start_point[0],Y+start_point[1]);
        } else if (1==num2) {
            painter.drawLine(X+start_point[0],Y+start_point[1],
                             X+start_point[0] + reper[pos[0]][0],Y+start_point[1]+reper[pos[0]][1]);
        } else {
            for (size_t i=0;i<pos.size();++i) {
                vector<int> cubant_part=cubant;
                cubant_part[pos[i]]=0;
                // optimize FIXME
                drawCubant(painter, cubant_part);
                cubant_part[pos[i]]=1;
                drawCubant(painter, cubant_part);
            }
        }
    }
}

//! [0]
ImageViewer::ImageViewer()
{
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

    setWindowTitle(tr("Image Viewer"));
    resize(900, 700);
    
    // here
    
    QImage* image=new QImage(800, 600, QImage::Format_ARGB32);
    image->fill(0);
    QPainter* painter=new QPainter(image);
    //painter->drawLine(1,1,100,100);
    initReper();
    drawReper(*painter);
    /// 1111111111111111111111111111111
    painter->setPen(QColor(255,0,0));
    vector<int> cubant(9);
    cubant[0]=2;
    cubant[1]=2;
    cubant[2]=2;
    cubant[3]=0;
    cubant[4]=0;
    cubant[5]=0;
    cubant[6]=0;
    cubant[7]=0;
    cubant[8]=0;
    drawCubant(*painter, cubant);
    cubant[0]=2;
    cubant[1]=2;
    cubant[2]=1;
    cubant[3]=0;
    cubant[4]=0;
    cubant[5]=0;
    cubant[6]=0;
    cubant[7]=0;
    cubant[8]=2;
    drawCubant(*painter, cubant);
    cubant[0]=2;
    cubant[1]=1;	
    cubant[2]=1;
    cubant[3]=0;
    cubant[4]=0;
    cubant[5]=0;
    cubant[6]=0;
    cubant[7]=2;
    cubant[8]=2;
    drawCubant(*painter, cubant);
    cubant[0]=1;
    cubant[1]=1;	
    cubant[2]=1;
    cubant[3]=0;
    cubant[4]=0;
    cubant[5]=0;
    cubant[6]=2;
    cubant[7]=2;
    cubant[8]=2;
    drawCubant(*painter, cubant);
    cubant[0]=1;
    cubant[1]=1;	
    cubant[2]=1;
    cubant[3]=0;
    cubant[4]=0;
    cubant[5]=2;
    cubant[6]=2;
    cubant[7]=2;
    cubant[8]=1;
    drawCubant(*painter, cubant);
    cubant[0]=1;
    cubant[1]=1;	
    cubant[2]=1;
    cubant[3]=0;
    cubant[4]=2;
    cubant[5]=2;
    cubant[6]=2;
    cubant[7]=1;
    cubant[8]=1;
    drawCubant(*painter, cubant);
    cubant[0]=1;
    cubant[1]=1;	
    cubant[2]=1;
    cubant[3]=2;
    cubant[4]=2;
    cubant[5]=2;
    cubant[6]=1;
    cubant[7]=1;
    cubant[8]=1;
    drawCubant(*painter, cubant);
    // 2222222222222222222222222222222222222222222222
    painter->setPen(QColor(0,255,0));
    cubant[0]=0;
    cubant[1]=0;	
    cubant[2]=0;
    cubant[3]=2;
    cubant[4]=2;
    cubant[5]=2;
    cubant[6]=0;
    cubant[7]=0;
    cubant[8]=0;
    drawCubant(*painter, cubant);
    cubant[0]=0;
    cubant[1]=0;	
    cubant[2]=2;
    cubant[3]=2;
    cubant[4]=2;
    cubant[5]=1;
    cubant[6]=0;
    cubant[7]=0;
    cubant[8]=0;
    drawCubant(*painter, cubant);
    cubant[0]=0;
    cubant[1]=2;	
    cubant[2]=2;
    cubant[3]=2;
    cubant[4]=1;
    cubant[5]=1;
    cubant[6]=0;
    cubant[7]=0;
    cubant[8]=0;
    drawCubant(*painter, cubant);
    cubant[0]=2;
    cubant[1]=2;	
    cubant[2]=2;
    cubant[3]=1;
    cubant[4]=1;
    cubant[5]=1;
    cubant[6]=0;
    cubant[7]=0;
    cubant[8]=0;
    drawCubant(*painter, cubant);
    cubant[0]=2;
    cubant[1]=2;	
    cubant[2]=1;
    cubant[3]=1;
    cubant[4]=1;
    cubant[5]=1;
    cubant[6]=0;
    cubant[7]=0;
    cubant[8]=2;
    drawCubant(*painter, cubant);
    cubant[0]=2;
    cubant[1]=1;	
    cubant[2]=1;
    cubant[3]=1;
    cubant[4]=1;
    cubant[5]=1;
    cubant[6]=0;
    cubant[7]=2;
    cubant[8]=2;
    drawCubant(*painter, cubant);
    cubant[0]=1;
    cubant[1]=1;	
    cubant[2]=1;
    cubant[3]=1;
    cubant[4]=1;
    cubant[5]=1;
    cubant[6]=2;
    cubant[7]=2;
    cubant[8]=2;
    drawCubant(*painter, cubant);
    // 333333333333333333333333333333333333333333
    painter->setPen(QColor(0,0,255));
    cubant[0]=0;
    cubant[1]=0;	
    cubant[2]=0;
    cubant[3]=0;
    cubant[4]=0;
    cubant[5]=0;
    cubant[6]=2;
    cubant[7]=2;
    cubant[8]=2;
    drawCubant(*painter, cubant);
    cubant[0]=0;
    cubant[1]=0;	
    cubant[2]=0;
    cubant[3]=0;
    cubant[4]=0;
    cubant[5]=2;
    cubant[6]=2;
    cubant[7]=2;
    cubant[8]=1;
    drawCubant(*painter, cubant);
    cubant[0]=0;
    cubant[1]=0;	
    cubant[2]=0;
    cubant[3]=0;
    cubant[4]=2;
    cubant[5]=2;
    cubant[6]=2;
    cubant[7]=1;
    cubant[8]=1;
    drawCubant(*painter, cubant);
    cubant[0]=0;
    cubant[1]=0;	
    cubant[2]=0;
    cubant[3]=2;
    cubant[4]=2;
    cubant[5]=2;
    cubant[6]=1;
    cubant[7]=1;
    cubant[8]=1;
    drawCubant(*painter, cubant);
    cubant[0]=0;
    cubant[1]=0;	
    cubant[2]=2;
    cubant[3]=2;
    cubant[4]=2;
    cubant[5]=1;
    cubant[6]=1;
    cubant[7]=1;
    cubant[8]=1;
    drawCubant(*painter, cubant);
    cubant[0]=0;
    cubant[1]=2;	
    cubant[2]=2;
    cubant[3]=2;
    cubant[4]=1;
    cubant[5]=1;
    cubant[6]=1;
    cubant[7]=1;
    cubant[8]=1;
    drawCubant(*painter, cubant);
    cubant[0]=2;
    cubant[1]=2;	
    cubant[2]=2;
    cubant[3]=1;
    cubant[4]=1;
    cubant[5]=1;
    cubant[6]=1;
    cubant[7]=1;
    cubant[8]=1;
    drawCubant(*painter, cubant);
    // to here
    imageLabel->setPixmap(QPixmap::fromImage(*image));
    
    
            scaleFactor = 1.0;

        printAct->setEnabled(true);
        fitToWindowAct->setEnabled(true);
        updateActions();

        if (!fitToWindowAct->isChecked())
            imageLabel->adjustSize();
    
}
//! [0]

//! [1]
void ImageViewer::open()
//! [1] //! [2]
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                    tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
        QImage image(fileName);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }
//! [2] //! [3]
        imageLabel->setPixmap(QPixmap::fromImage(image));
//! [3] //! [4]
        scaleFactor = 1.0;

        printAct->setEnabled(true);
        fitToWindowAct->setEnabled(true);
        updateActions();

        if (!fitToWindowAct->isChecked())
            imageLabel->adjustSize();
    }
}
//! [4]

//! [5]
void ImageViewer::print()
//! [5] //! [6]
{
    Q_ASSERT(imageLabel->pixmap());
#ifndef QT_NO_PRINTER
//! [6] //! [7]
    QPrintDialog dialog(&printer, this);
//! [7] //! [8]
    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *imageLabel->pixmap());
    }
#endif
}
//! [8]

//! [9]
void ImageViewer::zoomIn()
//! [9] //! [10]
{
    scaleImage(1.25);
}

void ImageViewer::zoomOut()
{
    scaleImage(0.8);
}

//! [10] //! [11]
void ImageViewer::normalSize()
//! [11] //! [12]
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}
//! [12]

//! [13]
void ImageViewer::fitToWindow()
//! [13] //! [14]
{
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow) {
        normalSize();
    }
    updateActions();
}
//! [14]


//! [15]
void ImageViewer::about()
//! [15] //! [16]
{
    QMessageBox::about(this, tr("About Image Viewer"),
            tr("<p>The <b>Image Viewer</b> example shows how to combine QLabel "
               "and QScrollArea to display an image. QLabel is typically used "
               "for displaying a text, but it can also display an image. "
               "QScrollArea provides a scrolling view around another widget. "
               "If the child widget exceeds the size of the frame, QScrollArea "
               "automatically provides scroll bars. </p><p>The example "
               "demonstrates how QLabel's ability to scale its contents "
               "(QLabel::scaledContents), and QScrollArea's ability to "
               "automatically resize its contents "
               "(QScrollArea::widgetResizable), can be used to implement "
               "zooming and scaling features. </p><p>In addition the example "
               "shows how to use QPainter to print an image.</p>"));
}
//! [16]

//! [17]
void ImageViewer::createActions()
//! [17] //! [18]
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcut(tr("Ctrl+P"));
    printAct->setEnabled(false);
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

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
}
//! [18]

//! [19]
void ImageViewer::createMenus()
//! [19] //! [20]
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = new QMenu(tr("&View"), this);
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(normalSizeAct);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(helpMenu);
}
//! [20]

//! [21]
void ImageViewer::updateActions()
//! [21] //! [22]
{
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}
//! [22]

//! [23]
void ImageViewer::scaleImage(double factor)
//! [23] //! [24]
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}
//! [24]

//! [25]
void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
//! [25] //! [26]
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
//! [26]
