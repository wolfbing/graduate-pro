#pragma once

#include "node.h"

/*
用于存放与边有关的数据, 诟病与Node相同
边是有向的
*/
class Edge
{
public:
	Edge(){};
	///////// 不使用有参数的构造函数, 因为根本无法确定每次哪些数据是必须的
	Edge(const Edge & );
	Edge& operator=(const Edge &);
	bool operator==(const Edge &);
	~Edge(void);

	// get
	Node * sourceNode() const;
	Node * destNode() const;
	uint roadLevel() const;
	QRectF sceneBorder() const;
	// set
	Edge & setSourceNode(Node *);
	Edge & setDestNode(Node *);
	Edge & setRoadLevel(uint);


private:
	// 边依赖于外部独立的节点
	Node * mSourceNode;
	Node * mDestNode;

	uint mRoadLevel;


};

