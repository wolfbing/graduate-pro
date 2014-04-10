#include "busnumgraphicsscene.h"

#include "graphicsscene.h"
#include "graphicsbusedgeitem.h"
#include "Edge.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"

BusNumGraphicsScene::BusNumGraphicsScene(QObject *parent)
	: GraphicsScene(parent)
{
	init();
	addLegend();
}

BusNumGraphicsScene::~BusNumGraphicsScene()
{

}


void BusNumGraphicsScene::updateItems()
{
	QListIterator<GraphicsBusEdgeItem*> edgeIte(mEdgeList);
	QListIterator<Node*> nodeIte(mNodeDataList);
	GraphicsBusEdgeItem * edgeItem;
	Node * tmpNode;
	while (nodeIte.hasNext())
	{
		tmpNode = nodeIte.next();
		tmpNode->setSceneCoor(normCoorToSceneCoor(tmpNode->coor()));
	}
	while (edgeIte.hasNext())
	{
		edgeItem = edgeIte.next();
		edgeItem->advance();
	}
}

void BusNumGraphicsScene::doSomething()
{

}



void BusNumGraphicsScene::addItems()
{
	QListIterator<Edge*> edgeIte(mEdgeDataList);
	Edge * tmpEdge;
	GraphicsBusEdgeItem * edgeItem;
	int colorIndex;
	while (edgeIte.hasNext())
	{
		tmpEdge = edgeIte.next();
		edgeItem = new GraphicsBusEdgeItem;
		colorIndex = tmpEdge->busNum()<6 ? tmpEdge->busNum() : 6; 
		edgeItem->setEdgeData(tmpEdge).setInnerColor(mColorList.at(colorIndex))
			.setWidth(mWidthList.at(colorIndex)).setHaveBorder(false).setZValue(mZValueList.at(colorIndex));
		addItem(edgeItem);
		connect(edgeItem, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(edgeItem, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus()) );
		mEdgeList << edgeItem;
	}
}

void BusNumGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(QStringLiteral("0条公交线路"), LegendElement::LINE, mWidthList.at(0), mColorList.at(0));
	elements << LegendElement(QStringLiteral("1条公交线路"), LegendElement::LINE, mWidthList.at(1), mColorList.at(1));
	elements << LegendElement(QStringLiteral("2条公交线路"), LegendElement::LINE, mWidthList.at(2), mColorList.at(2));
	elements << LegendElement(QStringLiteral("3条公交线路"), LegendElement::LINE, mWidthList.at(3), mColorList.at(3));
	elements << LegendElement(QStringLiteral("4条公交线路"), LegendElement::LINE, mWidthList.at(4), mColorList.at(4));
	elements << LegendElement(QStringLiteral("5条公交线路"), LegendElement::LINE, mWidthList.at(5), mColorList.at(5));
	elements << LegendElement(QStringLiteral(">=6条公交线路"), LegendElement::LINE, mWidthList.at(6), mColorList.at(6));
	Legend * legend = new Legend(elements);
	LegendProxy* proxy = new LegendProxy;
	proxy->setWidget(legend);
	addItem(proxy);
}

void BusNumGraphicsScene::init()
{
	mWidthList << 2 << 2 << 2 << 3 << 3 << 3 << 3;
	mColorList << QColor(54,4,255) << QColor(28,255,232) << QColor(106,251,0)
		<< QColor(225,192,0) << QColor(252,153,103) << QColor(251,0,1) << QColor(128,0,0);
	mZValueList << 0 << 1 << 2 << 3 << 4 << 5 << 6;


}
