#include <iostream>
#include <string>
#include "Container.h"
#include "Match.h"
#include "SharedDefines.h"
using namespace std;

int main()
{
	string name("Ciao");
	string surname("Miao");
	Referee r;
	r.name = "CIAO";
	r.surname = "MIAO";
	r.telephone = "0495590908";
	Match m(r, 57, "Piazzola");
	
	cout << m.GetId();
}
