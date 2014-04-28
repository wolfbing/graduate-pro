#include "TrafficVolume.h"


TrafficVolume::TrafficVolume(void)
{
}


TrafficVolume::~TrafficVolume(void)
{
}

TrafficVolume& TrafficVolume::setId(int id)
{
	mId = id;
	return *this;
}

TrafficVolume& TrafficVolume::setMotorVolume(qreal volume)
{
	mMotorVolume = volume;
	return *this;
}

TrafficVolume& TrafficVolume::setNonMotorVolume(qreal volume)
{
	mNonMotorVolume = volume;
	return *this;
}

TrafficVolume& TrafficVolume::setMotorbikeVolume(qreal volume)
{
	mMotorbikeVolume = volume;
	return *this;
}

TrafficVolume& TrafficVolume::setCarVolume(qreal volume)
{
	mCarVolume = volume;
	return *this;
}

TrafficVolume& TrafficVolume::setBusVolume(qreal volume)
{
	mBusVolume = volume;
	return *this;
}

TrafficVolume& TrafficVolume::setTaxiVolume(qreal volume)
{
	mTaxiVolume = volume;
	return *this;
}

TrafficVolume& TrafficVolume::setTruckVolume(qreal volume)
{
	mTruckVolume = volume;
	return *this;
}

int TrafficVolume::id() const
{
	return mId;
}

qreal TrafficVolume::motorVolume() const
{
	return mMotorVolume;
}

qreal TrafficVolume::nonMotorVolume() const
{
	return mNonMotorVolume;
}

qreal TrafficVolume::motorbikeVolume() const
{
	return mMotorbikeVolume;
}

qreal TrafficVolume::carVolume() const
{
	return mCarVolume;
}

qreal TrafficVolume::busVolume() const
{
	return mBusVolume;
}

qreal TrafficVolume::taxiVolume() const
{
	return mTaxiVolume;
}

qreal TrafficVolume::truckVolume() const
{
	return mTruckVolume;
}
