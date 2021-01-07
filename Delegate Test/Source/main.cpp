#include "Vec2.h"
#include "EventSystem.h"

int main()
{
	/*
	*** QUICK EXPLANATION ***
	EventSystem is a singleton

	Vec2 constructor always calls the EventSystem instance to add the printcoordinate delegate to it
	printcoordinatedel contains the functor to print current coordinates

	You should see an error when running that the same delegate is always being added
	This is because it is trying to add a delegate to a static function
	*/
	Vec2 aaa;
	Vec2 aab;
	aaa.setx(1);
	aab.sety(10);
	{
		Vec2 abb;
		Vec2 bbb;
		//aaa, aab, abb, bbb have printcoords called
		EventSystem::PrintVec2CoordEvent.Invoke();
	}
	//only aaa and aab have printcoords called
	EventSystem::PrintVec2CoordEvent.Invoke();
	
	//Meant to show that the delegates are different due to them belonging to different objects, despite having the same functor
	std::cout << "(aaa.printcoordsdel == aab.printcoordsdel) = " << (aaa.printcoordsdel == aab.printcoordsdel) << std::endl;

	//Meant to show that the delegates are the same due to them pointing to a static function
	std::cout << "(aaa.printnumvec2del == aab.printnumvec2del) = " << (aaa.printnumvec2del == aab.printnumvec2del) << std::endl;

	//Meant to show that the delegates are different due to them having different funtors, despite belonging to the same object
	std::cout << "(aaa.printnumvec2del == aaa.printcoordsdel) = " << (aaa.printnumvec2del == aaa.printcoordsdel) << std::endl;
}