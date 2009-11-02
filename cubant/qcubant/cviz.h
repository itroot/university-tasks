#ifndef CVIZ_H
#define CVIZ_H

#include <QMainWindow>

#include <vector>
#include <string>
#include <memory>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE

class Reper;

class CViz : public QMainWindow {
    Q_OBJECT

	public:
    CViz();

	private slots:
    void open();
		void drawCubants();
	private:
	  void executeLine(const std::string& line);
		void drawCubant(const std::string& cubant);
    void createActions();
    void createMenus();

    QLabel *imageLabel;

    QAction *openAct;
    QAction *aboutQtAct;

		QMenu *fileMenu;
    QMenu *helpMenu;
		
		std::auto_ptr<Reper> reper;
		// FIXME this shit
		std::vector<std::string> filecontents;
};

#endif
