#include "plotWidget.h"

#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_canvas.h>
#include <qwt_scale_div.h>

#include <QDebug>

const int queueSize = 400;

PlotWidget::PlotWidget() :
	mOriginalCurve(new QwtPlotCurve),
	mFilteredCurve(new QwtPlotCurve)
{
	for (int i = 0; i < queueSize; i++) {
		mIterator.append(i);
	}

	this->enableAxis(QwtPlot::xBottom, false);
	this->setCanvasBackground(Qt::white);


	setAxisMaxMajor(QwtPlot::yLeft, queueSize / 8);
	setAxisMaxMajor(QwtPlot::xBottom, queueSize / 8);

	mGrid = new QwtPlotGrid;
	mGrid->setPen("#999999", 0.2);
	mGrid->attach(this);

	mOriginalCurve->attach(this);
	mOriginalCurve->setPen(Qt::blue, 2);
	mOriginalCurve->setRenderHint(QwtPlotItem::RenderAntialiased, true);

	mFilteredCurve->attach(this);
	mFilteredCurve->setVisible(false);
	mFilteredCurve->setPen("#33cc33", 2);
	mFilteredCurve->setRenderHint(QwtPlotItem::RenderAntialiased, true);;

}

PlotWidget::~PlotWidget()
{
	delete mOriginalCurve;
	delete mFilteredCurve;
	delete mGrid;
}

void PlotWidget::addOriginalPoint(const int &newPoint)
{
	if (mOriginalData.size() >= queueSize) {
		mOriginalData.dequeue();
	}

	mOriginalData.enqueue(newPoint);

	mOriginalCurve->setSamples(mIterator.toVector(), mOriginalData.toVector());
	this->replot();
}

void PlotWidget::addFilteredPoint(const int &newPoint)
{
	if (mFilteredData.size() >= queueSize) {
		mFilteredData.dequeue();
	}

	mFilteredData.enqueue(newPoint);

	if (mFilteredCurve->isVisible()) {
		mFilteredCurve->setSamples(mIterator.toVector(), mFilteredData.toVector());
		this->replot();
	}
}

void PlotWidget::setFilteredVisible(bool isVisible)
{
	mFilteredCurve->setVisible(isVisible);
}

void PlotWidget::updateOriginalPoint(const int &newPoint)
{
	addOriginalPoint(newPoint);
}

void PlotWidget::updateFilteredPoint(const int &newPoint)
{
	addFilteredPoint(newPoint);
}


