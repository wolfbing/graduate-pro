#pragma once
#include <QObject>

class Communicate:public QObject
{
	Q_OBJECT

public:
	Communicate(void);
	~Communicate(void);

signals:
	void sendTmpInfoToStatus(QString);
	void clearTmpInfoFromStatus();


};

