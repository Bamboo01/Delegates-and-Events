#include "Delegate.h"
#include <list>
#include <iostream>
#pragma once
//Made by sherwyn hey mr tang :D

template<typename ClassType, typename FunctionType, typename... params>
class Event
{
private:
	int DelegateCount;
	std::list<Delegate<ClassType, FunctionType, params...>> DelegateList;

public:

	Event()
	{
		DelegateCount = 0;
	}
	
	void operator+=(const Delegate<ClassType, FunctionType, params...>& a)
	{
		auto it = std::find(DelegateList.begin(), DelegateList.end(), a);
		if (it == DelegateList.end())
		{
			DelegateList.push_back(a);
			DelegateCount++;
		}
		else
		{
			std::cout << "Trying to add a delegate that already exists!" << std::endl;
		}
	}

	void operator-=(const Delegate<ClassType, FunctionType, params...>& a)
	{
		auto it = std::find(DelegateList.begin(), DelegateList.end(), a);
		if (it != DelegateList.end())
		{
			DelegateList.remove(a);
			DelegateCount--;
		}
		else
		{
			std::cout << "Trying to remove a delegate that doesn't exist!" << std::endl;
		}
	}

	void Invoke(params... a)
	{
		for (auto b : DelegateList)
		{
			b.Invoke(a...);
		}
	}
};