#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>

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
	
	public:
		Record(const Item &item = NULL, Record *prev = NULL, Record *next = NULL);
		Record(const Record &record);
		~Record();
	
		// OPs
		bool operator==(const Record &record) const;
		bool operator!=(const Record &record) const;
		bool operator>(const Record &record) const;
		bool operator<(const Record &record) const;
		bool operator>=(const Record &record) const;
		bool operator<=(const Record &record) const;
		Record& operator=(const Record &record);
	
		friend std::ostream& operator<<(std::ostream &os, const typename Container<Item>::Record &record)
		{
			if (record.m_prev == NULL)
				os << "START -> ";
			
			os << record.m_info << " -> ";
			
			if (record.m_next == NULL)
				os << "END\n";
			else
				os << *(record.m_next);
				
			return os;   
		}
	
		// Helpers
		static Record* DeepCopy(Record *prev, Record *curr);
		void Update(const Item &item, Record *prev = NULL, Record *next = NULL);
		Item GetData() const;
	};
	
	Record *m_base;
	Record *m_end;
	
	void SetEnd(Record *record);

public:
	class Iterator
	{
	public:
		Record *pointer;
    
	public:
		friend class Const_iterator;
		Iterator(Record *pt) : pointer(pt) {}
		Iterator(const Iterator &i) : pointer(i.pointer) {}
		
		bool operator==(const Iterator &i) const { return pointer == i.pointer; }
		bool operator!=(const Iterator &i) const { return pointer != i.pointer; }
		
		friend std::ostream& operator<<(std::ostream &os, const typename Container<Item>::Iterator &i)
		{
			return os << *(i.pointer);
		}
		
		Iterator& operator++()
		{
			pointer = pointer->m_next;
			return *this;
		}
		
		Iterator& operator++(int)
		{
			Iterator t(*this);
			++(*this);
			return t;
		}
		
		Iterator& operator--()
		{
			pointer = pointer->m_prev;
			return *this;
		}
		
		Iterator& operator--(int)
		{
			Iterator t(*this);
			--(*this);
			return t;
		}
		
		Record* operator*()
		{
			return pointer; 
		}
	};
	
	class Const_iterator
	{
	private:
	    const Record *pointer;
    
	public:
		Const_iterator(Record *pt) : pointer(pt) {}
		Const_iterator(const Const_iterator &i) : pointer(i.pointer) {}
		Const_iterator(const Iterator &i) : pointer(i.pointer) {}
		
		bool operator==(const Const_iterator &i) const { return pointer == i.pointer; }
		bool operator!=(const Const_iterator &i) const { return pointer != i.pointer; }
		
		friend std::ostream& operator<<(std::ostream &os, const typename Container<Item>::Const_iterator &i)
		{
			    return os << *(i.pointer);
		}
		
		Const_iterator& operator++()
		{
		    pointer = pointer->m_next;
		    return *this;
		}
		    
		Const_iterator& operator++(int)
		{
		      Const_iterator t(*this);
		      ++(*this);
		      return t;
		}
		
		Const_iterator& operator--()
		{
			pointer = pointer->m_prev;
			return *this;
		}
		
		Const_iterator& operator--(int)
		{
			Const_iterator t(*this);
			--(*this);
			return t;
		}
		
		const Record* operator*() const
		{
			return pointer; 
		}
	};
    
	Container();
	Container(const Item &item);
	Container(const Container &cont);
	~Container();
	
	// OPs
	bool operator==(const Container &cont) const;
	bool operator!=(const Container &cont) const;
	Container<Item>& operator=(const Container &cont);
	Container<Item> operator+(const Container &cont) const;
	Container<Item> operator-(const Container &cont) const;
	
	friend std::ostream& operator<< <>(std::ostream &os, const Container<Item> &cont);
	
	// List management
	void Insert(const Item &item);
	void Remove(const Item &item);
	void RemoveAll(const Item &item);
	Record* Find(const Item &item);

	// Helpers
	Iterator Begin();
	Const_iterator Begin() const; // First element
	
	Iterator End();
	Const_iterator End() const; // Last + 1
	
	Iterator First();
	Const_iterator First() const; // Begin - 1
	
	Iterator Last();
	Const_iterator Last() const; // Last element
	
	
	bool IsEmpty();
	void Clear();
};

#include "Container.cpp"

#endif
