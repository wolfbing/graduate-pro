#include "checkbox.h"

CheckBox::CheckBox(QWidget *parent)
	: QCheckBox(parent)
{
	connect(this, SIGNAL(stateChanged(int)), this, SLOT(changeState(int)));
}

CheckBox::~CheckBox()
{

}

CheckBox& CheckBox::setId(int id)
{
	mId = id;
	return *this;
}

void CheckBox::changeState(int state)
{
	emit stateChange(state, mId);
}
