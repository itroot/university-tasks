#ifndef CHOICEDIALOG_H_
#define CHOICEDIALOG_H_

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>

class ChoiceDialog : public QDialog { 
  Q_OBJECT
  public:
    ChoiceDialog(QWidget* parent=0, Qt::WindowFlags f=0);
    ~ChoiceDialog();
  public slots:
    void syncLabels();
    void proceedResult();
  private:
    QVBoxLayout* layout;

    QLabel* extFacesLabel;
    QLabel* intFacesLabel;

    QLineEdit* extFacesLine;
    QLineEdit* intFacesLine;
    QPushButton* okButton;
    QCheckBox* isDual;
    QCheckBox* isUsial;
};


#endif
