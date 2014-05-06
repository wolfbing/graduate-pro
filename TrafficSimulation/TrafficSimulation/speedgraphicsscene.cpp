#include "speedgraphicsscene.h"

#include "graphicssidelineitem.h"
#include "Speed.h"
#include "Edge.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"


SpeedGraphicsScene::SpeedGraphicsScene(QObject *parent)
	: RoadGraphicsScene(parent)
{
	init();
	addLegend();
}

SpeedGraphicsScene::~SpeedGraphicsScene()
{

}

void SpeedGraphicsScene::init()
{
	mColorList << QColor(158,158,158) << QColor(0,122,204) << QColor(50,158,28) 
		<<  QColor(230,204,58) << QColor(240,129,0) << QColor(223,35,40);
	mWidthList << 3 << 3 << 3 << 3 << 3 << 3;
	mZValueList << 1 << 2 << 3 << 4 << 5 << 6;
	mLabelTextList << "<=10" << "10-20" << "20-30" << "30-40" << "40-60" << ">=60";
}

void SpeedGraphicsScene::addItems()
{
	QListIterator<Edge*> edgeDataIte(mEdgeDataList);
	Edge* tmpEdgeData;
	qreal speed;
	GraphicsSideLineItem * item;
	int index;
	while (edgeDataIte.hasNext())
	{
		tmpEdgeData = edgeDataIte.next();
		item = new GraphicsSideLineItem;
		speed = tmpEdgeData->speed()->speed();
		if(speed<=10)
			index = 0;
		else if(speed<=20)
			index = 1;
		else if(speed<=30)
			index = 2;
		else if(speed<=40)
			index = 3;
		else if(speed<=60)
			index = 4;
		else
			index = 5;

		item->setEdgeData(tmpEdgeData).setColor(mColorList.at(index)).setWidth(mWidthList.at(index))
			.setZValue(mZValueList.at(index));
		connect(item, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(item, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus()) );
		mSideLineItemList << item;
		addItem(item);
	}
}

void SpeedGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(mLabelTextList.at(0), LegendElement::LINE, mWidthList.at(0), mColorList.at(0));
	elements << LegendElement(mLabelTextList.at(1), LegendElement::LINE, mWidthList.at(1), mColorList.at(1));
	elements << LegendElement(mLabelTextList.at(2), LegendElement::LINE, mWidthList.at(2), mColorList.at(2));
	elements << LegendElement(mLabelTextList.at(3), LegendElement::LINE, mWidthList.at(3), mColorList.at(3));
	elements << LegendElement(mLabelTextList.at(4), LegendElement::LINE, mWidthList.at(4), mColorList.at(4));
	elements << LegendElement(mLabelTextList.at(5), LegendElement::LINE, mWidthList.at(5), mColorList.at(5));
	Legend* legend = new Legend(elements);
	mLegendProxy = new LegendProxy(legend);
	addItem(mLegendProxy);
}

void SpeedGraphicsScene::updateItemsAttr()
{
	QListIterator<GraphicsSideLineItem*> itemIte(mSideLineItemList);
	Edge* tmpEdgeData;
	qreal speed;
	GraphicsSideLineItem * item;
	int index;
	while (itemIte.hasNext())
	{
		item = itemIte.next();
		tmpEdgeData = item->edgeData();
		speed =tmpEdgeData->speed()->speed();
		if(speed<=10)
			index = 0;
		else if(speed<=20)
			index = 1;
		else if(speed<=30)
			index = 2;
		else if(speed<=40)
			index = 3;
		else if(speed<=60)
			index = 4;
		else
			index = 5;
		item->setColor(mColorList.at(index)).setWidth(mWidthList.at(index));
	}
	mLegendProxy->updateAttr(mColorList, mWidthList);

}


