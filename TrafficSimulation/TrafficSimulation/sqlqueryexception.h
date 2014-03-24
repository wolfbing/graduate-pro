#ifndef SQLQUERYEXCEPTION_H
#define SQLQUERYEXCEPTION_H

#include <QException>
#include <QString>

class SqlQueryException : public QException
{
public:
    SqlQueryException();
    SqlQueryException(QString err);
    ~SqlQueryException() throw();

    //重载
    void raise() const;
    SqlQueryException* clone() const;

    QString text();

private:
    QString mErr;
};

#endif // SQLQUERYEXCEPTION_H
