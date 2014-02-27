#include <iostream>
#include "Container.h"

using namespace std;

int main()
{
	Container<int> a(5);
	a.Insert(7.5f);
	a.Insert('c');
	a.Insert(true);
	a.Insert(99);
	
	cout << a;
	

	a.~Container();
	cout << a;
}
