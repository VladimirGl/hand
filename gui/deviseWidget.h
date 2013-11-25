#ifndef DEVISEWIDGET_H
#define DEVISEWIDGET_H

#include <QWidget>

#include <QStringList>

namespace Ui {
class DeviseWidget;
}

class DeviseWidget : public QWidget
{
	Q_OBJECT

public:
	explicit DeviseWidget(QWidget *parent = 0);
	~DeviseWidget();

public slots:
	void gloveConnectionChanged(const bool& isConnected, const QString& comment);
	void handConnectionChanged(const bool& isConnected, const QString& comment);

signals:
	void tryGloveConnect(const QString& port);
	void tryHandConnect(const QString& port);

protected slots:
	void fillPortList();

	void gloveConnection();
	void handConnection();

private:
	Ui::DeviseWidget *ui;

	QStringList mPortsList;
};

#endif // DEVISEWIDGET_H
