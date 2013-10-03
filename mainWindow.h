#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class QwtPlot;
class QwtPlotCurve;
class QwtPlotGrid;
class QwtSymbol;

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
	Q_OBJECT
	
public:
	MainWindow( QWidget * = NULL );
	~MainWindow();
	
private:
	QwtPlot *plot;
	QwtPlotGrid *grid;
	QwtPlotCurve *curve;
	QwtSymbol *symbol;

	QPolygonF points;
};

#endif // MAINWINDOW_H
