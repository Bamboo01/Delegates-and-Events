#include "Vec2.h"
#include <iostream>
#include "EventSystem.h"

int Vec2::numVec2 = 0;

Vec2::Vec2()
{
	printcoordsdel.Set<Vec2>(this, &Vec2::printCoords);
	printcoordsdeltemp.Set<Vec2>(this, &Vec2::printCoords);

	printnumvec2del.Set(printNumVec2);

	EventSystem::PrintVec2CoordEvent += printnumvec2del;
	EventSystem::PrintVec2CoordEvent += printcoordsdel;

	x = 0;
	y = 0;
	numVec2++;
}

Vec2::~Vec2()
{
	EventSystem::PrintVec2CoordEvent -= printcoordsdel;
	EventSystem::PrintVec2CoordEvent -= printnumvec2del;
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
	std::cout << "Printing coordinates for " << this << ":" << x << " " << y << std::endl;
}

void Vec2::forceEventAdd()
{
	EventSystem::PrintVec2CoordEvent += printcoordsdel;
}

void Vec2::forceEventRemove()
{
	EventSystem::PrintVec2CoordEvent -= printcoordsdel;
}

void Vec2::printNumVec2()
{
	std::cout << "Printing number of Vec2's instanstiated: " << numVec2 << std::endl;
}