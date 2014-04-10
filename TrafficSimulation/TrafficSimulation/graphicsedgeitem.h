#ifndef GRAPHICSEDGEITEM_H
#define GRAPHICSEDGEITEM_H

#include <QGraphicsItem>
#include "Communicate.h"
#include <QGraphicsItem>

class Edge;

class GraphicsEdgeItem :public Communicate, public QGraphicsItem //public QGraphicsItem
{
	Q_OBJECT

public:
	GraphicsEdgeItem(QGraphicsItem *parent = 0);
	~GraphicsEdgeItem();

	//// set
	GraphicsEdgeItem& setWidth(qreal);
	GraphicsEdgeItem& setBorderColor(QColor);
	GraphicsEdgeItem& setInnerColor(QColor);
	GraphicsEdgeItem& setEdgeData(Edge*); // 设置Edge数据
	GraphicsEdgeItem& setHaveBorder(bool);

	///// get
	Edge* edgeData() const;

	void advance();

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;

	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

	

protected:
	Edge* mEdgeData;

	// 绘图属性
	qreal mWidth;
	QColor mInnerColor;
	QColor mBorderColor;

	//
	bool mHaveBorder;

	
};

#endif // GRAPHICSEDGEITEM_H
