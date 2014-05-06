#include "coloredit.h"

#include <QPalette>
#include <QMouseEvent>
#include <QColorDialog>
#include <QHBoxLayout>

ColorEdit::ColorEdit(QColor color, int id, QWidget *parent)
	: QDialog(parent)
	, mColor(color)
	, mId(id)
{
	this->setModal(true);
	QHBoxLayout *layout = new QHBoxLayout;
	setLayout(layout);
	layout->setContentsMargins(0, 0, 0, 0);
	mButton = new QFrame(this);
	QPalette palette = mButton->palette();
	palette.setColor(QPalette::Window, QColor(mColor));
	mButton->setPalette(palette);
	mButton->setAutoFillBackground(true);
	mButton->setMinimumSize(32, 0);
	mButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
	mButton->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	layout->addWidget(mButton);
}

ColorEdit::~ColorEdit()
{

}

void ColorEdit::mousePressEvent(QMouseEvent * evt)
{
	if (evt->button() == Qt::LeftButton)
	{
		QColor color(mColor);
		QColorDialog dialog(color, 0);
		if(dialog.exec()==QDialog::Rejected)
			return;
		QColor newColor = dialog.selectedColor();
		if(newColor==mColor)
			return;
		else{
			setColor(newColor);
			emit colorChanged(newColor, mId);
		}
			

	}
}

void ColorEdit::setColor(QColor color)
{
	mColor = color;
	QPalette palette = mButton->palette();
	palette.setColor(QPalette::Window, color);
	mButton->setPalette(palette);
}


