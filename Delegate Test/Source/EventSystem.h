#pragma once
#include "Event.h"
#include "Vec2.h"

class EventSystem
{
public:
	static Event<void> PrintVec2CoordEvent;
	static Event<void> PrintNumVec2Event;

	EventSystem()
	{

	}

	~EventSystem()
	{

	}
};


