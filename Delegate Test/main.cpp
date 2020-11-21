#include "Vec2.h"
#include "EventSystem.h"

int main()
{
	Vec2 aaa;
	Vec2 aab;
	aaa.setx(1);
	aab.sety(10);
	{
		Vec2 abb;
		Vec2 bbb;
		EventSystem::eventlist.Invoke();
	}
	EventSystem::eventlist.Invoke();
	
	std::cout << (aaa.printcoordsdel == aab.printcoordsdel) << std::endl;
}