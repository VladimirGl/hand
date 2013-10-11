#ifndef ACTIONLOADER_H
#define ACTIONLOADER_H

#include "actionFileStructure.h"

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QList>

/**
* @file actionLoader.h
*
* Implementation of ActionLoader class.
* Used to read action from the file.
*/

class ActionLoader : ActionFileStructure
{
public:
	ActionLoader(const QString &fileName);

	bool isFileCorrect() const;
	bool isFileEnd() const;

	int freq() const { return mFreq; }

	/// Returns one motion.
	QList<int> data();

protected:
	void propertiesParse();

	void readFrequency();
	void readNumberOfDOF();

	bool isValueCorrect(const int &val) const;

private:
	QFile mFile;
	QTextStream mStream;

	bool mIsFileCorrect;
	bool mIsFileEnd;

	int mFreq;
	int mNumberOfDOF;
};

#endif // ACTIONLOADER_H
