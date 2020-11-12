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

	StaticDelegate<void, int> setVecX(Vec2::setx);
	StaticDelegate<void, int> setVecY(Vec2::sety);

	Delegate<Vec2, void> printVecDelegate(&testvec, &Vec2::printCoords);
	Delegate<Vec2, void, int> testtestest(&testvec, &Vec2::test);
    Delegate<Vec2, void, int, int, int> testtestest1(&testvec, &Vec2::test1);


	Event<void, int> vecevents;
	Event<void> voidevents;

	vecevents += &setVecX;
	vecevents += &setVecY;

	vecevents.Invoke(1);

	vecevents -= &setVecY;
	vecevents.Invoke(10);

	vecevents += &testtestest;

	vecevents.Invoke(10);
}