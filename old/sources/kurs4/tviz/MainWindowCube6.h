#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include "Renderer.h"


/**
 * Class represents main (and only) window of app.
 * Just widgets, nothing more.
 */
class MainWindow : public QMainWindow { 
  Q_OBJECT
  // Functions.
  public: 
  	MainWindow();
  	~MainWindow();
  private:
    void createWidgets();
    void createActions();
    void createMenus();
    void proceedRequest(); // temporary
  // Members.
  public:
  /// Main widget in window - renders objects.
  Renderer* renderer;
};

#endif /*MAINWINDOW_H_*/
