#ifndef USERFILESTRUCTURE_H
#define USERFILESTRUCTURE_H

#include <QString>

class UserFileStructure
{
public:
	UserFileStructure() :
		mHeader("user_file"),
		mDOFKeyWord("DOF_list"),
		mConformityKeyWord("Conformity_list"),
		mStartWord("begin"),
		mEndWord("end")
	{}

	QString header() { return mHeader; }
	QString DOFKeyWord() { return mDOFKeyWord; }
	QString conformityKeyWord() { return mConformityKeyWord; }
	QString startWord() { return mStartWord; }
	QString endWord() { return mEndWord; }

private:
	const QString mHeader;
	const QString mDOFKeyWord;
	const QString mConformityKeyWord;
	const QString mStartWord;
	const QString mEndWord;
};

#endif // USERFILESTRUCTURE_H
