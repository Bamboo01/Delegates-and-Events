#pragma once

template<typename FunctionType, typename... params >
class Delegate
{
private:
	std::function<FunctionType(params...)> func;

public:
	Delegate(FunctionType a(params...))
	{
		func = a;
	}

	~Delegate()
	{

	}

	void Invoke(params... a)
	{
		func(a...);
	}
};