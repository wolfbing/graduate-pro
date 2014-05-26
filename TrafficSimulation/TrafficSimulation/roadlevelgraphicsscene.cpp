#include "roadlevelgraphicsscene.h"
#include "Edge.h"
#include "graphicssidelineitem.h"
#include "node.h"
#include "graphicsedgenetitem.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"
#include <QGraphicsProxyWidget>

RoadLevelGraphicsScene::RoadLevelGraphicsScene(QObject *parent)
	: RoadGraphicsScene(parent)
{
	init(); // 在其他操作前进行
	addLegend();

}

RoadLevelGraphicsScene::~RoadLevelGraphicsScene()
{

}


void RoadLevelGraphicsScene::init()
{
	mColorList << QColor(205,168,232) << QColor(249,126,128) << QColor(255,225,104)
		<< QColor(254,252,193) << QColor(151,189,253) << QColor(139,182,105) 
		<< QColor(250,158,37);
	//mBorderColorList << QColor(147,102,128) << QColor(186,98,96) << QColor(231,195,96) 
	//	<< QColor(221,217,188) << QColor(151,189,253) <<QColor(139,182,105) 
	//	<< QColor(231,160,37);
	//mHaveBorderList << true << true << true << true << false << false << true;
	//mWidthList << 7 << 6 << 6 << 5 << 2 << 2 << 9;
	mWidthList << 3 << 3 << 3 << 3 << 3 << 3 << 3;
	mZValueList << 6 << 4 << 3 << 2 << 1 << 0 << 5; 
	mLabelTextList << QStringLiteral("城市高架道路") << QStringLiteral("城市快速干道")
		<< QStringLiteral("城市主干道") << QStringLiteral("城市次干道")
		<< QStringLiteral("城市支路") << QStringLiteral("郊区公路")
		<< QStringLiteral("高速公路");

}

void RoadLevelGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(mLabelTextList.at(0),LegendElement::LINE,mWidthList.at(0),mColorList.at(0))
		<< LegendElement(mLabelTextList.at(1),LegendElement::LINE, mWidthList.at(1),mColorList.at(1))
		<< LegendElement(mLabelTextList.at(2),LegendElement::LINE, mWidthList.at(2),mColorList.at(2))
		<< LegendElement(mLabelTextList.at(3),LegendElement::LINE, mWidthList.at(3),mColorList.at(3))
		<< LegendElement(mLabelTextList.at(4),LegendElement::LINE, mWidthList.at(4),mColorList.at(4))
		<< LegendElement(mLabelTextList.at(5),LegendElement::LINE, mWidthList.at(5),mColorList.at(5))
		<< LegendElement(mLabelTextList.at(6),LegendElement::LINE, mWidthList.at(6),mColorList.at(6));
	mLegend = new Legend(elements);
	mLegendProxy = new LegendProxy;
	mLegendProxy->setWidget(mLegend);
	addItem(mLegendProxy);
}


void RoadLevelGraphicsScene::addItems()
{
	Edge* tmpEdge;
	GraphicsSideLineItem* item;
	QListIterator<Edge*> ite(mEdgeDataList);
	while (ite.hasNext())
	{
		tmpEdge = ite.next();
		item = new GraphicsSideLineItem;
		item->setEdgeData(tmpEdge);
		int level = tmpEdge->roadLevel();
		item->setWidth(mWidthList.at(level)).setColor(mColorList.at(level))
			.setZValue(mZValueList.at(level));
		item->setGraphType(GraphicsSideLineItem::RoadLevelGraph);
		mSideLineItemList << item;
		addItem(item);
		connect(item, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(item, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus()) );

	}
	
}

void RoadLevelGraphicsScene::updateItemsAttr()
{
	QListIterator<GraphicsSideLineItem*> itemIte(mSideLineItemList);
	GraphicsSideLineItem* item;
	Edge* tmpEdgeData;
	int index;
	while (itemIte.hasNext())
	{
		item = itemIte.next();
		tmpEdgeData = item->edgeData();
		index = tmpEdgeData->roadLevel();
		item->updateAttr(mColorList.at(index), mWidthList.at(index));

	}
	mLegend->updateAttr(mColorList, mWidthList);

}









