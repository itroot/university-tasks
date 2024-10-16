#ifndef CVIZ_H
#define CVIZ_H

#include <QMainWindow>

#include <vector>
#include <string>
#include <memory>
#include <set>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QPainter;
class QImage;
class QVBoxLayout;
class QTextEdit;
class QPushButton;
QT_END_NAMESPACE

class Reper;

class CViz : public QMainWindow {
    Q_OBJECT

	public:
    CViz();

  private:
    static const double RGB=255.0;
  private slots:
    void open();
    void save();
    void onPushRunButton();
    void drawCubants();
    void saveVRML();
  private:
	  void executeLine(const std::string& line);
		void drawCubant(const std::string& cubant);
    void createActions();
    void createMenus();
    void adjustImage();
    void setColor(const std::string& line);
    void setReper(const std::string& line);
    void drawReper();
    
    // VRML
    void initVrml();
    void addPoint(int x, int y, int z=0);
    void addLine(int x1, int x2, int y1, int y2, int z1=0, int z2=0);

    QScrollArea* scrollArea;
    QLabel *imageLabel;
    QVBoxLayout* layout;
    QWidget* centerWidget;
    QTextEdit* textEdit;
    QPushButton* runButton;
    
    std::auto_ptr<QImage> image;
    std::auto_ptr<QPainter> painter;

    QAction *openAct;
    QAction *saveAct;
    QAction *saveVRMLAct;
    QAction *aboutQtAct;

    QMenu *fileMenu;
    QMenu *helpMenu;
		
    std::auto_ptr<Reper> reper;
    // FIXME this shit
    std::vector<std::string> filecontents;
    std::set<std::string> drawedCubants;
    // FIXME HACK
    std::string vrml;
    // HACK
    int R;
    int G;
    int B;
};

#endif
