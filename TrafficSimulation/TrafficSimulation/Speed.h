#pragma once

#include <QtCore>

class Speed
{
public:
	Speed(void);
	~Speed(void);

	////// set
	Speed& setId(int);
	Speed& setSpeed(qreal);

	///// get
	int id() const;
	qreal speed() const;


private:
	int mId;
	qreal mSpeed;

};

