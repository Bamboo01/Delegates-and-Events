#include "Delegate.h"
#include <list>
#include <iostream>
#pragma once

template<typename FunctionType, typename... params>
class Event
{
private:
	int DelegateCount;
	std::list<Delegate<FunctionType, params...>> DelegateList;

public:

	Event()
	{
		DelegateCount = 0;
	}
	
	void operator+=(const Delegate<FunctionType, params...>& a)
	{
		DelegateList.push_back(a);
		DelegateCount++;
	}

	void operator-=(const Delegate<FunctionType, params...>& a)
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