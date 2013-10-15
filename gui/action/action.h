#ifndef ACTION_H
#define ACTION_H

#include <QWidget>

class FileActionPerformer;

namespace Ui {
class Action;
}

class Action : public QWidget
{
	Q_OBJECT

public:
	explicit Action(QWidget *parent = 0);
	~Action();

protected slots:
	void print();
	void loadData();
	void stopData();

private:
	Ui::Action *ui;

	FileActionPerformer *mActionPerformer;
};

#endif // ACTION_H
