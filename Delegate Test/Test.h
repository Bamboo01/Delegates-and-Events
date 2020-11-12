#include <iostream>
#pragma once
class Test
{
private:
	static int count;

public:
	Test()
	{
		count++;
	}

	~Test()
	{

	}

	static void HelloWorld()
	{

	}
};

int Test::count = 0;