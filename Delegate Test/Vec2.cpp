#include "Vec2.h"
#include <iostream>
#include "EventSystem.h"

int Vec2::numVec2 = 0;

Vec2::Vec2()
{
	printcoordsdel.Set<Vec2>(this, &Vec2::printCoords);
	EventSystem::eventlist += printcoordsdel;
	x = 0;
	y = 0;
	numVec2++;
}

Vec2::~Vec2()
{
	EventSystem::eventlist -= printcoordsdel;
	numVec2--;
}

void Vec2::setx(int a)
{
	x = a;
}

void Vec2::sety(int a)
{
	y = a;
}

void Vec2::printCoords()
{
	std::cout << x << " " << y << std::endl;
}

void Vec2::forceEventAdd()
{
	EventSystem::eventlist += printcoordsdel;
}

void Vec2::forceEventRemove()
{
	EventSystem::eventlist -= printcoordsdel;
}

void Vec2::printNumVec2()
{
	std::cout << numVec2 << std::endl;
}