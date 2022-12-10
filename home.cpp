#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home) {
  ui->setupUi(this);
  net.addVer("Ver0");
  net.addVer("Ver1");
  net.addArc(0, 1);
  if (net.haveArc(0, 1))
    qDebug() << "have 0 -> 1";
  if (net.haveArc(0, 2))
    qDebug() << "have 0 -> 2";
}

Home::~Home() { delete ui; }
