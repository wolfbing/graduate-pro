#include "junctiontypegraphicsscene.h"

#include "graphicsedgenetitem.h"
#include "graphicsnodeitem.h"
#include "legendelement.h"
#include "legend.h"
#include "legendproxy.h"

JunctionTypeGraphicsScene::JunctionTypeGraphicsScene(QObject *parent)
	: CommonNodeGraphicsScene(parent)
{
	init();
	addLegend();
}

JunctionTypeGraphicsScene::~JunctionTypeGraphicsScene()
{

}

void JunctionTypeGraphicsScene::addItems()
{
	{
		mEdgeNetItem = new GraphicsEdgeNetItem;
		QListIterator<Edge*> edgeDataIte(mEdgeDataList);
		while (edgeDataIte.hasNext())
		{
			mEdgeNetItem->addEdgeData(edgeDataIte.next());
		}  //// 添加路网
		mEdgeNetItem->setHaveBorder(mHaveBorderList.last()).setInnerColor(mInnerColorList.last())
			.setBorderColor(mBorderColorList.last()).setWidth(mSizeList.last());
		addItem(mEdgeNetItem);
	}
	{
		QListIterator<Node*> nodeDataIte(mNodeDataList);
		Node * tmpNodeData;
		GraphicsNodeItem * tmpNodeItem;
		int index;
		while (nodeDataIte.hasNext())
		{
			tmpNodeData = nodeDataIte.next();
			index = tmpNodeData->junctionType()-1;
			tmpNodeItem = new GraphicsNodeItem;
			tmpNodeItem->setNodeData(tmpNodeData).setRadius(mSizeList.at(index))
				.setInnerColor(mInnerColorList.at(index)).setBorderColor(mBorderColorList.at(index))
				.setHaveBorder(mHaveBorderList.at(index)).setNodeItemType(GraphicsNodeItem::Junction);
			addItem(tmpNodeItem);
			mNodeItemList << tmpNodeItem;
			connect(tmpNodeItem, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
			connect(tmpNodeItem, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus() ) );
		}
	}

}

void JunctionTypeGraphicsScene::init()
{
	mHaveBorderList << true << true << true << true << true << true << true ;
	mInnerColorList << QColor(255,0,0) << QColor(0,255,0) << QColor(0,0,255)
		<< QColor(0,255,255) <<QColor(255,0,255) << QColor(255,255,0) << QColor(253,206,102);
	mBorderColorList << QColor() << QColor() << QColor() << QColor() << QColor() <<QColor() << QColor(203,168,87);
	mSizeList << 4 << 4 << 4 << 4 << 4 << 4 << 4;
	mLabelTextList << QStringLiteral("信号交叉口") << QStringLiteral("无控制交叉口") << QStringLiteral("环形交叉口")
		<< QStringLiteral("立体交叉口") << QStringLiteral("进口拓宽交叉口") <<QStringLiteral("主路优先权交叉口")
		<< QStringLiteral("路段");
}


void JunctionTypeGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(mLabelTextList.at(0),LegendElement::THICK_DOT,mSizeList.at(0) 
		,mInnerColorList.at(0), mBorderColorList.at(0));
	elements << LegendElement(mLabelTextList.at(1),LegendElement::THICK_DOT,mSizeList.at(1) 
		,mInnerColorList.at(1), mBorderColorList.at(1));
	elements << LegendElement(mLabelTextList.at(2),LegendElement::THICK_DOT,mSizeList.at(2) 
		,mInnerColorList.at(2), mBorderColorList.at(2));
	elements << LegendElement(mLabelTextList.at(3),LegendElement::THICK_DOT,mSizeList.at(3) 
		,mInnerColorList.at(3), mBorderColorList.at(3));
	elements << LegendElement(mLabelTextList.at(4),LegendElement::THICK_DOT,mSizeList.at(4) 
		,mInnerColorList.at(4), mBorderColorList.at(4));
	elements << LegendElement(mLabelTextList.at(5),LegendElement::THICK_DOT,mSizeList.at(5) 
		,mInnerColorList.at(5), mBorderColorList.at(5));
	elements << LegendElement(mLabelTextList.at(6), LegendElement::THICK_LINE, mSizeList.at(6),
		mInnerColorList.at(6), mBorderColorList.at(6));
	mLegend = new Legend(elements);
	mLegendProxy = new LegendProxy;
	mLegendProxy->setWidget(mLegend);
	addItem(mLegendProxy);

}

void JunctionTypeGraphicsScene::updateItemsAttr()
{
	QListIterator<GraphicsNodeItem*> nodeItemIte(mNodeItemList);
	Node * tmpNodeData;
	GraphicsNodeItem * tmpNodeItem;
	int index;
	while (nodeItemIte.hasNext())
	{
		tmpNodeItem = nodeItemIte.next();
		tmpNodeData = tmpNodeItem->nodeData();
		index = tmpNodeData->junctionType()-1;
		tmpNodeItem->updateAttr(mInnerColorList.at(index), mBorderColorList.at(index), 
			mSizeList.at(index), mHaveBorderList.at(index));

	}
	mEdgeNetItem->updateAttr(mInnerColorList.last(), mBorderColorList.last(),
		mSizeList.last(), mHaveBorderList.last());
	mLegend->updateAttr(mInnerColorList, mBorderColorList, mSizeList);

}

