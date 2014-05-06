#ifndef COLOREDIT_H
#define COLOREDIT_H

#include <QDialog>
#include <QFrame>

class ColorEdit : public QDialog
{
	Q_OBJECT

public:
	ColorEdit(QColor, int, QWidget *parent=0);
	~ColorEdit();

	void setColor(QColor);

signals:
	void colorChanged(QColor, int);

protected:
	void mousePressEvent(QMouseEvent *);

private:
	QColor mColor;
	int mId;
	QFrame* mButton;
	
};

#endif // COLOREDIT_H
