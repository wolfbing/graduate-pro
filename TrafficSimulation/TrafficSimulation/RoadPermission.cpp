#include "RoadPermission.h"


RoadPermission::RoadPermission(void)
{
}


RoadPermission::~RoadPermission(void)
{
}

RoadPermission& RoadPermission::setRoadId(int id)
{
	mRoadId = id;
	return *this;
}

RoadPermission& RoadPermission::setPermitBike(int forbid)
{
	mPermitBike = forbid;
	return *this;
}

RoadPermission& RoadPermission::setPermitCar(int forbid)
{
	mPermitCar = forbid;
	return *this;
}

RoadPermission& RoadPermission::setPermitMotor(int forbid)
{
	mPermitMotor = forbid;
	return *this;
}

RoadPermission& RoadPermission::setPermitTaxi(int forbid)
{
	mPermitTaxi = forbid;
	return *this;
}

RoadPermission& RoadPermission::setPermitTruck(int forbid)
{
	mPermitTruck = forbid;
	return *this;
}

RoadPermission& RoadPermission::setPermitBus(int forbid)
{
	mPermitBus = forbid;
	return *this;
}

int RoadPermission::roadId() const
{
	return mRoadId;
}

int RoadPermission::permitBike() const
{
	return mPermitBike;
}

int RoadPermission::permitCar() const
{
	return mPermitCar;
}

int RoadPermission::permitMotor() const
{
	return mPermitMotor;
}

int RoadPermission::permitTaxi() const
{
	return mPermitTaxi;
}

int RoadPermission::permitTruck() const
{
	return mPermitTruck;
}

int RoadPermission::permitBus() const
{
	return mPermitBus;
}
