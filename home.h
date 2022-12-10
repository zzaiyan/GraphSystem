#ifndef HOME_H
#define HOME_H

#include "net.h"
#include <QHash>
#include <QString>
#include <QVector>
#include <QWidget>
#include <fstream>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
class Home;
}
QT_END_NAMESPACE

class Home : public QWidget {
  Q_OBJECT

public:
  Home(QWidget *parent = nullptr);
  ~Home();

protected:
  void readFile();

private:
  Ui::Home *ui;
  ALNet<int, int> net; // 有向网
  QHash<QString, int> hsId;
  QVector<QString> id2str;
};
#endif // HOME_H
