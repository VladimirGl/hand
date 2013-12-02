#include "calibratorScene.h"

#include "calibrateRectItem.h"
#include "guiConsts.h"

#include <QDebug>

CalibratorScene::CalibratorScene(const int &numOfCalibrated, QObject *parent) :
	QGraphicsScene(parent)
{
	this->setSceneRect(0, 0, CalibrateRect::rectW * numOfCalibrated, CalibrateRect::rectH);

	for (int i = 0; i < numOfCalibrated; i++) {
		mList.append(new CalibrateRectItem);

		this->addItem(mList.last());

		mList.last()->setPos(i * CalibrateRect::rectW, 0);
	}
}

void CalibratorScene::setData(const QList<int> &mins, const QList<int> &maxs, const QList<int> &values)
{
	qDebug() << values;

	if (mins.size() != mList.size()) {
		qDebug() << "bad data try to load to calibrator widget";
		return;
	}

	for (int i = 0; i < mList.size(); i++) {
		mList.at(i)->setCalibrateingData(mins.at(i), maxs.at(i), values.at(i));
	}
}
