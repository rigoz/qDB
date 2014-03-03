#include <iostream>
#include "Container.h"

using namespace std;

int main()
{
	Container<int> a(1);
	a.Insert(2);
	a.Insert(3);
	/*a.Insert(4);
	a.Insert(5);
	a.Insert(6);
	a.Insert(7);
	a.Insert(8);*/
	
	Container<int> b(1);
	b.Insert(2);
	b.Insert(3);
	
	cout <<  a - b;
	
	//a.Remove(1);
	//a.Remove(2);
	//a.Remove(3);
	cout << "fine\n";
	
	
	/*
	Container<int> h(a);
	cout << h;
	Container<int> c;
	
	c = a + b;
	
	cout << "A = " << a << "B = " << b << "C = " << c;
	Container<int> d;
	d = a - b;
	cout  << "D = " << d;
	
	if (c.Find(20))
		cout << "trovato\n";
	else
		cout << "non trovato\n";*/
	
}
