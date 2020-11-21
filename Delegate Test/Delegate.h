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
	using MemberFunctionPointer = FunctionType(ClassType::*)(params...);

	template <typename ClassType>
	void Set(ClassType* a, MemberFunctionPointer<ClassType> b)
	{
		objectptr = a;
		funcptr = &b;
		func = bind_this(a, b);
	}

	void Set(FunctionType a(params...))
	{
		objectptr = nullptr;
		funcptr = nullptr;
		func = a;
	}

	bool operator== (const Delegate<FunctionType, params...>& rhs) const
	{
		if (this->objectptr == rhs.objectptr &&
			this->funcptr == rhs.funcptr)
		{
			//Check if this is
			//1) 2 static functions OR
			//2) 2 member functions pointing to the same thing
			if (this->objectptr != nullptr && this->funcptr != nullptr)
			{
				//2 member functions pointing to the same thing
				return true;
			}
			else
			{
				//2 static functions
				FunctionType(* const* ptr_lhs)(params...) = this->func.target<FunctionType(*)(params...)>();
				FunctionType(* const* ptr_rhs)(params...) = rhs.func.target<FunctionType(*)(params...)>();
				return ptr_lhs == ptr_rhs;
			}
		}
		else
		{
			//One is a static function, the other is a member function
			return false;
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