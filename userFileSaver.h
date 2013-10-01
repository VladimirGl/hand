#ifndef USERFFILESAVER_H
#define USERFFILESAVER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QList>

#include "userFileStructure.h"

/**
* @file userFileSaver.h
*
* Implementation of UserFileSaver class.
* Used to save user properties to the file.
* The first should be written information about DOFs,
* and after information aboud sensor-motor conformity.
*/

class UserFileSaver : public UserFileStructure
{
public:
	UserFileSaver(const QString &fileName);

	/// Writes one new DOF data to the file.
	void writeDOFData(const int &min, const int &max);
	/// Writes one new sensor-motor conformity list to the file.
	void writeConformityData(const QList<int> &data);

	void stopWriteFile();

protected:
	void startWriteFile();
	void writeConformityHeaders();

private:
	bool mIsConformityDataStart;

	QFile mFile;
	QTextStream mStream;
};

#endif // USERFFILESAVER_H
