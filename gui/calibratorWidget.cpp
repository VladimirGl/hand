#include "calibratorWidget.h"
#include "ui_calibratorWidget.h"

#include "calibratorScene.h"

CalibratorWidget::CalibratorWidget(const int& numOfCalibrated, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CalibratorWidget)
{
	ui->setupUi(this);

	ui->graphicsView->setScene(new CalibratorScene(numOfCalibrated));

	connect(ui->startCalibrateButton, SIGNAL(clicked()), this, SIGNAL(startCalibrate()));
	connect(ui->stopCalibrateButton, SIGNAL(clicked()), this, SIGNAL(stopCalibrate()));
}

CalibratorWidget::~CalibratorWidget()
{
	delete ui;
}

void CalibratorWidget::setData(const QList<int> &mins, const QList<int> &maxs, const QList<int> &values)
{
	static_cast<CalibratorScene *> (ui->graphicsView->scene())->setData(mins, maxs, values);
}
