#pragma once
#include "Event.h"
#include "Vec2.h"

class EventSystem
{
public:
	static Event<Vec2, void> eventlist;

	EventSystem()
	{

	}

	~EventSystem()
	{

	}
};


