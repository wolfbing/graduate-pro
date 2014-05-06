#include "busnumgraphicsscene.h"

#include "graphicsscene.h"
#include "graphicssidelineitem.h"
#include "Edge.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"

BusNumGraphicsScene::BusNumGraphicsScene(QObject *parent)
	: RoadGraphicsScene(parent)
{
	init();
	addLegend();
}

BusNumGraphicsScene::~BusNumGraphicsScene()
{

}

void BusNumGraphicsScene::addItems()
{
	QListIterator<Edge*> edgeIte(mEdgeDataList);
	Edge * tmpEdge;
	GraphicsSideLineItem * item;
	int colorIndex;
	while (edgeIte.hasNext())
	{
		tmpEdge = edgeIte.next();
		item = new GraphicsSideLineItem;
		colorIndex = tmpEdge->busNum()<6 ? tmpEdge->busNum() : 6; 
		item->setGraphType(GraphicsSideLineItem::BusNumGraph);
		item->setEdgeData(tmpEdge).setColor(mColorList.at(colorIndex))
			.setWidth(mWidthList.at(colorIndex)).setZValue(mZValueList.at(colorIndex));
		addItem(item);
		connect(item, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(item, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus()) );
		mSideLineItemList << item;
	}
}

void BusNumGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(mLabelTextList.at(0), LegendElement::LINE, mWidthList.at(0), mColorList.at(0));
	elements << LegendElement(mLabelTextList.at(1), LegendElement::LINE, mWidthList.at(1), mColorList.at(1));
	elements << LegendElement(mLabelTextList.at(2), LegendElement::LINE, mWidthList.at(2), mColorList.at(2));
	elements << LegendElement(mLabelTextList.at(3), LegendElement::LINE, mWidthList.at(3), mColorList.at(3));
	elements << LegendElement(mLabelTextList.at(4), LegendElement::LINE, mWidthList.at(4), mColorList.at(4));
	elements << LegendElement(mLabelTextList.at(5), LegendElement::LINE, mWidthList.at(5), mColorList.at(5));
	elements << LegendElement(mLabelTextList.at(6), LegendElement::LINE, mWidthList.at(6), mColorList.at(6));
	mLegend = new Legend(elements);
	mLegendProxy = new LegendProxy;
	mLegendProxy->setWidget(mLegend);
	addItem(mLegendProxy);
}

void BusNumGraphicsScene::init()
{
	mWidthList << 2 << 2 << 2 << 3 << 3 << 3 << 3;
	mColorList << QColor(54,4,255) << QColor(28,255,232) << QColor(106,251,0)
		<< QColor(225,192,0) << QColor(252,153,103) << QColor(251,0,1) << QColor(128,0,0);
	mZValueList << 0 << 1 << 2 << 3 << 4 << 5 << 6;
	mLabelTextList << QStringLiteral("0条公交线路") << QStringLiteral("1条公交线路")
		<< QStringLiteral("2条公交线路") << QStringLiteral("3条公交线路")
		<< QStringLiteral("4条公交线路") << QStringLiteral("5条公交线路")
		<< QStringLiteral(">=6条公交线路");

}

void BusNumGraphicsScene::updateItemsAttr()
{
	QListIterator<GraphicsSideLineItem*> itemIte(mSideLineItemList);
	Edge * tmpEdge;
	GraphicsSideLineItem * item;
	int index;
	while (itemIte.hasNext())
	{
		item = itemIte.next();
		tmpEdge = item->edgeData();
		index = tmpEdge->busNum()<6 ? tmpEdge->busNum() : 6;
		item->updateAttr(mColorList.at(index), mWidthList.at(index));
	}
	mLegend->updateAttr(mColorList, mWidthList);
}
