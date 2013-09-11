#ifndef SHADOWGLOVE_H
#define SHADOWGLOVE_H

#include "abstractGlove.h"

// после AbstractGlove нужно делать.

class Action;

class ShadowGlove : public AbstractGlove
{
public:
	ShadowGlove();

private:
	Action action;
};

#endif // SHADOWGLOVE_H
