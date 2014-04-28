#ifndef COMMONEXCEPTION_H
#define COMMONEXCEPTION_H

#include <QException>
#include <QString>

class CommonException : public QException
{

public:
	CommonException(QString info);
	~CommonException();

	void raise() const {throw *this;}
	CommonException* clone() const{return new CommonException(*this);};

	QString info() const;

private:
	QString mErrInfo;
};

#endif // COMMONEXCEPTION_H
