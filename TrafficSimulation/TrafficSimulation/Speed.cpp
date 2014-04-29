#include "Speed.h"


Speed::Speed(void)
{
}


Speed::~Speed(void)
{
}

Speed& Speed::setId(int id)
{
	mId = id;
	return *this;
}

Speed& Speed::setSpeed(qreal speed)
{
	mSpeed = speed;
	return *this;
}

int Speed::id() const
{
	return mId;
}

qreal Speed::speed() const
{
	return mSpeed;
}
