#ifndef CALIBRATORWIDGET_H
#define CALIBRATORWIDGET_H

#include <QWidget>

namespace Ui {
class CalibratorWidget;
}

class CalibratorWidget : public QWidget
{
	Q_OBJECT

public:
	explicit CalibratorWidget(QWidget *parent = 0);
	~CalibratorWidget();

signals:
	void startCalibrate();
	void stopCalibrate();

private:
	Ui::CalibratorWidget *ui;
};

#endif // CALIBRATORWIDGET_H
