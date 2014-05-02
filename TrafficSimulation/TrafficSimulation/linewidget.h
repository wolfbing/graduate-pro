#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include <QWidget>
#include <QColor>

class LineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LineWidget(QWidget *parent = 0);
    LineWidget* setWidth(qreal width);
    LineWidget* setColor(QColor color);

signals:

public slots:
	void changeColor(QColor);
	void changeWidth(qreal);

protected:
    void paintEvent(QPaintEvent* event);

public:
    QSize sizeHint() const;

private:
    QColor mColor;
    qreal mWidth;



};

#endif // LINEWIDGET_H
