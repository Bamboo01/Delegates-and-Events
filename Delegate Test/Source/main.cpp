#include "Vec2.h"
#include "EventSystem.h"
#include "Delegate.h"
#include "Event.h"
#include <string>

using namespace std;

static void test(string aaa)
{
	cout << aaa << "\n";
	return;
}

int main()
{
	string nigga;
	Delegate<void, string> str_func;
	Delegate<void, string> str_func1;
	Delegate<void, string> str_func2;
	Delegate<void, string> str_func3;
	Delegate<void, string> str_func4;

	str_func.Set(&test);
	str_func1.Set(&test);
	str_func2.Set(&test);
	str_func3.Set(&test);
	str_func4.Set(&test);

	Event<void, string> str_event;
	str_event += str_func;
	str_event += str_func1;
	str_event += str_func2;
	str_event += str_func3;
	str_event += str_func4;

	str_event.Invoke("TTNEJITNEKT");

	return 0;
}