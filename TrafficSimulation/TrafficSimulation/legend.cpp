#include "legend.h"
#include "linewidget.h"
#include "dotwidget.h"
#include "thicklinewidget.h"
#include "thickdotwidget.h"

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSizePolicy>
#include <QtWidgets\qgridlayout.h>
#include <QMoveEvent>
#include <QPalette>


Legend::Legend(QList<LegendElement> elements, QWidget *parent) :
    QDialog(parent),mElements(elements)
	, mFirstShow(true)
{
    this->setWindowTitle(tr("legend"));
    this->setWindowOpacity(0.75);

    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::MinimumExpanding);
	this->setMinimumWidth(200);
	this->setMinimumHeight(100);
	draw();
}

Legend *Legend::setElements(QList<LegendElement> elelist)
{
    mElements = elelist;
    return this;
}

void Legend::draw(){
	QGridLayout* layout = new QGridLayout;
	this->setLayout(layout);
	for(int i=0; i<mElements.size(); ++i){
		LegendElement element = mElements.at(i);
		int rowNum = layout->rowCount();
		if(element.type() == LegendElement::DOT ){
			QLabel* label = new QLabel(element.name());
			DotWidget* dotWidget = new DotWidget;
			dotWidget->setColor(element.color1());
			dotWidget->setRadius(element.size());
			layout->addWidget(label, rowNum, 1);
			layout->addWidget(dotWidget, rowNum, 2);
			
		}
		if(element.type() == LegendElement::LINE){
			QLabel* label = new QLabel(element.name());
			LineWidget* lineWidget = new LineWidget;
			lineWidget->setColor(element.color1());
			lineWidget->setWidth(element.size());
			layout->addWidget(label, rowNum, 1);
			layout->addWidget(lineWidget,rowNum,2);
		}
		if (element.type() == LegendElement::THICK_LINE)
		{
			QLabel* label = new QLabel(element.name());
			ThickLineWidget* tLineWidget = new ThickLineWidget(
				element.size(), element.color1(),element.color2());
			layout->addWidget(label,rowNum, 1);
			layout->addWidget(tLineWidget, rowNum,2);
		}
		if (element.type() == LegendElement::THICK_DOT)
		{
			QLabel* label = new QLabel(element.name());
			ThickDotWidget* tDotWidget = new ThickDotWidget(
				element.size(), element.color1(),element.color2());
			layout->addWidget(label,rowNum,1);
			layout->addWidget(tDotWidget,rowNum,2);
		}
	}
	
}



void Legend::moveEvent( QMoveEvent * event)
{
	updatePos();
}

void Legend::updatePos()
{
	QPoint p = this->pos();
	QRect r = this->geometry();
	QRect fr = this->frameGeometry();
	QPoint brp = fr.bottomRight();
	QWidget* par = (QWidget*) parent();
	QWidget* mainWin = (QWidget*)par->parent();
	QPoint mainWinPos = mainWin->geometry().topLeft();
	QPoint parRelPos = par->pos();
	QPoint limitTopLeftPos = mainWinPos + parRelPos;
	QPoint limitBottomRightPos = mainWinPos + par->geometry().bottomRight();
	QPoint finalPos;
	QPoint frame = this->geometry().topLeft() - this->frameGeometry().topLeft();
	QPoint brframe = this->frameGeometry().bottomRight() - this->geometry().bottomRight();
	if (p.x() < limitTopLeftPos.x())
		finalPos.setX(limitTopLeftPos.x()+frame.x());
	else if(brp.x()>limitBottomRightPos.x())
		finalPos.setX(limitBottomRightPos.x()-brframe.x()-r.width());
	else
		finalPos.setX(r.x());
	if (p.y()<limitTopLeftPos.y())
		finalPos.setY(limitTopLeftPos.y()+frame.y());
	else if(brp.y()>limitBottomRightPos.y())
		finalPos.setY(limitBottomRightPos.y()-brframe.y()-r.height());
	else
		finalPos.setY(r.y());

	setGeometry(finalPos.x(),finalPos.y(),r.width(),r.height());
}

void Legend::initPos()
{
	QWidget* par = (QWidget*) parent();
	QWidget* mainWin = (QWidget*)par->parent();
	QPoint mainWinPos = mainWin->geometry().topLeft();
	QPoint limitBottomRightPos = mainWinPos + par->geometry().bottomRight();
	QRect r = this->geometry();
	QRect fr = this->frameGeometry();
	QPoint frame = this->geometry().topLeft() - this->frameGeometry().topLeft();
	QPoint finalPos;
	finalPos.setX(limitBottomRightPos.x()-fr.width()+frame.x()-50);
	finalPos.setY(limitBottomRightPos.y()-fr.height()+frame.y()-100);
	setGeometry(finalPos.x(),finalPos.y(),r.width(),r.height());

}

void Legend::paintEvent( QPaintEvent * event )
{
	QDialog::paintEvent(event);
	if (mFirstShow)
	{
		initPos();
		mFirstShow = false;
	}
}


