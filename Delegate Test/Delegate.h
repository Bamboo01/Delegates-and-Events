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
class IDelegate
{
protected:
	std::function<FunctionType(params...)> func;

public:
	IDelegate()
	{

	}

	~IDelegate()
	{

	}

	FunctionType Invoke(params... a)
	{
		return func(a...);
	}
};

template<typename FunctionType, typename... params>
class StaticDelegate : public IDelegate<FunctionType, params...>
{
public:
	StaticDelegate(FunctionType a(params...))
	{
		this->func = a;
	}

	~StaticDelegate()
	{

	}
};

template<typename ClassType, typename FunctionType, typename... params>
class Delegate : public IDelegate<FunctionType, params...>
{
private:
	using MemberFunctionPointer = FunctionType(ClassType::*)(params...);	

public:
	Delegate(ClassType* a, MemberFunctionPointer b)
	{
		this->func = bind_this(a, b);
	}

	~Delegate()
	{

	}
};