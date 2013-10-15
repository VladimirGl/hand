#include "actionSaver.h"

#include <QFile>
#include <QTextStream>

ActionSaver::ActionSaver(const int &freq, const int &numOfDOF, const QString &fileName)
{
	mFile.setFileName(fileName);
	mFile.open(QFile::WriteOnly | QFile::Truncate);

	mStream.setDevice(&mFile);

	writePropertiesData(freq, numOfDOF);
}

ActionSaver::~ActionSaver()
{
	mFile.close();
}

void ActionSaver::writeData(const QList<int> &data)
{
	const int size = data.size();

	for (int i = 0; i < size; i++) {
		mStream << data.at(i);

		if (i != (size - 1)) {
			mStream << " ";
		}
	}

	mStream << "\n";
}

void ActionSaver::stopRecord()
{
	mStream << ActionFileStructure::endActionKeyWord();

	mFile.close();
}

void ActionSaver::writePropertiesData(const int &freq, const int &numOfDOF)
{
	mStream << ActionFileStructure::header()
			<< "\n"
			<< ActionFileStructure::freqKeyWord()
			<< " "
			<< freq
			<< "\n"
			<< ActionFileStructure::DOFKeyWord()
			<< " "
			<< numOfDOF
			<< "\n"
			<< ActionFileStructure::startActionKeyWord()
			<< "\n";
}

