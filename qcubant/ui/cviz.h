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
class QScriptEngine;
QT_END_NAMESPACE

class Reper;

class CViz : public QMainWindow {
    Q_OBJECT

    public:
        CViz();
        ~CViz();

    public slots:
        void drawCubant(const std::string& cubant);
        void drawCubantClearCache(const std::string& cubant);
        void setReperDimension(unsigned int);
        void setPenWidth(unsigned int);
        void setNumColor(unsigned int, unsigned int, unsigned int); // RGB
        void setImageSize(unsigned int x, unsigned int y);
        void setCubantStart(unsigned int x, unsigned int y);
        void setReper2DVector(unsigned int vectorNum, int x, int y);
    private:
        static const double RGB=255.0;
        void resetImage(unsigned int x, unsigned int y);
    private slots:
        void open();
        void save();
        void onPushRunButton();
        void drawCubants();
        void saveVRML();
        void showhideJsOut();
        void openJS();
    private:
        void executeLine(const std::string& line);
        void createActions();
        void createMenus();
        void adjustImage();
        void setColor(const std::string& line);
        void setReper(const std::string& line);
        void setImage(const std::string& line);
        void setCStart(const std::string& line);
        void drawReper();
        // js
        void runJsScript();
        void embedCubants();

        // VRML
        void initVrml();
        void addPoint(int x, int y, int z=0);
        void addLine(int x1, int x2, int y1, int y2, int z1=0, int z2=0);

        QScrollArea* scrollArea;
        QLabel *imageLabel;
        QVBoxLayout* layout;
        QWidget* centerWidget;
        QTabWidget* tabWidget;
        QTextEdit* textEdit;
        QTextEdit* jsEdit;
        QTextEdit* jsOut;
        QPushButton* runButton;

        std::auto_ptr<QImage> image;
        std::auto_ptr<QPainter> painter;

        QAction *openAct;
        QAction *saveAct;
        QAction *saveVRMLAct;
        QAction *showhideJsOutAct;
        QAction *openJsOutAct;
        QAction *aboutQtAct;

        QMenu *fileMenu;
        QMenu *helpMenu;

        std::auto_ptr<QScriptEngine> scriptEngine;
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
        int penWidth;
        // cubant pos.
        int startCX;
        int startCY;
};

#endif
