#ifndef ACTION_H
#define ACTION_H

#include <QWidget>

namespace Ui {
class Action;
}

class ActionWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ActionWidget(QWidget *parent = 0);
	~ActionWidget();

	void dataEnd();
	void saveingEnd();

signals:
	void startLoading(const QString &fileName);
	void stopLoading();

	void startSaveing(const QString &fileName, const int &freq);
	void stopSaveing();

protected slots:
	void startLoad();
	void startSave();

	void stopLoad();
	void stopSave();

private:
	Ui::Action *ui;
};

#endif // ACTION_H
