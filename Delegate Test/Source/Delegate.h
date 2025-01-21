#include <functional>
#include <unordered_map>
#include <list>
#include <assert.h>
#include <typeinfo>
#include <iostream>
#include <immintrin.h>


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
	uintptr_t funcptr;
	uintptr_t objectptr;

public:
	Delegate()
	{
		func = nullptr;
		funcptr = 0x0;
		objectptr = 0x0;
	}

	~Delegate()
	{

	}

	FunctionType Invoke(params... a)
	{
		assert(func != nullptr && "Delegate was not set up, but invocation was called!");
		return func(a...);
	}

	template <typename ClassType>
	void Set(ClassType* a, MemberFunctionPointer<ClassType> b)
	{
		func = bind_this(a, b);
		objectptr = (uintptr_t)a;
		funcptr = *reinterpret_cast<uintptr_t*>(&b);
	}

	void Set(FunctionType a(params...))	
	{
		objectptr = (uintptr_t)nullptr;
		func = a;
		funcptr = reinterpret_cast<uintptr_t>(a);
	}

	bool operator== (const Delegate<FunctionType, params...>& rhs) const
	{
		// Check if the delegates both point to the same object
		// If they don't, continue
		if (this->objectptr != rhs.objectptr) return false;

		// Both the functions are either static or from the same object
		// We just need to check if the function pointer is the same
		return this->funcptr == rhs.funcptr;
	}

	Delegate<FunctionType, params...>& operator=(const Delegate<FunctionType, params...>& other)
	{
		this->func = other.func;
		this->funcptr = other.funcptr;
		this->objectptr = other.objectptr;
		return *this;
	}
};