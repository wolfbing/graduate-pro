#include "legendelement.h"

LegendElement::LegendElement(QObject *parent) :
    QObject(parent)
{
}

LegendElement::LegendElement(QString name, int type, float size, QColor color1, QColor color2) :
    QObject(0)
{
	setElementName(name);
	setElementType(type);
	setElementSize(size);
	setElementColor1(color1);
	setElementColor2(color2);
}

LegendElement::LegendElement(const LegendElement & element){
	mName = element.mName;
	mType = element.mType;
	mSize = element.mSize;
	mColor1 = element.mColor1;
	mColor2 = element.mColor2;
}

void LegendElement::operator=(const LegendElement & element){
	mName = element.mName;
	mType = element.mType;
	mSize = element.mSize;
	mColor1 = element.mColor1;
	mColor2 = element.mColor2;
}

LegendElement *LegendElement::setElementName(QString name)
{
    mName = name;
    return this;
}

LegendElement *LegendElement::setElementType(int type)
{
    mType = type;
    return this;
}

LegendElement *LegendElement::setElementSize(float size)
{
    mSize = size;
    return this;
}

LegendElement* LegendElement::setElementColor1(QColor color){
	mColor1 = color;
	return this;
}

QString LegendElement::name(){
	return mName;
}

int LegendElement::type(){
	return mType;
}

float LegendElement::size(){
	return mSize;
}

QColor LegendElement::color1(){
	return mColor1;
}

QColor LegendElement::color2()
{
	return mColor2;
}

LegendElement* LegendElement::setElementColor2( QColor color )
{
	mColor2 = color;
	return this;
}


