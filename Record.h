#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string.h>
#include "SharedDefines.h"

template<class Item> class Record;
template<class Item> std::ostream& operator<<(std::ostream &os, const Record<Item> &record);

template <class Item>
class Record
{
private:
	Item m_info;
	Record *m_prev;
	Record *m_next;
	
public:
	Record(const Item &item = 0, Record *prev = NULL, Record *next = NULL);
	Record(const Record &record);
	~Record();
	
	// OPs
	bool operator==(const Record &record) const;
	bool operator!=(const Record &record) const;
	bool operator>(const Record &record) const;
	bool operator<(const Record &record) const;
	bool operator>=(const Record &record) const;
	bool operator<=(const Record &record) const;
	Record<Item>& operator=(const Record &record);
	
	friend std::ostream& operator<< <>(std::ostream &os, const Record<Item> &record);
	
	// Helpers
	static void DeepCopy(Record *r1, Record *r2);
	Record<Item>* Next(Record *r2);
};

#include "Record.cpp"

#endif
