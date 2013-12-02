#ifndef CALIBRATORWIDGET_H
#define CALIBRATORWIDGET_H

#include <QWidget>

#include <QList>

namespace Ui {
class CalibratorWidget;
}

class CalibratorWidget : public QWidget
{
	Q_OBJECT

public:
	explicit CalibratorWidget(int const& numOfCalibrated, QWidget *parent = 0);
	~CalibratorWidget();

	void setData(QList<int> const& mins, QList<int> const& maxs, QList<int> const& values);

signals:
	void startCalibrate();
	void stopCalibrate();

private:
	Ui::CalibratorWidget *ui;
};

#endif // CALIBRATORWIDGET_H
