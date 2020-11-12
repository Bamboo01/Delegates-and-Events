#include <iostream>
#include <functional>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Delegate.h"
#include "Vec2.h"
#include "EventSystem.h"
#include "Event.h"
#include "Test.h"

int main()
{
	//Delegate and Event Test
	Vec2 testvec;
	Test test1;
	Test test2;

	Delegate<void, int> setVecX(Vec2::setx);
	Delegate<void, int> setVecY(Vec2::sety);

	Event<void, int> vecevents;
	Event<void> voidevents;

	vecevents += &setVecX;
	vecevents += &setVecY;
	vecevents.Invoke(1);

	vecevents -= &setVecY;
	vecevents.Invoke(10);

	testvec.printCoords();
}