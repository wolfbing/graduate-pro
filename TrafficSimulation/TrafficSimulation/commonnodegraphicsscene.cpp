#include "commonnodegraphicsscene.h"

#include "graphicsedgenetitem.h"
#include "graphicsnodeitem.h"
#include "commonnodegraphicsconfigdialog.h"

CommonNodeGraphicsScene::CommonNodeGraphicsScene(QObject *parent)
	: GraphicsScene(parent)
	, mLegendProxy(0)
{

}

CommonNodeGraphicsScene::~CommonNodeGraphicsScene()
{

}

void CommonNodeGraphicsScene::updateItems()
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

void CommonNodeGraphicsScene::config()
{
	CommonNodeGraphicsConfigDialog* dialog = new CommonNodeGraphicsConfigDialog;
	dialog->setInnerColorList(mInnerColorList);
	dialog->setBorderColorList(mBorderColorList);
	dialog->setLabelTextList(mLabelTextList);
	dialog->setSizeList(mSizeList);
	dialog->setHaveBorderList(mHaveBorderList);
	dialog->draw();
	if (dialog->exec()==QDialog::Accepted)
	{
		mInnerColorList = dialog->innerColorList();
		mBorderColorList = dialog->borderColorList();
		mSizeList = dialog->sizeList();
		mHaveBorderList = dialog->haveBorderList();
		updateItemsAttr();
	}
	delete dialog;
}
