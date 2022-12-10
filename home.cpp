#include "home.h"
#include "ui_home.h"

#define ID_FILE "D:\\QtWorks\\GraphSystem\\data\\id.csv"

Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home) {
  ui->setupUi(this);
  readFile();

  qDebug() << hsId["贾宝玉"];
}

Home::~Home() { delete ui; }

void Home::readFile() {
  hsId.clear();
  std::ifstream ifs(ID_FILE, std::ios::in);
  if (!ifs) {
    qDebug() << "File open error!";
    exit(1);
  }
  std::string lineBuf;
  while (std::getline(ifs, lineBuf)) {
    int div = 0, len = lineBuf.size();
    for (; div < len && lineBuf[div] != ','; div++)
      ;
    QString name = QString::fromLocal8Bit(lineBuf.data(), div++);
    int id = QString::fromLocal8Bit(lineBuf.data() + div, len - div).toInt();
    qDebug() << QString("%1 -> %2").arg(name).arg(id);
    hsId.insert(name, id);
  }
}
