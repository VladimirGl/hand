#ifndef ACTIONFILEREADER_H
#define ACTIONFILEREADER_H

#include <QString>

namespace FreqLimits {
const int maxFreq = 10000;
const int minFreq = 100;
}

namespace DOFLimits {
const int minDOFs = 1;
const int maxDOFs = 25;
}

class ActionFileStructure
{
public:
	ActionFileStructure() :
		mHeader("action_file"),
		mFreqKeyWord("frequency_info"),
		mDOFKeyWord("DOF_info"),
		mStartAction("begin_action"),
		mEndAction("end_action")
	{}

	QString header() const { return mHeader; }
	QString freqKeyWord() const { return mFreqKeyWord; }
	QString DOFKeyWord() const { return mDOFKeyWord; }
	QString startActionKeyWord() const { return mStartAction; }
	QString endActionKeyWord() const { return mEndAction; }

private:
	const QString mHeader;
	const QString mFreqKeyWord;
	const QString mDOFKeyWord;
	const QString mStartAction;
	const QString mEndAction;
};

#endif // ACTIONFILEREADER_H
