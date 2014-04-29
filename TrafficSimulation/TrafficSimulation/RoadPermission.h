#pragma once
class RoadPermission
{
public:
	RoadPermission(void);
	~RoadPermission(void);

	// set
	RoadPermission& setRoadId(int);
	RoadPermission& setPermitBike(int);
	RoadPermission& setPermitCar(int);
	RoadPermission& setPermitMotor(int);
	RoadPermission& setPermitTaxi(int);
	RoadPermission& setPermitTruck(int);
	RoadPermission& setPermitBus(int);

	// get
	int roadId() const;
	int permitBike() const;
	int permitCar() const;
	int permitMotor() const;
	int permitTaxi() const;
	int permitTruck() const;
	int permitBus() const;


private:
	int mRoadId;
	int mPermitBike;
	int mPermitCar;
	int mPermitMotor;
	int mPermitTaxi;
	int mPermitTruck;
	int mPermitBus;

};

