#include "Delegate.h"
#include <vector>
#include <unordered_map>
#include <memory>
#pragma once

template<typename FunctionType, typename... params >
class Event
{
private:
	std::unordered_map <Delegate<FunctionType, params...>*, Delegate<FunctionType, params...>> DelegateList;

public:

	Event()
	{
		DelegateList = {};
	}
	
	void operator+=(Delegate<FunctionType, params...>* a)
	{
		DelegateList.insert(std::make_pair(a, *a));
	}

	void operator-=(Delegate<FunctionType, params...>* a)
	{
		DelegateList.erase(a);
	}

	void Invoke(params... a)
	{
		for (auto b : DelegateList)
		{
			b.second.Invoke(a...);
		}
	}
};