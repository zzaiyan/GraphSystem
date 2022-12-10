#ifndef NET_H
#define NET_H

#define DefaultSize 20
#define TT template <class VerData, class ArcData>

#include <QDebug>
#include <QString>
#include <list>
#include <map>
#include <vector>
using std::list;
using std::map;
using std::vector;

template <class VerData, class ArcData> class ALNet {
public:
  struct VerNode { // 顶点
    int id;
    VerData _data;
  };
  struct ArcNode { // 有向边
    VerNode *from, *to;
    ArcData _data;
  };

private:
  int verNum, arcNum;
  vector<VerNode *> vers;              // 顶点数组
  vector<list<ArcNode>> outAdj, inAdj; // 顶点对应的邻接表

public:
  ALNet(const int s = DefaultSize) : verNum(s) {
    for (int i = 0; i < s; i++) // initialize
      vers.push_back(new VerNode{i, {}});
    inAdj.reserve(s), outAdj.reserve(s);
  }
  // 获取下标对应的顶点指针
  VerNode *getVer(int id) { return vers[id]; }
  // 获取顶点序偶对应的边指针
  ArcNode *getArc(int a, int b) {
    ArcNode *arc = nullptr;
    for (auto it : outAdj[a])
      if (it.to->id == b) {
        arc = &it;
        break;
      }
    return arc;
  }
  // 尾插顶点并赋值
  void addVer(const VerData &e) {
    vers.push_back(new VerNode{verNum++, e});
    inAdj.push_back({});
    outAdj.push_back({});
  }
  // 尾插顶点
  void addVer() { addVer({}); }
  // 加边
  void addArc(int a, int b, const ArcData &e) {
    outAdj[a].push_back({getVer(a), getVer(b), e});
    outAdj[b].push_back({getVer(b), getVer(a), e});
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
    qDebug() << "Origin ArcData = " << arc->_data;
    if (arc == nullptr)
      return false;
    arc->_data = e;
    return true;
  }

  ArcData rmArc(int a, int b) {
    auto arc = getArc(a, b);
    if (arc == nullptr)
      return ArcData{};
    auto tmp = arc->_data;
    auto &L = outAdj[a];
    L.clear();
    //    delete arc;
    return tmp;
  }
};

#undef TT
#endif // NET_H
