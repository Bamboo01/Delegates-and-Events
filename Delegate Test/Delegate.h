#include <functional>
#include <unordered_map>
#include <list>

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

template<typename ClassType, typename FunctionType, typename... params>
class Delegate
{
protected:
	using MemberFunctionPointer = FunctionType(ClassType::*)(params...);

	std::function<FunctionType(params...)> func;
	ClassType* objectptr;
	MemberFunctionPointer funcptr;

public:
	Delegate(ClassType* a, MemberFunctionPointer b)
	{
		//Member function
		objectptr = a;
		funcptr = b;
		func = bind_this(a, b);
	}

	Delegate(FunctionType a(params...))
	{
		//Static function
		objectptr = nullptr;
		funcptr = nullptr;
		this->func = a;
	}

	Delegate(const Delegate<ClassType, FunctionType, params...>& a)
	{
		this->func = a.func;
		this->funcptr = a.funcptr;
		this->objectptr = a.objectptr;
	}

	Delegate()
	{

	}

	~Delegate()
	{

	}

	FunctionType Invoke(params... a)
	{
		return func(a...);
	}

	bool operator== (const Delegate<ClassType, FunctionType, params...>& rhs) const
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

	Delegate<ClassType, FunctionType, params...>& operator=(const Delegate<ClassType, FunctionType, params...>& other)
	{
		this->func = other.func;
		this->funcptr = other.funcptr;
		this->objectptr = other.objectptr;
		return *this;
	}
};