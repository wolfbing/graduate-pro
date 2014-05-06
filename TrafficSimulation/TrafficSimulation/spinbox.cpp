#include "spinbox.h"

SpinBox::SpinBox(QWidget *parent)
	: QDoubleSpinBox(parent)
{
	connect(this, SIGNAL(valueChanged(double)), this, SLOT(changeValue(qreal)));
}

SpinBox::~SpinBox()
{

}

SpinBox& SpinBox::setId(int id)
{
	mId = id;
	return *this;
}

void SpinBox::changeValue(qreal value)
{
	emit valueChange(value, mId);
}
