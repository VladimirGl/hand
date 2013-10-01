#ifndef USERFILESTRUCTURE_H
#define USERFILESTRUCTURE_H

#include <QString>

/**
* All user files have the format:
*
*********************************************
*
* user_file
* DOF_list
* begin
* Two integer values, e.g:
* 42 42
* ...
* ...
* end
* conformity_list
* begin
* unknown number of integer values, e.g:
* 1 2 3
* 6 5 4
* 7
* 8 9
* end
*
*********************************************
*/

class UserFileStructure
{
public:
	UserFileStructure() :
		mHeader("user_file"),
		mDOFKeyWord("DOF_list"),
		mConformityKeyWord("conformity_list"),
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
