#ifndef SPINBOX_H
#define SPINBOX_H

#include <QDoubleSpinBox>

class SpinBox : public QDoubleSpinBox
{
	Q_OBJECT

public:
	SpinBox(QWidget *parent=0);
	~SpinBox();

	SpinBox& setId(int); 

signals:
	void valueChange(qreal, int);

public slots:
	void changeValue(qreal);
	

private:
	int mId;
	
};

#endif // SPINBOX_H
