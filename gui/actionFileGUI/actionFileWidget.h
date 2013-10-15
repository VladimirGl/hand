#ifndef ACTIONFILEWIDGET_H
#define ACTIONFILEWIDGET_H

#include <QWidget>

namespace Ui {
class ActionFileWidget;
}

class ActionFileWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ActionFileWidget(QWidget *parent = 0);
	~ActionFileWidget();

private:
	Ui::ActionFileWidget *ui;
};

#endif // ACTIONFILEWIDGET_H
