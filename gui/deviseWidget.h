#ifndef DEVISEWIDGET_H
#define DEVISEWIDGET_H

#include <QWidget>

namespace Ui {
class DeviseWidget;
}

class DeviseWidget : public QWidget
{
	Q_OBJECT

public:
	explicit DeviseWidget(QWidget *parent = 0);
	~DeviseWidget();

private:
	Ui::DeviseWidget *ui;
};

#endif // DEVISEWIDGET_H
