#include "deviseWidget.h"
#include "ui_deviseWidget.h"

DeviseWidget::DeviseWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DeviseWidget)
{
	ui->setupUi(this);
}

DeviseWidget::~DeviseWidget()
{
	delete ui;
}
