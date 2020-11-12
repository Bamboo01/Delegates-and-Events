#pragma once
class Vec2
{
private:
	static int x;
	static int y;

public:
	Vec2()
	{
		x = 0;
		y = 0;
	}

	~Vec2()
	{

	}

	static void setx(int a)
	{
		x = a;
	}

	static void sety(int a)
	{
		y = a;
	}

	void test(int a)
	{
		std::cout << a << std::endl;
	}

	void test1(int a, int b, int c)
	{

	}

	void printCoords()
	{
		std::cout << x << " " << y << std::endl;
	}
};

int Vec2::x = 0;
int Vec2::y = 0;