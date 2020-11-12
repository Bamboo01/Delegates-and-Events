#include "Delegate.h"
#include <vector>
#include <unordered_map>
#include <memory>
#pragma once

template<typename FunctionType, typename... params >
class Event
{
private:
	std::unordered_map <IDelegate<FunctionType, params...>*, IDelegate<FunctionType, params...>> DelegateList;

public:

	Event()
	{

	}
	
	void operator+=(IDelegate<FunctionType, params...>* a)
	{
		DelegateList.insert(std::make_pair(a, *a));
	}

	void operator-=(IDelegate<FunctionType, params...>* a)
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