#include "ChoiceDialog.h"

#include <QIntValidator>
#include "Etc.h"
#include "tmath/OctoCube.h"

namespace {
  QString getFixedHex(unsigned int value, size_t size) {
    QString s(size,'0');
    for (int i=size-1;i>=0;--i) {
      if (value&1) {
        s[i]='1';
      } else {
        s[i]='0';
      }
      value>>=1;
    }
    return s;
  }
}

ChoiceDialog::ChoiceDialog(QWidget* parent, Qt::WindowFlags f):
  QDialog(parent,f) {

  extFacesLabel=new QLabel(this);
  intFacesLabel=new QLabel(this);

  extFacesLine=new QLineEdit(this);
  intFacesLine=new QLineEdit(this);
  okButton=new QPushButton(this);

  isDual=new QCheckBox(this);
  isDual->setText(tr("dual"));

  isUsial=new QCheckBox(this);
  isUsial->setText(tr("usial"));
  isUsial->setChecked(/*yes*/true);

  layout=new QVBoxLayout;
  layout->addWidget(extFacesLine);
  layout->addWidget(extFacesLabel);
  layout->addWidget(intFacesLine);
  layout->addWidget(intFacesLabel);
  layout->addWidget(okButton);
  layout->addWidget(isDual);
  layout->addWidget(isUsial);

  this->setLayout(layout);

  okButton->setText("OK");

  extFacesLine->setText("0");
  intFacesLine->setText("0");

  extFacesLine->setValidator(new QIntValidator(0,16777215,this));
  intFacesLine->setValidator(new QIntValidator(0,4095,this));


  connect(extFacesLine,SIGNAL(textChanged(const QString&)),this,SLOT(syncLabels()));
  connect(intFacesLine,SIGNAL(textChanged(const QString&)),this,SLOT(syncLabels()));
  connect(okButton,SIGNAL(clicked()),this,SLOT(proceedResult()));
  syncLabels();
}

void ChoiceDialog::syncLabels() {
  unsigned int efaces=extFacesLine->text().toInt();
  unsigned int ifaces=intFacesLine->text().toInt();
  QString color="green";

  QString etext=getFixedHex(efaces,24);
  QString itext=getFixedHex(ifaces,12);

  OctoCube ocube(efaces,ifaces);
  if (ocube.isGood()) {
    color="green";
    okButton->setEnabled(true);
  } else {
    color="red";
    okButton->setEnabled(false);
  }
  extFacesLabel->setText("<font color="+color+">"+etext+"</color>");
  intFacesLabel->setText("<font color="+color+">"+itext+"</color>");
}

void ChoiceDialog::proceedResult() {
  static_ext_faces=extFacesLine->text().toInt();
  static_int_faces=intFacesLine->text().toInt();
  static_is_dual=isDual->isChecked();
  static_is_usial=isUsial->isChecked();
  accept();
}

ChoiceDialog::~ChoiceDialog() {
}
