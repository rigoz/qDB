#ifndef CONTAINER_H
#define CONTAINER_H

#include "Record.h"
#include <iostream>

template <class Item = int>
class Container
{
private:
	Record<Item> *m_base;
	Record<Item> *m_end;

public:

};

#endif
