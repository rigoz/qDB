#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include "SharedDefines.h"


template<class Item> class Container;
template<class Item> std::ostream& operator<<(std::ostream &os, const Container<Item> &cont);

template <class Item = int>
class Container
{
private:
	class Record
	{
	    
	friend class Container;
	
	private:
		Item m_info;
		Record *m_prev;
		Record *m_next;
	
		static Record* DeepCopy(Record *prev, Record *curr);
		
	public:
		Record(const Item &item = NULL, Record *prev = NULL, Record *next = NULL);
		Record(const Record &record);
		~Record();
	
		// <----------- Operators ------------
		bool operator==(const Record &record) const;
		bool operator!=(const Record &record) const;
		bool operator>(const Record &record) const;
		bool operator<(const Record &record) const;
		bool operator>=(const Record &record) const;
		bool operator<=(const Record &record) const;
		Record& operator=(Record record);
	
		// op<< for a nested template class cannot be implemented outside 
		friend std::ostream& operator<<(std::ostream &os, const typename Container<Item>::Record &record)
		{
			os << record.m_info << " ";
			
			if (record.m_next != NULL)
				os << *(record.m_next);
				
			return os;   
		}
		// ----------------------------------->
	
	
		// <------------ Helpers --------------
		Item GetData() const;
		// ----------------------------------->
	};
	
	Record *m_base;
	Record *m_end;
	unsigned int m_size;
	
	void SetEnd(Record *record);
	void SetEmpty();
	void RemoveBoundaries(Record *limit);

public:
	class Iterator
	{
	public:
		Record *pointer;
    
	public:
		friend class Const_iterator;
		Iterator(Record *pt) : pointer(pt) {}
		Iterator(const Iterator &i) : pointer(i.pointer) {}
		
		// <----------- Operators ------------
		bool operator==(const Iterator &i) const { return pointer == i.pointer; }
		bool operator!=(const Iterator &i) const { return pointer != i.pointer; }
		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator--();
		Iterator operator--(int);
		Record* operator*();
		
		// op<< for a nested template class cannot be implemented outside 
		friend std::ostream& operator<<(std::ostream &os, const typename Container<Item>::Iterator &i) { return os << *(i.pointer);}
		// ----------------------------------->
	};
	
	class Const_iterator
	{
	private:
	    const Record *pointer;
    
	public:
		Const_iterator(Record *pt) : pointer(pt) {}
		Const_iterator(const Const_iterator &i) : pointer(i.pointer) {}
		Const_iterator(const Iterator &i) : pointer(i.pointer) {}
		
		// <----------- Operators ------------
		bool operator==(const Const_iterator &i) const { return pointer == i.pointer; }
		bool operator!=(const Const_iterator &i) const { return pointer != i.pointer; }
		Const_iterator& operator++();  
		Const_iterator operator++(int);
		Const_iterator& operator--();
		Const_iterator operator--(int);
		const Record* operator*() const;
		
		// op<< for a nested template class cannot be implemented outside 
		friend std::ostream& operator<<(std::ostream &os, const typename Container<Item>::Const_iterator &i) { return os << *(i.pointer); }
		// ----------------------------------->
	};
    
	Container();
	Container(const Item &item);
	Container(const Container &cont);
	~Container();
	
	// <----------- Operators ------------
	bool operator==(const Container &cont) const;
	bool operator!=(const Container &cont) const;
	Container<Item>& operator=(Container cont);
	Container<Item> operator+(Container cont) const;
	Container<Item> operator-(const Container &cont) const;
	
	friend std::ostream& operator<< <>(std::ostream &os, const Container<Item> &cont);
	// ----------------------------------->
	
	
	// <-------- List management ----------
	void Insert(const Item &item);
	void Remove(const Item &item);
	void Remove(Record *record);
	void RemoveAll(const Item &item);
	Record* Find(const Item &item);
	const Record* Find(const Item &item) const;
	void Update(Record *record, const Item &item);
	// ----------------------------------->
	
	
	// <----------- Iterators -------------
	// First element
	Iterator Begin();
	Const_iterator Begin() const;
	
	// Last element + 1
	Iterator End();
	Const_iterator End() const;
	
	// Begin - 1
	Iterator First();
	Const_iterator First() const;
	
	// Last element
	Iterator Last();
	Const_iterator Last() const;
	// ----------------------------------->
	
	
	// <------------ Helpers --------------
	static void Swap(Container &c1, Container &c2);
	static void Swap(Record &r1, Record &r2);
	bool IsEmpty() const;
	void Clear();
	unsigned int Size() const;
	// ----------------------------------->
};

#include "Container.cpp"
#include "Record.cpp"
#include "Iterator.cpp"

#endif
