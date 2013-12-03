#include "graphicalWidget.h"
#include <qlayout.h>
#include <QString>

GraphicalWidget::GraphicalWidget(const int &countOfSensors)
{
	mPlotWidget = new PlotWidget;
	mCurrentSensor = new QComboBox();
	for (int i = 0; i < countOfSensors; i++)
	{
		mCurrentSensor->addItem("Sensor " + QString::number(i));
	}
	connect(mCurrentSensor, SIGNAL(currentIndexChanged(const int &)),
					 this, SLOT(changedNumberOfSensor(const int &)));

	filteredDataStatus = new QCheckBox("Filtered Data");
	connect(filteredDataStatus, SIGNAL(clicked(bool)), this, SLOT(changedFilteredStatus(bool)));

	QVBoxLayout *vLayout = new QVBoxLayout();
	vLayout->addWidget(mCurrentSensor);
	vLayout->addWidget(filteredDataStatus);

	QHBoxLayout *hLayout = new QHBoxLayout(this);
	hLayout->addWidget(mPlotWidget);
	hLayout->addLayout(vLayout);

}

void GraphicalWidget::updateOriginalPoint(const int &newPoint)
{
	mPlotWidget->addOriginalPoint(newPoint);
}

void GraphicalWidget::updateFilteredPoint(const int &newPoint)
{
	mPlotWidget->addFilteredPoint(newPoint);
}

void GraphicalWidget::updateFilteredVisible(bool isVisible)
{
	mPlotWidget->setFilteredVisible(isVisible);
}

void GraphicalWidget::changedNumberOfSensor(const int &newSensor)
{
	mPlotWidget->clear();

	emit changedCurrentSensor(newSensor);
}

void GraphicalWidget::changedFilteredStatus(bool newStatus)
{
	mPlotWidget->setFilteredVisible(newStatus);
}
