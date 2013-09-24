#include "actionSaver.h"

#include <QFile>
#include <QTextStream>

#include <QTimer>

ActionSaver::ActionSaver(const int &freq, const int &numOfDOF, const QString &fileName) :
	mFreq(freq),
	mNumberOfDOF(numOfDOF)
{
	mFile.setFileName(fileName);
	mFile.open(QFile::WriteOnly | QFile::Truncate);

	mStream.setDevice(&mFile);

	writePropertiesData();

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SIGNAL(onReadyWrite()));
	timer->start(mFreq);
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

void ActionSaver::writePropertiesData()
{
	mStream << ActionFileStructure::header()
			<< "\n"
			<< ActionFileStructure::freqKeyWord()
			<< " "
			<< mFreq
			<< "\n"
			<< ActionFileStructure::DOFKeyWord()
			<< " "
			<< mNumberOfDOF
			<< "\n"
			<< ActionFileStructure::startActionKeyWord()
			<< "\n";
}

