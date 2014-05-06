#include "roadgraphicsscene.h"

#include "graphicssidelineitem.h"
#include "roadgraphicsconfigdialog.h"
#include "graphicsview.h"

RoadGraphicsScene::RoadGraphicsScene(QObject *parent)
	: GraphicsScene(parent)
	, mConfigDialog(0)
{

}

RoadGraphicsScene::~RoadGraphicsScene()
{

}

void RoadGraphicsScene::updateItems()
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

void RoadGraphicsScene::config()
{
	mConfigDialog = new RoadGraphicsConfigDialog;
	mConfigDialog->setColorList(mColorList);
	mConfigDialog->setWidthList(mWidthList);
	mConfigDialog->setLabelTextList(mLabelTextList);
	mConfigDialog->draw();
		
	if (mConfigDialog->exec()==QDialog::Accepted)
	{
		mColorList = mConfigDialog->colorList();
		mWidthList = mConfigDialog->widthList();
		updateItemsAttr();
	}
	delete mConfigDialog;
	mConfigDialog=0;

}
