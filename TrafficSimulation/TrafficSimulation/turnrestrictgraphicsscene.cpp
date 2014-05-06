#include "turnrestrictgraphicsscene.h"
#include "graphicsnodeitem.h"
#include "graphicsedgenetitem.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"


TurnRestrictGraphicsScene::TurnRestrictGraphicsScene(QObject *parent)
	: CommonNodeGraphicsScene(parent)
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
		tmpNodeItem->setNodeData(tmpNodeData).setHaveBorder(mHaveBorderList.at(index))
			.setRadius(mSizeList.at(index)).setInnerColor(mInnerColorList.at(index))
			.setBorderColor(mBorderColorList.at(index)).setNodeItemType(GraphicsNodeItem::Restriction);
		addItem(tmpNodeItem);
		connect(tmpNodeItem, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(tmpNodeItem, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus() ) );
		mNodeItemList << tmpNodeItem;
	}
	QListIterator<Edge*> edgeDataIte(mEdgeDataList);
	Edge * tmpEdgeData;
	mEdgeNetItem = new GraphicsEdgeNetItem;
	mEdgeNetItem->setHaveBorder(mHaveBorderList.last()).setInnerColor(mInnerColorList.last())
		.setBorderColor(mBorderColorList.last()).setWidth(mSizeList.last());
	while (edgeDataIte.hasNext())
	{
		tmpEdgeData = edgeDataIte.next();
		mEdgeNetItem->addEdgeData(tmpEdgeData);
	}
	addItem(mEdgeNetItem);

}

void TurnRestrictGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(mLabelTextList.at(0), LegendElement::THICK_DOT, mSizeList.at(0),
		mInnerColorList.at(0), mBorderColorList.at(0));
	elements << LegendElement(mLabelTextList.at(1), LegendElement::THICK_DOT, mSizeList.at(1),
		mInnerColorList.at(1), mBorderColorList.at(1));
	elements << LegendElement(mLabelTextList.at(2), LegendElement::THICK_LINE, mSizeList.at(2),
		mInnerColorList.at(2), mBorderColorList.at(2));
	mLegend = new Legend(elements);
	LegendProxy * mLegendProxy = new LegendProxy;
	mLegendProxy->setWidget(mLegend);
	addItem(mLegendProxy);

}

void TurnRestrictGraphicsScene::init()
{
	mBorderColorList << QColor() << QColor() << QColor(203,168,87);
	mInnerColorList << QColor(0,255,0) << QColor(255,0,0) << QColor(253,206,102);
	mSizeList << 4 << 4 << 4;
	mHaveBorderList << true << true << true;
	mLabelTextList << QStringLiteral("无转向限制交叉") << QStringLiteral("转向限制交叉") <<
		QStringLiteral("路段");

}

void TurnRestrictGraphicsScene::updateItemsAttr()
{
	QListIterator<GraphicsNodeItem*> nodeItemIte(mNodeItemList);
	GraphicsNodeItem * tmpNodeItem;
	Node* tmpNodeData;
	int index;
	while (nodeItemIte.hasNext())
	{
		tmpNodeItem = nodeItemIte.next();
		tmpNodeData = tmpNodeItem->nodeData();
		index = tmpNodeData->haveTurnRestrict() ? 1 : 0;
		tmpNodeItem->updateAttr(mInnerColorList.at(index), mBorderColorList.at(index),
			mSizeList.at(index), mHaveBorderList.at(index));
	}
	mEdgeNetItem->updateAttr(mInnerColorList.last(), mBorderColorList.last(),
		mSizeList.last(), mHaveBorderList.last());
	mLegend->updateAttr(mInnerColorList, mBorderColorList, mSizeList);
}


