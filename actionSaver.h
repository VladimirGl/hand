#ifndef ACTIONSAVER_H
#define ACTIONSAVER_H

#include "actionFileStructure.h"

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QList>

/**
* @file actionSaver.h
*
* Implementation of ActionSaver class.
* Used to save action to the file.
*/

class ActionSaver : public ActionFileStructure
{
public:
	ActionSaver(const int &freq
			, const int &numOfDOF
			, const QString &fileName);
	~ActionSaver();

	/// Write one motion to the file.
	void writeData(const QList<int> &data);
	void stopRecord();

protected:
	void writePropertiesData(const int &freq, const int &numOfDOF);

private:
	QFile mFile;
	QTextStream mStream;
};

#endif // ACTIONSAVER_H
