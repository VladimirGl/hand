#include "mainWindow.h"

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

MainWindow::MainWindow(QWidget *parent)
{
	plot = new QwtPlot(this);

	plot->setTitle("First Plot");
	plot->setCanvasBackground(Qt::white);
	plot->insertLegend(new QwtLegend());

	grid = new QwtPlotGrid();
	grid->attach(plot);

	curve = new QwtPlotCurve();
	curve->setTitle("Some Points");
	curve->setPen(Qt::blue, 4),
	curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);

	symbol = new QwtSymbol(QwtSymbol::Ellipse,
		QBrush(Qt::yellow), QPen(Qt::red, 2), QSize(8, 8));
	curve->setSymbol( symbol );

	points << QPointF(0.0, 2.3) << QPointF(1.0, 3.2)
		<< QPointF(2.0, 3.5) << QPointF(3.0, 5.8)
		<< QPointF(4.0, 8.9) << QPointF(5.0, 3.1);

	curve->setSamples(points);
	curve->attach(plot);


	plot->resize(600, 400);
}


MainWindow::~MainWindow()
{
	delete symbol;
	delete curve;
	delete grid;
	delete plot;
}
