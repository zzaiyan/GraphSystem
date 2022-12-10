#include "home.h"
#include "ui_home.h"

Home::Home(QWidget* parent) : QWidget(parent), ui(new Ui::Home) {
  ui->setupUi(this);
  ALNet<int, int> net;

  net.addVer(0);
  net.addVer(1);
  net.addVer(2);

  net.addArc(0, 1, 901);  // 901 means <0,1>
  net.addArc(0, 2, 902);
  net.addArc(1, 0, 910);
  net.addArc(1, 2, 912);
  net.addArc(2, 1, 921);

  net.printVers();
  net.printTable();

  qDebug() << "";
  net.rmVer(1);
  qDebug() << "";

  net.printTable();
}

Home::~Home() {
  delete ui;
}
