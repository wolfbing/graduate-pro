#ifndef GRAPHICSNODEITEM_H
#define GRAPHICSNODEITEM_H

#include <QGraphicsItem>

class GraphicsNodeItem : public QGraphicsItem
{
	//Q_OBJECT

public:
	GraphicsNodeItem(QGraphicsItem *parent = 0);
	GraphicsNodeItem(QPointF , QGraphicsItem *parent=0);
	~GraphicsNodeItem();

	void setNormPos(QPointF);
	QPointF normPos() const;
	void setNo(int);
	int no() const;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;

private:
	void init();

private:
	QPointF mNormPos;
	int mNo;
	qreal mRadius;

};

#endif // GRAPHICSNODEITEM_H
