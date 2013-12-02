#ifndef DEGREEOFFREEDOM_H
#define DEGREEOFFREEDOM_H

/**
* @file degreeOfFreedom.h
*
* Implementation of DegreeOfFreedom class.
* Contains two values, which varies within the flex sensor datas.
*/

class DegreeOfFreedom
{
public:
	DegreeOfFreedom(int const& newMin, int const& newMax) :
		mMinimum(newMin),
		mMaximum(newMax)
	{}

	void setMin(int const& newMin) { mMinimum = newMin; }
	void setMax(int const& newMax) { mMaximum = newMax; }

	int min() const { return mMinimum; }
	int max() const { return mMaximum; }

private:
	int mMinimum;
	int mMaximum;
};

class SensorState : public DegreeOfFreedom
{
	SensorState(int const& newMin, int const& newMax) :
		DegreeOfFreedom(newMin, newMax),
		mCurrent(0)
	{}

	void setCurr(int const& newCurr) { mCurrent = newCurr; }

	int curr() const { return mCurrent; }

private:
	int mCurrent;
};

#endif // DEGREEOFFREEDOM_H
