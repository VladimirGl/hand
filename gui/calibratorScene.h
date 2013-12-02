#ifndef CALIBRATORSCENE_H
#define CALIBRATORSCENE_H

#include <QGraphicsScene>

class CalibrateRectItem;

class CalibratorScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit CalibratorScene(const int& numOfCalibrated, QObject *parent = 0);

	void setData(QList<int> const& mins, QList<int> const& maxs, QList<int> const& values);

private:
	QList<CalibrateRectItem *> mList;
};

#endif // CALIBRATORSCENE_H
