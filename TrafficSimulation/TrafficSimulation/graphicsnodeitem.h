#ifndef GRAPHICSNODEITEM_H
#define GRAPHICSNODEITEM_H

#include <QGraphicsItem>

class GraphicsNodeItem : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
	GraphicsNodeItem(QGraphicsItem *parent = 0);
	GraphicsNodeItem(QPointF normPos, QGraphicsItem *parent=0);
	GraphicsNodeItem(QPointF normPos, int no, QGraphicsItem *parent=0);
	~GraphicsNodeItem();

	void setNormPos(QPointF);
	QPointF normPos() const;
	void setNo(int);
	int no() const;
	// 重载
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	// 设置绘制属性
	GraphicsNodeItem & setRadius(qreal radius);
	GraphicsNodeItem & setHaveBorder(bool haveBorder);
	GraphicsNodeItem & setBorderColor(QColor borderColor);
	GraphicsNodeItem & setInnerColor(QColor innerColor);
	// 检查最近节点, 并设为邻居
	void checkNeighbour(GraphicsNodeItem*);
	// 获取半径
	qreal radius() const;
	// 设置编号item
	GraphicsNodeItem & setNoTextItem(QGraphicsItem*);

	void checkNoItemVisible();

signals:
	void sendNodeInfoToStatus(QString);
	void clearNodeInfoFromStatus();

protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
	

private:
	void init();
	

private:
	QPointF mNormPos;
	int mNo;
	qreal mRadius;
	QColor mBorderColor;
	QColor mInnerColor;
	bool mHaveBorder;
	// 最邻近的节点
	GraphicsNodeItem* mNeignbour;
	qreal mNearestDistance;
	QGraphicsItem* mNoTextItem;

};

#endif // GRAPHICSNODEITEM_H
