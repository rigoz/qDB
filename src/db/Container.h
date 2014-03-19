#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <fstream>
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
			os << record.m_info << "\n";
			
			if (record.m_next != NULL)
				os << *(record.m_next);
				
			return os;   
		}
		// ----------------------------------->
	
	
		// <------------ Helpers --------------
		Item GetInfo() const;
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
		Record *m_data;
	
	public:
		friend class Const_iterator;
		Iterator(Record *pt) : m_data(pt) {}
		Iterator(const Iterator &i) : m_data(i.m_data) {}
		
		// <----------- Operators ------------
		bool operator==(const Iterator &i) const { return m_data == i.m_data; }
		bool operator!=(const Iterator &i) const { return m_data != i.m_data; }
		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator--();
		Iterator operator--(int);
		Record* operator*();
		
		// op<< for a nested template class cannot be implemented outside 
		friend std::ostream& operator<<(std::ostream &os, const typename Container<Item>::Iterator &i) { return os << *(i.m_data);}
		// ----------------------------------->
	};
	
	class Const_iterator
	{
	private:
		const Record *m_data;
	
	public:
		Const_iterator(Record *pt) : m_data(pt) {}
		Const_iterator(const Const_iterator &i) : m_data(i.m_data) {}
		Const_iterator(const Iterator &i) : m_data(i.m_data) {}
		
		// <----------- Operators ------------
		bool operator==(const Const_iterator &i) const { return m_data == i.m_data; }
		bool operator!=(const Const_iterator &i) const { return m_data != i.m_data; }
		Const_iterator& operator++();  
		Const_iterator operator++(int);
		Const_iterator& operator--();
		Const_iterator operator--(int);
		const Record* operator*() const;
		
		// op<< for a nested template class cannot be implemented outside 
		friend std::ostream& operator<<(std::ostream &os, const typename Container<Item>::Const_iterator &i) { return os << *(i.m_data); }
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
	void Remove(Record *record);
	void RemoveAll(const Item &item);
	Container Find(const Item &item);
	const Container Find(const Item &item) const;
	static void Update(Record *record, const Item &item);
	Record* GetRecord(const Item &item);
	// ----------------------------------->
	
	// <----------- File I/O --------------
	void Save() const;
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
