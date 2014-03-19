#include <iostream>
#include <fstream>
#include <string>
#include "Container.h"
#include "ItemPointer.h"
#include "Match.h"
#include "SharedDefines.h"
#include "BasketballMatch.h"
#include "FootballMatch.h"
#include "VolleyballMatch.h"
#include "TennisMatch.h"
using namespace std;

int main()
{
	Date d(1, 3, 2014);
	BasketballMatch b("bref", d, "bloc", "bhome", "bguest", "bleague" );
	FootballMatch f("fref", d, "floc", "fhome", "fguest", "fleague" );
	VolleyballMatch v("vref", d, "vloc", "vhome", "vguest", "vleague" );
	TennisMatch t("tref", d, "tloc", "tp1", "tp2", "tleague" );
	ItemPointer ib(&b);
	ItemPointer i_f(&f);
	ItemPointer iv(&v);
	ItemPointer it(&t);
	
	Container<ItemPointer> c;
	c.Insert(it);
	c.Insert(ib);
	c.Insert(i_f);
	c.Insert(iv);
	
	c.Save();
}
