#ifndef CONTAINER_H
#define CONTAINER_H

#include "Record.h"
#include <iostream>

template<class Item> class Container;
template<class Item> std::ostream& operator<<(std::ostream &os, const Container<Item> &cont);

template <class Item = int>
class Container
{
private:
	Record<Item> *m_base;
	Record<Item> *m_end;

public:
	class Iterator;
	class Const_iterator;
    
	Container(const Item &item);
	Container(const Container &cont);
	~Container();
	
	// OPs
	bool operator==(const Container &cont) const;
	bool operator!=(const Container &cont) const;
	Container<Item>& operator=(const Container &cont);
	Container<Item> operator+(const Contaner &cont) const;
	Container<Item> operator-(const Container &cont) const;
	
	friend std::ostream& operator<< <>(std::ostream &os, const Container<Item> &cont);
	
	// List management
	void Insert(const Item &item, Record *point = End());
	void Remove(Record *r);
	void RemoveAll(const Item &item);
	Record* Find(const Item &item);

	// Helpers
	Iterator* Begin();
	Iterator* End();
	Const_iterator* Begin() const;
	Const_iterator* End() const;
	bool IsEmpty();
	void Clear();
};

#endif
