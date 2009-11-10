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
QT_END_NAMESPACE

class Reper;

class CViz : public QMainWindow {
    Q_OBJECT

	public:
    CViz();

	private slots:
    void open();
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

    QScrollArea* scrollArea;
    QLabel *imageLabel;
    
    std::auto_ptr<QImage> image;
    std::auto_ptr<QPainter> painter;

    QAction *openAct;
    QAction *saveVRMLAct;
    QAction *aboutQtAct;

		QMenu *fileMenu;
    QMenu *helpMenu;
		
		std::auto_ptr<Reper> reper;
		// FIXME this shit
		std::vector<std::string> filecontents;
    std::set<std::string> drawedCubants;
    // FIXME HACK
    std::string vrmlString;
};

#endif
