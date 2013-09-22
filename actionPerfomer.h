#ifndef ACTIONPERFOMER_H
#define ACTIONPERFOMER_H

#include <QObject>
#include <QList>

class ActionPerfomer : public QObject
{
	Q_OBJECT
public:
	ActionPerfomer();

	QList<int> *data() {};

signals:
	void commandIsSend();
};

#endif // ACTIONPERFOMER_H
