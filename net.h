#ifndef NET_H
#define NET_H

#include <QDebug>
#include <QString>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <vector>

using std::list;
using std::map;
using std::queue;
using std::stack;
using std::vector;

template <class VerData, class ArcData> class ALNet {
public:
  struct ArcNode;
  struct VerNode { // 顶点
    int id;
    VerData _data;
    list<ArcNode> _Adj, _rAdj;
    VerNode(int i = -1) : id(i) {}
    VerNode(int i, const VerData &e) : id(i), _data(e) {}
  };
  struct ArcNode { // 有向边
    VerNode *from = nullptr;
    VerNode *to = nullptr;
    ArcData _data;
  };

private:
  vector<VerNode *> vers; // 顶点数组

  int fromNum(const ArcNode &a) { return a.from->id; }    // 获取起点下标
  int toNum(const ArcNode &a) { return a.to->id; }        // 获取终点下标
  list<ArcNode> &Adj(int id) { return vers[id]->_Adj; }   // 获取邻接表
  list<ArcNode> &rAdj(int id) { return vers[id]->_rAdj; } // 获取逆邻接表

public:
  ALNet(const int s = 0) {
    for (int i = 0; i < s; i++) // initialize
      vers.push_back(new VerNode{i, {}});
  }
  // 获取下标对应的顶点指针
  VerNode *getVer(int id) { return vers[id]; }
  // 获取顶点序偶对应的边指针
  ArcNode *getArc(int a, int b) {
    ArcNode *arc = nullptr;
    for (auto it = Adj(a).begin(); it != Adj(a).end(); it++)
      if (it->to->id == b) {
        arc = &(*it);
        break;
      }
    return arc;
  }

  int getVerNum() const { return vers.size(); }
  int inDegree(int id) const { return rAdj(id).size(); }
  int outDegree(int id) const { return Adj(id).size(); }

  // 尾插顶点并赋值
  void addVer(const VerData &e) { vers.push_back(new VerNode{vers.size(), e}); }
  // 尾插顶点
  void addVer() { addVer({}); }
  // 加边
  void addArc(int a, int b, const ArcData &e) {
    Adj(a).push_back({getVer(a), getVer(b), e});
    rAdj(b).push_back({getVer(b), getVer(a), e});
  }
  // 加边
  void addArc(int a, int b) { addArc(a, b, {}); }
  // 判断边
  bool haveArc(int a, int b) { return getArc(a, b) != nullptr; }
  // 改变顶点的数据
  bool setVer(int id, const VerData &e) {
    auto ver = getVer(id);
    if (ver == nullptr)
      return false;
    ver->_data = e;
    return true;
  }
  // 改变边的数据
  bool setArc(int a, int b, const ArcData &e) {
    auto arc = getArc(a, b);
    //    auto str = arc->_data;
    if (arc == nullptr)
      return false;
    arc->_data = e;
    return true;
  }

  ArcData rmArc(int a, int b) {
    ArcData ret;
    auto it1 = Adj(a).begin();
    auto it2 = rAdj(b).begin();
    for (; it1 != Adj(a).end(); it1++)
      if (it1->to->id == b) {
        ret = it1->_data;
        break;
      }
    for (; it2 != rAdj(b).end(); it2++)
      if (it2->to->id == a)
        break;
    ret = it1->_data;
    Adj(a).erase(it1);
    rAdj(b).erase(it2);
    return ret;
  }

  VerData rmVer(int id) {
    for (int i = 0; i < vers.size(); i++) {
      if (i == id)
        continue;
      queue<std::pair<int, int>> que;
      for (auto &e : Adj(i)) {
        int a = fromNum(e), b = toNum(e);
        if (a == id || b == id)
          que.push({a, b});
      }
      while (que.size()) {
        rmArc(que.front().first, que.front().second);
        qDebug() << QString("delete <%1,%2>.")
                        .arg(que.front().first)
                        .arg(que.front().second);
        que.pop();
      }
    }
    delete vers[id];
    for (int i = id + 1; i < vers.size(); i++)
      vers[i - 1] = vers[i];
    vers.pop_back();
  }

  void printVers() {
    QString buf;
    for (int i = 0; i < vers.size(); i++) {
      buf += (QString::number(vers[i]->_data) + " ");
    }
    qDebug() << buf;
  }

  QString getList(const list<ArcNode> &li) {
    QString buf;
    for (auto it = li.begin(); it != li.end(); it++) {
      if (it != li.begin())
        buf += " -> ";
      buf += QString::number(it->_data);
    }
    return buf;
  }

  void printTable() {
    qDebug() << "start print out table.";
    for (int i = 0; i < vers.size(); i++) {
      QString buf;
      buf += (QString::number(vers[i]->_data) + ": ");
      auto line = Adj(i);
      buf += getList(line);
      qDebug() << buf;
    }
    qDebug() << "start print in table.";
    for (int i = 0; i < vers.size(); i++) {
      QString buf;
      buf += (QString::number(vers[i]->_data) + ": ");
      auto line = rAdj(i);
      buf += getList(line);
      qDebug() << buf;
    }
  }
};

#endif // NET_H
