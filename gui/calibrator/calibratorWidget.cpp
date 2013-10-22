#include "calibratorWidget.h"
#include "ui_calibratorwidget.h"

CalibratorWidget::CalibratorWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CalibratorWidget)
{
	ui->setupUi(this);

	connect(ui->startCalibrateButton, SIGNAL(clicked()), this, SIGNAL(startCalibrate()));
	connect(ui->stopCalibrateButton, SIGNAL(clicked()), this, SIGNAL(stopCalibrate()));
}

CalibratorWidget::~CalibratorWidget()
{
	delete ui;
}
