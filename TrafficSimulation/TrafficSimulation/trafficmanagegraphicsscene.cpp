#include "trafficmanagegraphicsscene.h"

#include "graphicssidelineitem.h"
#include "Edge.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"

TrafficManageGraphicsScene::TrafficManageGraphicsScene(QObject *parent)
	: RoadGraphicsScene(parent)
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
	mLabelTextList << QStringLiteral("公共交通专用线") << QStringLiteral("自行车专用线")
		<< QStringLiteral("客运专用线") << QStringLiteral("机动车专用线")
		<< QStringLiteral("摩托车禁止通行线") << QStringLiteral("非管理线");
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


void TrafficManageGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(mLabelTextList.at(0), LegendElement::LINE, mWidthList.at(0), mColorList.at(0)) ;
	elements << LegendElement(mLabelTextList.at(1), LegendElement::LINE, mWidthList.at(1), mColorList.at(1)) ;
	elements << LegendElement(mLabelTextList.at(2), LegendElement::LINE, mWidthList.at(2), mColorList.at(2)) ;
	elements << LegendElement(mLabelTextList.at(3), LegendElement::LINE, mWidthList.at(3), mColorList.at(3)) ;
	elements << LegendElement(mLabelTextList.at(4), LegendElement::LINE, mWidthList.at(4), mColorList.at(4)) ;
	elements << LegendElement(mLabelTextList.at(5), LegendElement::LINE, mWidthList.at(5), mColorList.at(5)) ;
	Legend * legend = new Legend(elements);
	mLegendProxy = new LegendProxy(legend);
	addItem(mLegendProxy);
}

void TrafficManageGraphicsScene::updateItemsAttr()
{
	QListIterator<GraphicsSideLineItem*> itemIte(mSideLineItemList);
	Edge* edgeData;
	GraphicsSideLineItem * item;
	int index;
	while (itemIte.hasNext())
	{
		item = itemIte.next();
		edgeData = item->edgeData();
		index = edgeData->trafficType()-1;
		item->updateAttr(mColorList.at(index), mWidthList.at(index));
	}
	mLegendProxy->updateAttr(mColorList, mWidthList);
}
