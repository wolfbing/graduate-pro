#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QCheckBox>

class CheckBox : public QCheckBox
{
	Q_OBJECT

public:
	CheckBox(QWidget *parent=0);
	~CheckBox();

	CheckBox& setId(int);

signals:
	void stateChange(int ,int);

public slots:
	void changeState(int);

private:
	int mId;
};

#endif // CHECKBOX_H
