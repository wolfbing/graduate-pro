#ifndef THICKLINEWIDGET_H
#define THICKLINEWIDGET_H

#include <QWidget>

class ThickLineWidget : public QWidget
{
	Q_OBJECT

public:
	ThickLineWidget(QWidget *parent = 0);
	ThickLineWidget(double width, QColor color, QColor outColor, QWidget* parent=0);
	~ThickLineWidget();

protected:
	void paintEvent(QPaintEvent * event);

private:
	QColor mColor;
	QColor mOutColor;
	double mWidth; // Íâ²àÏß¿í, ÄÚ²à-2

};

#endif // THICKLINEWIDGET_H
