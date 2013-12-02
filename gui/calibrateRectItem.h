#ifndef CALIBRATERECTITEM_H
#define CALIBRATERECTITEM_H

#include <QGraphicsRectItem>

class CalibrateRectItem : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	CalibrateRectItem();

	void setCalibrateingData(const int& min, const int& max, const int& value);

signals:

public slots:

protected:
	void setBoard();

	void setLineBrush();
	void setRectBrush();

private:
	QGraphicsLineItem *mMinLine;
	QGraphicsLineItem *mMaxLine;

	QGraphicsRectItem *mCurrValueRect;
};

#endif // CALIBRATERECTITEM_H
