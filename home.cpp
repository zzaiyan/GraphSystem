#include "home.h"
#include "ui_home.h"

#define ID_FILE "/home/z/Desktop/QPro/GraphSystem/data/id.csv"
#define REL_FILE "/home/z/Desktop/QPro/GraphSystem/data/data.csv"

Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home) {
  ui->setupUi(this);
  readFile();

  net.printVers();
  auto jby = net.getVer(308);
  for (int i = 1; i <= 100; i++) {
    net.rmVer(10);
    qDebug() << getId("贾宝玉") << jby->_data.ID;
  }
  net.printVers();
  //  net.printTable();
}

Home::~Home() { delete ui; }

void Home::readFile() {
  hashs.clear();
  names.clear();
  std::ifstream ifs;

  ifs.open(ID_FILE, std::ios::in);
  if (!ifs) {
    qDebug() << "ID_FILE open error!";
    exit(1);
  }
  std::string lineBuf;
  while (std::getline(ifs, lineBuf)) {
    int div = 0, len = lineBuf.size();
    for (; div < len && lineBuf[div] != ','; div++)
      ;
    QString name = QString::fromLocal8Bit(lineBuf.data(), div++);
    int id = QString::fromLocal8Bit(lineBuf.data() + div, len - div).toInt();
    //    qDebug() << QString("%1 -> %2").arg(name).arg(id);

    net.addVer({id, name});
    hashs.insert(name, net.getVer(id));
  }
  ifs.close();

  ifs.open(REL_FILE, std::ios::in);
  if (!ifs) {
    qDebug() << "REL_FILE open error!";
    exit(1);
  }
  while (getline(ifs, lineBuf)) {
    auto qBuf = QString::fromLocal8Bit(lineBuf.data());
    qBuf = qBuf.left(qBuf.size() - 1);
    auto li = qBuf.split(',');
    //    qDebug() << li;
    auto it = li.begin();
    int a, b;
    a = getId(*it++);
    b = getId(*it++);
    qBuf = *it;
    //    qDebug() << QString("<%1, %2> = %3").arg(a).arg(b).arg(qBuf);

    net.addArc(a, b, {QString("<%1,%2>").arg(a).arg(b)});
  }

  ifs.close();
}
