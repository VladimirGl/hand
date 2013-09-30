#include "userFileSaver.h"

UserFileSaver::UserFileSaver(const QString &fileName) :
	mIsConformityDataStart(false)
{
	mFile.setFileName(fileName);
	mFile.open(QFile::WriteOnly | QFile::Truncate);

	mStream.setDevice(&mFile);

	startWriteFile();
}

void UserFileSaver::writeDOFData(const int &min, const int &max)
{
	mStream << min
			<< " "
			<< max
			<< "\n";
}

void UserFileSaver::writeConformityData(const QList<int> &data)
{
	if (!mIsConformityDataStart) {
		writeConformityHeaders();

		mIsConformityDataStart = true;
	}

	const int size = data.size();

	for (int i = 0; i < size; i++) {
		mStream << data.at(i);

		if (i != (size - 1)) {
			mStream << " ";
		}
	}

	mStream << "\n";
}

void UserFileSaver::stopWriteFile()
{
	mStream << UserFileStructure::endWord();

	mFile.close();
}

void UserFileSaver::startWriteFile()
{
	mStream << UserFileStructure::header()
			<< "\n"
			<< UserFileStructure::DOFKeyWord()
			<< "\n"
			<< UserFileStructure::startWord()
			<< "\n";
}

void UserFileSaver::writeConformityHeaders()
{
	mStream << UserFileStructure::endWord()
			<< "\n"
			<< UserFileStructure::conformityKeyWord()
			<< "\n"
			<< UserFileStructure::startWord();
}


