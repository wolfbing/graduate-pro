
#ifndef NODE
#define  NODE

#include <QtCore>
#include "node.h"
#include "Normal.h"

class Positionable{
public:
	virtual QPointF coor() const = 0;
	virtual void setCoor(const QPointF& p) = 0;
};
/*
用于存放与节点相关的数据
我非常诟病这个类, 因为它通常是浪费内存的, 因为在特定情景中只用到其中很少的信息
*/
class Node
	: virtual public Normal
{
public:
	Node(){};
	Node(const Node & );
	Node & operator = (const Node & );
	Node(QPointF, int);
	bool operator==(const Node & node)const;

	Rect border() const;
	void norm(qreal, QPointF);

	// get
	QPointF coor() const;
	int id() const;
	int no() const;
	QPointF sceneCoor() const;
	int junctionType() const;
	bool inScale() const;
	// set
	Node& setCoor(QPointF);
	Node& setNo(int);
	Node& setSceneCoor(QPointF);
	Node& setJunctionType(int);
	Node& setInScale(bool);
	Node& setId(int);
	// 计算和其他node距离
	qreal dis(Node*)const;
	qreal sceneDis(Node*)const;

private:
	QPointF mCoor; //坐标
	QPointF mSceneCoor; // 在scene中的坐标
	int mId; //rowid
	int mNo; //编号
	int mJunctionType; // 连接类型
	bool mInScale; // 是否在范围内


};



inline uint qHash(Node n, uint seed = 0){
	return 0;
}


qreal length(QPair<Node,Node> pair);





#endif // !NODE
