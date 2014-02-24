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
	Record(const Item &item = 0);
	Record(const Record &record);
	~Record();
	
	bool operator==(const Record &record) const;
	bool operator!=(const Record &record) const;
	bool operator>(const Record &record) const;
	bool operator<(const Record &record) const;
	bool operator>=(const Record &record) const;
	bool operator<=(const Record &record) const;
	
	friend std::ostream& operator<< <>(std::ostream &os, const Record<Item> &record);
};

#include "Record.cpp"

#endif
