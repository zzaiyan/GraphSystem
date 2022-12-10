#ifndef NETNODE_H
#define NETNODE_H

#include <QString>

// 顶点
struct VNode {
  int _id;
  QString _name;

  VNode() {}
};

// 边
struct EdNode {
  VNode *fr, *to;
  QString _label;
  EdNode() {}
};

#endif // NETNODE_H
