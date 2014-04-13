#pragma once

#include <QList>

class BusRoute
{
public:
	BusRoute(void);
	~BusRoute(void);

	BusRoute(const BusRoute & );
	BusRoute& operator=(const BusRoute &);
	bool operator==(const BusRoute &) const;

	/// set
	BusRoute& setId(int);
	BusRoute& setRouteId(int);
	BusRoute& setStopNum(int);
	BusRoute& setStops(QList<int>);
	BusRoute& setVehicle(int);
	BusRoute& setCarEquivalent(qreal);

	//// get
	int id() const;
	int routeId() const;
	int stopNum() const;
	QList<int> stops() const;
	int vehicle() const;
	qreal carEquivalent() const;


private:
	int mId;
	int mRouteId;
	int mStopNum;
	QList<int> mStops;
	int mVehicle; 
	qreal mCarEquivalent;


};

