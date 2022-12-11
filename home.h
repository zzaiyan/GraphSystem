#ifndef HOME_H
#define HOME_H

#include "net.h"
#include "node.h"
#include <QHash>
#include <QString>
#include <QVector>
#include <QWidget>
#include <cstring>
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

  ALNet<RoleData, RelData> net; // 有向网

  QHash<QString, ALNet<RoleData, RelData>::VerNode *> hashs;
  QVector<QString> names;

  int getId(const QString &s) { return hashs[s]->_id; }
};
#endif // HOME_H
