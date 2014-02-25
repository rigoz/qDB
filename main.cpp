#include <iostream>
#include "Record.h"

using namespace std;

int main()
{
	Record<int> a(5);
	Record<int> *t;
	
	t = a.Next(new Record<int>(8, &a));
	t = t->Next(new Record<int>(2, t));
	t = t->Next(new Record<int>(3, t));
	t = t->Next(new Record<int>(4, t));
	t = t->Next(new Record<int>(5, t));
	
	Record<int> b(45);
	t = b.Next(new Record<int>(456, &b));
	t = t->Next(new Record<int>(745, t));
	t = t->Next(new Record<int>(456, t));
	t = t->Next(new Record<int>(56343, t));
	t = t->Next(new Record<int>(324, t));
	
	cout << a;
	cout << b;
	
	a = b;
	cout << a;

}
