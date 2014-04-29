#include "BusRoute.h"


BusRoute::BusRoute(void)
{
}

BusRoute::BusRoute( const BusRoute & route )
{
	mId = route.mId;
	mRouteId = route.mRouteId;
	mStopNum = route.mStopNum;
	mStops = route.mStops;
	mVehicle = route.mVehicle;
	mCarEquivalent = route.mCarEquivalent;
}


BusRoute::~BusRoute(void)
{
}

BusRoute& BusRoute::setId( int id)
{
	mId = id;
	return *this;
}

BusRoute& BusRoute::setRouteId( int id )
{
	mRouteId = id;
	return *this;
}

BusRoute& BusRoute::setStopNum( int num )
{
	mStopNum = num;
	return *this;
}

BusRoute& BusRoute::setStops( QList<int> list )
{
	mStops = list;
	return *this;
}

BusRoute& BusRoute::setVehicle( int vehicle )
{
	mVehicle = vehicle;
	return *this;
}

BusRoute& BusRoute::setCarEquivalent( qreal equ)
{
	mCarEquivalent = equ;
	return *this;
}

int BusRoute::id() const
{
	return mId;
}

int BusRoute::routeId() const
{
	return mRouteId;
}

int BusRoute::stopNum() const
{
	return mStopNum;
}

QList<int> BusRoute::stops() const
{
	return mStops;
}

int BusRoute::vehicle() const
{
	return mVehicle;
}

qreal BusRoute::carEquivalent() const
{
	return mCarEquivalent;
}

BusRoute& BusRoute::operator=( const BusRoute & route )
{
	mId = route.mId;
	mRouteId = route.mRouteId;
	mStopNum = route.mStopNum;
	mStops = route.mStops;
	mVehicle = route.mVehicle;
	mCarEquivalent = route.mCarEquivalent;
	return *this;
}

bool BusRoute::operator==( const BusRoute & route ) const
{
	return 
	(mId == route.mId)
	&&(mRouteId == route.mRouteId)
	&&(mStopNum == route.mStopNum)
	&&(mStops == route.mStops)
	&&(mVehicle == route.mVehicle)
	&&(mCarEquivalent == route.mCarEquivalent);
}
