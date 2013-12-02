#ifndef MAP_H
#define MAP_H

/// amazing class with love

class Map
{
public:
	static int map(int const& value
			, int const& firstMin, int const& firstMax
			, int const& secondMin, int const& secondMax)
	{
		return (((value - firstMin)
				* (secondMax - secondMin)
				/ (firstMax - firstMin))
				+ secondMin);
	}
};

#endif // MAP_H
