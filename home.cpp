#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home) {
  ui->setupUi(this);
  net.addVer("Ver0");
  net.addVer("Ver1");
  net.addVer("Ver2");
  QString str1 = "123", str2 = "456";
  net.addArc(0, 1, str1);
  net.addArc(0, 2);
  qDebug() << net.setArc(0, 1, str2);
  qDebug() << net.getArc(0, 1)->_data;
  if (net.haveArc(0, 1))
    qDebug() << "have 0 -> 1";
  if (net.haveArc(0, 2))
    qDebug() << "have 0 -> 2";
  net.rmArc(0, 2);
  if (net.haveArc(0, 1))
    qDebug() << "have 0 -> 1";
  if (net.haveArc(0, 2))
    qDebug() << "have 0 -> 2";
}

Home::~Home() { delete ui; }
