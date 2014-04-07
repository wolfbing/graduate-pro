#include "graphicsnodenotextitem.h"

GraphicsNodeNoTextItem::GraphicsNodeNoTextItem(GraphicsNodeItem *parent)
	: QGraphicsTextItem(parent)
{
	parent->setNoTextItem(this);
	QGraphicsTextItem::setPlainText(QString::number(parent->nodeData()->no() )  );
	QGraphicsTextItem::setPos(parent->radius()+3, -parent->radius()-10);
	hide(); // 初始隐藏, 后面根据节点间的距离考虑显示
	// 渲染设置
	setCacheMode(QGraphicsItem::ItemCoordinateCache);
	setEnabled(false);
}

GraphicsNodeNoTextItem::~GraphicsNodeNoTextItem()
{

}
