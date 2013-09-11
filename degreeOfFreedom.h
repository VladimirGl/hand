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
	DegreeOfFreedom(int newMin, int newMax) :
		minimum(newMin),
		maximum(newMax)
	{}

	void setMin(int const& newMin) { minimum = newMin; }
	void setMax(int const& newMax) { maximum = newMax; }

	int min() const { return minimum; }
	int max() const { return maximum; }

private:
	int minimum;
	int maximum;
};

#endif // DEGREEOFFREEDOM_H
