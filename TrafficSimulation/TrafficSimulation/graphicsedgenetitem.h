#ifndef QGRAPHICSEDGETNETITEM_H
#define QGRAPHICSEDGETNETITEM_H

#include <QGraphicsItem>
#include "Edge.h"

class GraphicsEdgetNetItem : public QGraphicsItem
{

public:
	GraphicsEdgetNetItem(QGraphicsItem *parent = 0);
	~GraphicsEdgetNetItem();

	void addEdge(const Edge &);

	void advance();

	// ÷ÿ‘ÿ–È∫Ø ˝
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QPainterPath shape() const;
	 
	// …Ë÷√ªÊÕº Ù–‘
	GraphicsEdgetNetItem & setWidth(qreal width);
	GraphicsEdgetNetItem & setBorderColor(QColor borderColor);
	GraphicsEdgetNetItem & setInnerColor(QColor innerColor);
	GraphicsEdgetNetItem & setHaveBorder(bool haveBorder);

private:
	void init();

private:
	QList<Edge> mEdges;
	qreal mEdgeWidth;
	QColor mBorderColor;
	QColor mInnerColor;
	bool mHaveBorder;
	
};

#endif // QGRAPHICSEDGETNETITEM_H
