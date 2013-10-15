#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QList>
#include <QQueue>
#include <QPointF>
#include "qwt_plot.h"

class QwtPlotCurve;
class QwtPlotGrid;

class PlotWidget : public QwtPlot
{
	Q_OBJECT
public:
	PlotWidget();
	~PlotWidget();

	void addOriginalPoint(const int &newPoint);
	void addFilteredPoint(const int &newPoint);

	void setFilteredVisible(bool isVisible);

public slots:
	void updateOriginalPoint(const int &newPoint);
	void updateFilteredPoint(const int &newPoint);

private:
	QwtPlotCurve *mOriginalCurve;
	QwtPlotCurve *mFilteredCurve;

	QwtPlotGrid* mGrid;

	QQueue<qreal> mOriginalData;
	QQueue<qreal> mFilteredData;

	QList<qreal> mIterator;
};

#endif // PLOTWIDGET_H
