#include "Delegate.h"

#pragma once
class Vec2
{
private:
	int x;
	int y;
	static int numVec2;

public:
	Delegate<void> printcoordsdel;

	Vec2();

	~Vec2();

	void setx(int a);

	void sety(int a);

	void printCoords();

	void forceEventAdd();

	void forceEventRemove();

	static void printNumVec2();
};
