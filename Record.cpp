template <class Item>
Container<Item>::Record::Record(const Item &item,  Container<Item>::Record *prev, Container<Item>::Record *next) : m_info(item), m_prev(prev), m_next(next) {}

template <class Item>
Container<Item>::Record::Record(const Container<Item>::Record &record)
{
	if (*this != record)
	{
		m_prev = NULL;
		m_info = record.m_info;
		m_next = DeepCopy(this, record.m_next); // previous Record to attach, next Record to copy
	}
}

template <class Item>
Container<Item>::Record::~Record()
{
	delete m_next; // cascade delete
}

template <class Item>
bool Container<Item>::Record::operator==(const Record &record) const
{
	return m_info == record.m_info;
}

template <class Item>
bool Container<Item>::Record::operator!=(const Record &record) const
{
	return m_info != record.m_info;
}

template <class Item>
bool Container<Item>::Record::operator>(const Record &record) const
{
	return m_info > record.m_info;
}

template <class Item>
bool Container<Item>::Record::operator<(const Record &record) const
{
	return m_info < record.m_info;
}

template <class Item>
bool Container<Item>::Record::operator>=(const Record &record) const
{
	return m_info >= record.m_info;
}

template <class Item>
bool Container<Item>::Record::operator<=(const Record &record) const
{
	return m_info <= record.m_info;
}

template <class Item>
typename Container<Item>::Record& Container<Item>::Record::operator=(Record record)
{
	Swap(*this, record); // swap list pointers
	
	// we dont need to delete our old data since it now
	// belongs to "record", which is a local copy and will
	// be destroyed after the return statement
	return *this;
}

// Creates a new Record copying it from "curr" and attaching it to the "prev"
template <class Item>
typename Container<Item>::Record* Container<Item>::Record::DeepCopy(Container<Item>::Record *prev , Container<Item>::Record *curr)
{	
	if (curr == NULL) // Reached the end of the list to copy
	    return NULL;
	
	Record *t = new typename Container<Item>::Record(curr->m_info);
	t->m_prev = prev;
	t->m_next = DeepCopy(t, curr->m_next);
	return t;                                                   
}

// Returns data contained in m_info
template <class Item>
Item Container<Item>::Record::GetInfo() const
{
	return m_info;
}
