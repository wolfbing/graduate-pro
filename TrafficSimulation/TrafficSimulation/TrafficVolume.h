#pragma once

#include <QtCore>

class TrafficVolume
{
public:
	TrafficVolume(void);
	~TrafficVolume(void);

	//set
	TrafficVolume& setId(int id);
	TrafficVolume& setMotorVolume(qreal);
	TrafficVolume& setNonMotorVolume(qreal);
	TrafficVolume& setMotorbikeVolume(qreal);
	TrafficVolume& setCarVolume(qreal);
	TrafficVolume& setBusVolume(qreal);
	TrafficVolume& setTaxiVolume(qreal);
	TrafficVolume& setTruckVolume(qreal);

	// get
	int id() const;
	qreal motorVolume() const;
	qreal nonMotorVolume() const;
	qreal motorbikeVolume() const;
	qreal carVolume() const;
	qreal busVolume() const;
	qreal taxiVolume() const;
	qreal truckVolume() const;



private:
	int mId;
	qreal mMotorVolume;
	qreal mNonMotorVolume;
	qreal mMotorbikeVolume;
	qreal mCarVolume;
	qreal mBusVolume;
	qreal mTaxiVolume;
	qreal mTruckVolume;


};

