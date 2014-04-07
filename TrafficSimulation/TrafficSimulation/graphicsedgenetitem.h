#ifndef QGRAPHICSEDGETNETITEM_H
#define QGRAPHICSEDGETNETITEM_H

#include <QGraphicsItem>
#include "Edge.h"

class GraphicsEdgetNetItem : public QGraphicsItem
{

public:
	GraphicsEdgetNetItem(QGraphicsItem *parent = 0);
	~GraphicsEdgetNetItem();

	void addEdgeData(Edge*);

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

	qreal edgeWidth() const ;
	QColor innerColor() const;
	QColor borderColor() const;

private:
	void init();

private:
	QList<Edge*> mEdgeDataList;
	// ªÊÕº Ù–‘
	qreal mEdgeWidth;
	QColor mBorderColor;
	QColor mInnerColor;
	bool mHaveBorder;
	
};

#endif // QGRAPHICSEDGETNETITEM_H
