#include "roadtypegraphicsscene.h"
#include "graphicssidelineitem.h"
#include "Edge.h"
#include "graphicsedgeitem.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"

RoadTypeGraphicsScene::RoadTypeGraphicsScene(QObject *parent)
	: RoadGraphicsScene(parent)
{
	init();
	addLegend();
}

RoadTypeGraphicsScene::~RoadTypeGraphicsScene()
{

}

void RoadTypeGraphicsScene::init()
{
	mColorList << QColor(240,129,0) << QColor(116,40,148) << QColor(50,158,28) 
		<< QColor(223,35,40) << QColor(0,122,204);
	mWidthList << 3 << 3 << 3 << 3 << 3;
	mZValueList << 5 << 4 << 3 << 2 << 1;
	mLabelTextList << QStringLiteral("双向通行道路,\n有中央(物体)分隔")
		<< QStringLiteral("双向通行道路,\n无中央(物体)分隔")
		<< QStringLiteral("单向通行道路,\n可通行方向")
		<< QStringLiteral("单向通行道路,\n不可通行方向")
		<< QStringLiteral("单向通行道路,\n不可通行方向,\n但公交车辆可通行");
}

void RoadTypeGraphicsScene::addItems()
{
	QListIterator<Edge*> edgeDataIte(mEdgeDataList);
	Edge * edgeData;
	GraphicsSideLineItem * item;
	int index;
	while (edgeDataIte.hasNext())
	{
		edgeData = edgeDataIte.next();
		index = edgeData->roadType() - 1;
		item = new GraphicsSideLineItem;
		item->setEdgeData(edgeData).setColor(mColorList.at(index)).setWidth(mWidthList.at(index))
			.setZValue(mZValueList.at(index));
		item->setGraphType(GraphicsSideLineItem::RoadTypeGraph);
		connect(item, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(item, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus()) );
		mSideLineItemList << item;
		addItem(item);
	}
}


void RoadTypeGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(mLabelTextList.at(0), LegendElement::LINE, mWidthList.at(0), mColorList.at(0));
	elements << LegendElement(mLabelTextList.at(1), LegendElement::LINE, mWidthList.at(1), mColorList.at(1));
	elements << LegendElement(mLabelTextList.at(2), LegendElement::LINE, mWidthList.at(2), mColorList.at(2));
	elements << LegendElement(mLabelTextList.at(3), LegendElement::LINE, mWidthList.at(3), mColorList.at(3));
	elements << LegendElement(mLabelTextList.at(4), LegendElement::LINE, mWidthList.at(4), mColorList.at(4));
	Legend* legend = new Legend(elements);
	mLegendProxy = new LegendProxy(legend);
	addItem(mLegendProxy);
}

void RoadTypeGraphicsScene::updateItemsAttr()
{
	QListIterator<GraphicsSideLineItem*> itemIte(mSideLineItemList);
	Edge * edgeData;
	GraphicsSideLineItem * item;
	int index;
	while (itemIte.hasNext())
	{
		item = itemIte.next();
		edgeData = item->edgeData();
		index = edgeData->roadType() - 1;
		item->updateAttr(mColorList.at(index), mWidthList.at(index));
	}
	mLegendProxy->updateAttr(mColorList, mWidthList);
}

