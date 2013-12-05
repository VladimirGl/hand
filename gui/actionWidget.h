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
	void savingEnd();

signals:
	void startLoading(const QString &fileName);
	void stopLoading();

	void startSaving(const QString &fileName, const int &freq);
	void stopSaving();

protected slots:
	void startLoad();
	void startSave();

	void stopLoad();
	void stopSave();

private:
	Ui::Action *ui;
};

#endif // ACTION_H
