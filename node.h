#ifndef NODE_H
#define NODE_H
#include <QDebug>
#include <QString>

struct RoleData {
  int ID, color;
  QString name;
  QString desc;

  RoleData() = default;
  RoleData(int x, const QString &s) : ID(x), name(s) {}
  void print() { qDebug() << QString("Role %1: %2").arg(ID).arg(name); }
};

struct RelData {
  QString label;

  RelData() = default;
  void print() { qDebug() << QString("Label: %1").arg(label); }
};

#endif // NODE_H
