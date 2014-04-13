#include "junctiontypegraphicsscene.h"

#include "graphicsedgenetitem.h"
#include "graphicsnodeitem.h"
#include "legendelement.h"
#include "legend.h"
#include "legendproxy.h"

JunctionTypeGraphicsScene::JunctionTypeGraphicsScene(QObject *parent)
	: GraphicsScene(parent)
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
			tmpNodeItem->setNodeData(tmpNodeData).setRadius(mNodeRadiusList.at(index))
				.setInnerColor(mNodeInnerColorList.at(index)).setBorderColor(mNodeBorderColorList.at(index))
				.setHaveBorder(mNodeHaveBorderList.at(index)).setNodeItemType(GraphicsNodeItem::Junction);
			addItem(tmpNodeItem);
			mNodeItemList << tmpNodeItem;
			connect(tmpNodeItem, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
			connect(tmpNodeItem, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus() ) );
		}
	}

}

void JunctionTypeGraphicsScene::init()
{
	mNodeHaveBorderList << true << true << true << true << true << true ;
	mNodeInnerColorList << QColor(255,0,0) << QColor(0,255,0) << QColor(0,0,255)
		<< QColor(0,255,255) <<QColor(255,0,255) << QColor(255,255,0);
	mNodeBorderColorList << QColor() << QColor() << QColor() << QColor() << QColor() <<QColor();
	mNodeRadiusList << 4 << 4 << 4 << 4 << 4 << 4;

	mEdgeNetBorderColor =  QColor(203,168,87);
	mEdgeNetHaveBorder = true;
	mEdgeNetWidth = 4.0;
	mEdgeNetInnerColor = QColor(253,206,102);
}

void JunctionTypeGraphicsScene::updateItems()
{
	GraphicsScene::updateItems();
	mEdgeNetItem->advance();
	GraphicsNodeItem * tmpNodeItem;
	QListIterator<GraphicsNodeItem*> nodeItemIte(mNodeItemList);
	while (nodeItemIte.hasNext())
	{
		tmpNodeItem = nodeItemIte.next();
		tmpNodeItem->setPos(tmpNodeItem->nodeData()->sceneCoor());
	}
}

void JunctionTypeGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(QStringLiteral("信号交叉口"),LegendElement::THICK_DOT,mNodeRadiusList.at(0) 
		,mNodeInnerColorList.at(0), mNodeBorderColorList.at(0));
	elements << LegendElement(QStringLiteral("无控制交叉口"),LegendElement::THICK_DOT,mNodeRadiusList.at(1) 
		,mNodeInnerColorList.at(1), mNodeBorderColorList.at(1));
	elements << LegendElement(QStringLiteral("环形交叉口"),LegendElement::THICK_DOT,mNodeRadiusList.at(2) 
		,mNodeInnerColorList.at(2), mNodeBorderColorList.at(2));
	elements << LegendElement(QStringLiteral("立体交叉口"),LegendElement::THICK_DOT,mNodeRadiusList.at(3) 
		,mNodeInnerColorList.at(3), mNodeBorderColorList.at(3));
	elements << LegendElement(QStringLiteral("进口拓宽交叉口"),LegendElement::THICK_DOT,mNodeRadiusList.at(4) 
		,mNodeInnerColorList.at(4), mNodeBorderColorList.at(4));
	elements << LegendElement(QStringLiteral("主路优先权交叉口"),LegendElement::THICK_DOT,mNodeRadiusList.at(5) 
		,mNodeInnerColorList.at(5), mNodeBorderColorList.at(5));
	elements << LegendElement(QStringLiteral("路段"), LegendElement::THICK_LINE, mEdgeNetWidth,
		mEdgeNetInnerColor, mEdgeNetBorderColor);
	Legend * legend = new Legend(elements);
	LegendProxy * proxy = new LegendProxy;
	proxy->setWidget(legend);
	addItem(proxy);

}

void JunctionTypeGraphicsScene::doSomething()
{

}
