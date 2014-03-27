
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

struct NodeWithCoorNo
	: virtual public Normal
{
	QPointF mCoor; //×ø±ê
	int mNo; //±àºÅ

	NodeWithCoorNo(){};
	NodeWithCoorNo(const NodeWithCoorNo & );
	NodeWithCoorNo & operator = (const NodeWithCoorNo & );
	NodeWithCoorNo(QPointF, int);
	bool operator==(const NodeWithCoorNo & node)const;

	Rect border() const;
	void norm(qreal, QPointF);
};



inline uint qHash(NodeWithCoorNo n, uint seed = 0){
	return 0;
}


qreal length(QPair<NodeWithCoorNo,NodeWithCoorNo> pair);


#endif // !NODE
