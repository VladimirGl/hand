#ifndef USERFILELOADER_H
#define USERFILELOADER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QList>

#include "userFileStructure.h"

/**
* @file userFileLoader.h
*
* Implementation of UserFileLoader class.
* Used to read user properties from the file.
* The first should be read information about DOFs,
* and after information aboud sensor-motor conformity.
*/

class UserFileLoader : public UserFileStructure
{
public:
	UserFileLoader(const QString &fileName);

	bool isFileCorrect() const { return mIsFileCorrect; }
	bool isFileEnd() const { return mIsFileEnd; }

	bool isDOFRead() const { return mIsDOFData; }
	bool isConformityRead() const { return mIsConformityData; }

	/// Returns QList of 2 elements, min and max values of DOF.
	QList<int> DOFList();

	/// Returns QList of unknown size. Each value mean motor number.
	QList<int> conformityList();

protected:
	void beginParse();

	void readDOF();
	void readConformity();

	/// DOF must lie in the interval from 0 to 1023.
	bool isDOFcorrect(const int &min, const int &max);

private:
	bool mIsDOFData;
	bool mIsConformityData;

	bool mIsFileCorrect;
	bool mIsFileEnd;

	QFile mFile;
	QTextStream mStream;
};

#endif // USERFILELOADER_H
