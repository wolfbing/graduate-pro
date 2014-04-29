#include "speedgraphicsscene.h"

#include "graphicssidelineitem.h"
#include "Speed.h"
#include "Edge.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"


SpeedGraphicsScene::SpeedGraphicsScene(QObject *parent)
	: GraphicsScene(parent)
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
	elements << LegendElement("<=10", LegendElement::LINE, mWidthList.at(0), mColorList.at(0));
	elements << LegendElement("10-20", LegendElement::LINE, mWidthList.at(1), mColorList.at(1));
	elements << LegendElement("20-30", LegendElement::LINE, mWidthList.at(2), mColorList.at(2));
	elements << LegendElement("30-40", LegendElement::LINE, mWidthList.at(3), mColorList.at(3));
	elements << LegendElement("40-60", LegendElement::LINE, mWidthList.at(4), mColorList.at(4));
	elements << LegendElement(">=60", LegendElement::LINE, mWidthList.at(5), mColorList.at(5));
	Legend* legend = new Legend(elements);
	LegendProxy* proxy = new LegendProxy(legend);
	addItem(proxy);
}

void SpeedGraphicsScene::updateItems()
{
	GraphicsScene::updateItems();
	QListIterator<GraphicsSideLineItem*> ite(mSideLineItemList);
	GraphicsSideLineItem* item;
	while (ite.hasNext())
	{
		item = ite.next();
		item->advance();
	}
}
