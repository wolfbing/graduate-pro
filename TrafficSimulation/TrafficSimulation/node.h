
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
	int no() const;
	QPointF sceneCoor() const;
	// set
	Node& setCoor(QPointF);
	Node& setNo(int);
	Node& setSceneCoor(QPointF);

private:
	QPointF mCoor; //坐标
	QPointF mSceneCoor; // 在scene中的坐标
	int mNo; //编号


};



inline uint qHash(Node n, uint seed = 0){
	return 0;
}


qreal length(QPair<Node,Node> pair);





#endif // !NODE
