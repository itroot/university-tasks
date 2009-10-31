#ifndef CVIZ_H
#define CVIZ_H

#include <QMainWindow>

#include <vector>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE

class CViz : public QMainWindow {
    Q_OBJECT

public:
//    CViz();

private slots:

private:
    void createActions();
    void createMenus();
    void updateActions();

    QLabel *imageLabel;


    QAction *aboutQtAct;

    QMenu *helpMenu;
};

#endif
