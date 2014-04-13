#include "turnrestrictgraphicsscene.h"
#include "graphicsnodeitem.h"
#include "graphicsedgenetitem.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"


TurnRestrictGraphicsScene::TurnRestrictGraphicsScene(QObject *parent)
	: GraphicsScene(parent)
{
	init();
	addLegend();
}

TurnRestrictGraphicsScene::~TurnRestrictGraphicsScene()
{

}

void TurnRestrictGraphicsScene::addItems()
{
	QListIterator<Node*> nodeIte(mNodeDataList);
	GraphicsNodeItem * tmpNodeItem;
	Node* tmpNodeData;
	int index;
	while (nodeIte.hasNext())
	{
		tmpNodeData = nodeIte.next();
		index = tmpNodeData->haveTurnRestrict() ? 1 : 0;
		tmpNodeItem = new GraphicsNodeItem;
		tmpNodeItem->setNodeData(tmpNodeData).setHaveBorder(mNodeHaveBorderList.at(index))
			.setRadius(mNodeRadiusList.at(index)).setInnerColor(mNodeInnerColorList.at(index))
			.setBorderColor(mNodeBorderColorList.at(index)).setNodeItemType(GraphicsNodeItem::Restriction);
		addItem(tmpNodeItem);
		connect(tmpNodeItem, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(tmpNodeItem, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus() ) );
		mNodeItemList << tmpNodeItem;
	}
	QListIterator<Edge*> edgeDataIte(mEdgeDataList);
	Edge * tmpEdgeData;
	mEdgeNetItem = new GraphicsEdgeNetItem;
	mEdgeNetItem->setHaveBorder(mEdgeNetHaveBorder).setInnerColor(mEdgeNetInnerColor)
		.setBorderColor(mEdgeNetBorderColor).setWidth(mEdgeNetWidth);
	while (edgeDataIte.hasNext())
	{
		tmpEdgeData = edgeDataIte.next();
		mEdgeNetItem->addEdgeData(tmpEdgeData);
	}
	addItem(mEdgeNetItem);

}

void TurnRestrictGraphicsScene::updateItems()
{
	GraphicsScene::updateItems();
	QListIterator<GraphicsNodeItem*> nodeItemIte(mNodeItemList);
	GraphicsNodeItem* tmpNodeItem;
	while (nodeItemIte.hasNext())
	{
		tmpNodeItem = nodeItemIte.next();
		tmpNodeItem->setPos(tmpNodeItem->nodeData()->sceneCoor());

	}
	mEdgeNetItem->advance();
}

void TurnRestrictGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(QStringLiteral("无转向限制交叉"), LegendElement::THICK_DOT, mNodeRadiusList.at(0),
		mNodeInnerColorList.at(0), mNodeBorderColorList.at(0));
	elements << LegendElement(QStringLiteral("转向限制交叉"), LegendElement::THICK_DOT, mNodeRadiusList.at(1),
		mNodeInnerColorList.at(1), mNodeBorderColorList.at(1));
	elements << LegendElement(QStringLiteral("路段"), LegendElement::THICK_LINE, mEdgeNetWidth,
		mEdgeNetInnerColor, mEdgeNetBorderColor);
	Legend * legend = new Legend(elements);
	LegendProxy * proxy = new LegendProxy;
	proxy->setWidget(legend);
	addItem(proxy);

}

void TurnRestrictGraphicsScene::init()
{
	mNodeBorderColorList << QColor() << QColor();
	mNodeInnerColorList << QColor(0,255,0) << QColor(255,0,0);
	mNodeRadiusList << 4 << 4;
	mNodeHaveBorderList << true << true;
	mEdgeNetBorderColor =  QColor(203,168,87);
	mEdgeNetHaveBorder = true;
	mEdgeNetWidth = 4.0;
	mEdgeNetInnerColor = QColor(253,206,102);

}

void TurnRestrictGraphicsScene::doSomething()
{

}
