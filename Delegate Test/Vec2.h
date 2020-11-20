#include "Delegate.h"

#pragma once
class Vec2
{
private:
	int x;
	int y;
	static int numVec2;
	Delegate<Vec2, void> myprintcoord;

public:
	Vec2();

	~Vec2();

	void setx(int a);

	void sety(int a);

	void printCoords();

	static void printNumVec2();
};
