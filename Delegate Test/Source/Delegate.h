#include <functional>
#include <unordered_map>
#include <list>
#include <assert.h>

#pragma once
/*
I have no idea why this solves my variadic placeholders issue
THANKS STACKOVERFLOW

|
|	FIX BELOW
|
v

https://stackoverflow.com/questions/38680931/omit-stdplaceholders-in-stdbind
*/

template <class C, typename Ret, typename ... Ts>
std::function<Ret(Ts...)> bind_this(C* c, Ret(C::* m)(Ts...))
{
	return [=](auto&&... args) { return (c->*m)(std::forward<decltype(args)>(args)...); };
}

template <class C, typename Ret, typename ... Ts>
std::function<Ret(Ts...)> bind_this(const C* c, Ret(C::* m)(Ts...) const)
{
	return [=](auto&&... args) { return (c->*m)(std::forward<decltype(args)>(args)...); };
}

template<typename FunctionType, typename... params>
class Delegate
{
private:
	template <typename ClassType>
	using MemberFunctionPointer = FunctionType(ClassType::*)(params...);

protected:
	std::function<FunctionType(params...)> func;

	//THIS IS HIGHLY ILLEGAL YOU KNOW
	//IT WORKS DOE
	void* funcptr;
	void* objectptr;

public:
	Delegate()
	{
		func = nullptr;
		funcptr = nullptr;
		objectptr = nullptr;
	}

	~Delegate()
	{

	}

	FunctionType Invoke(params... a)
	{
		assert(func != nullptr, "Delegate was not set up, but invokation was called!");
		return func(a...);
	}

	template <typename ClassType>
	void Set(ClassType* a, MemberFunctionPointer<ClassType> b)
	{
		func = bind_this(a, b);
		objectptr = a;
		funcptr = &b;
	}

	void Set(FunctionType a(params...))
	{
		objectptr = nullptr;
		func = a;
		funcptr = *a;
	}

	bool operator== (const Delegate<FunctionType, params...>& rhs) const
	{
		if ((!this->objectptr && rhs.objectptr) || (this->objectptr && !rhs.objectptr))
		{
			return false;
		}
		else if (this->objectptr != rhs.objectptr)
		{
			return false;
		}
		else
		{
			if (this->funcptr == rhs.funcptr)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	Delegate<FunctionType, params...>& operator=(const Delegate<FunctionType, params...>& other)
	{
		this->func = other.func;
		this->funcptr = other.funcptr;
		this->objectptr = other.objectptr;
		return *this;
	}
};