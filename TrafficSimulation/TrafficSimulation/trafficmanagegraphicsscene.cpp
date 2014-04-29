#include "trafficmanagegraphicsscene.h"

#include "graphicssidelineitem.h"
#include "Edge.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"

TrafficManageGraphicsScene::TrafficManageGraphicsScene(QObject *parent)
	: GraphicsScene(parent)
{
	init();
	addLegend();
}

TrafficManageGraphicsScene::~TrafficManageGraphicsScene()
{

}

void TrafficManageGraphicsScene::init()
{
	mColorList << QColor(240,129,0) << QColor(50,158,28) << QColor(0,122,204) << QColor(116,40,148)
		<< QColor(223,35,40) << QColor(158,158,158);
	mWidthList << 3 << 3 << 3 << 3 << 3 << 3;
	mZValueList << 6 << 5 << 4 << 3 << 2 << 1;
}

void TrafficManageGraphicsScene::addItems()
{
	QListIterator<Edge*> edgeDataIte(mEdgeDataList);
	Edge* edgeData;
	GraphicsSideLineItem * item;
	int index;
	while (edgeDataIte.hasNext())
	{
		edgeData = edgeDataIte.next();
		index = edgeData->trafficType()-1;
		item = new GraphicsSideLineItem;
		item->setColor(mColorList.at(index)).setWidth(mWidthList.at(index)).setEdgeData(edgeData)
			.setGraphType(GraphicsSideLineItem::TrafficTypeGraph).setZValue(mZValueList.at(index));
		connect(item, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(item, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus()) );
		mSideLineItemList << item;
		addItem(item);
	}
}

void TrafficManageGraphicsScene::updateItems()
{
	GraphicsScene::updateItems();
	QListIterator<GraphicsSideLineItem*> ite(mSideLineItemList);
	GraphicsSideLineItem * item;
	while (ite.hasNext())
	{
		item = ite.next();
		item->advance();
	}
}

void TrafficManageGraphicsScene::doSomething()
{

}

void TrafficManageGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(QStringLiteral("公共交通专用线"), LegendElement::LINE, mWidthList.at(0), mColorList.at(0)) ;
	elements << LegendElement(QStringLiteral("自行车专用线"), LegendElement::LINE, mWidthList.at(1), mColorList.at(1)) ;
	elements << LegendElement(QStringLiteral("客运专用线"), LegendElement::LINE, mWidthList.at(2), mColorList.at(2)) ;
	elements << LegendElement(QStringLiteral("机动车专用线"), LegendElement::LINE, mWidthList.at(3), mColorList.at(3)) ;
	elements << LegendElement(QStringLiteral("摩托车禁止通行线"), LegendElement::LINE, mWidthList.at(4), mColorList.at(4)) ;
	elements << LegendElement(QStringLiteral("非管理线"), LegendElement::LINE, mWidthList.at(5), mColorList.at(5)) ;
	Legend * legend = new Legend(elements);
	LegendProxy * proxy = new LegendProxy(legend);
	addItem(proxy);
}
