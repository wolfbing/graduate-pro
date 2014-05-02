#ifndef THICKDOTWIDGET_H
#define THICKDOTWIDGET_H

#include <QWidget>

class ThickDotWidget : public QWidget
{
	Q_OBJECT

public:
	ThickDotWidget(QWidget *parent = 0);
	
	ThickDotWidget(qreal radius, QColor inColor, QColor outColor, bool haveBorder=true, QWidget* parent=0);
	~ThickDotWidget();

public slots:
	void changeSize(qreal);
	void changeInnerColor(QColor color);
	void changeBorderColor(QColor color);
	void changeHaveBorder(int);

protected:
	void paintEvent(QPaintEvent *);
	QSize sizeHint() const;

private:
	QColor mInColor;
	QColor mOutColor;
	qreal mSize; // ÍâÈ¦°ë¾¶, ÄÚÈ¦°ë¾¶Ð¡1
	bool mHaveBorder;
};

#endif // THICKDOTWIDGET_H
