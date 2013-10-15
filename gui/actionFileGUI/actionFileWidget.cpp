#include "actionFileWidget.h"
#include "ui_actionfilewidget.h"

ActionFileWidget::ActionFileWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ActionFileWidget)
{
	ui->setupUi(this);
}

ActionFileWidget::~ActionFileWidget()
{
	delete ui;
}
