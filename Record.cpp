template <class Item>
Record<Item>::Record(const Item &item) : m_info(item)
{
	m_prev = NULL;
	m_next = NULL;
}

template <class Item>
Record<Item>::Record(const Record &record)
{
	// deep copy
}

template <class Item>
Record<Item>::~Record()
{
	if (m_next != NULL)
		delete m_next;
}

template <class Item>
bool Record<Item>::operator==(const Record &record) const
{
	return m_info == record.m_info;
}

template <class Item>
bool Record<Item>::operator!=(const Record &record) const
{
	return m_info != record.m_info;
}

template <class Item>
bool Record<Item>::operator>(const Record &record) const
{
	return m_info > record.m_info;
}

template <class Item>
bool Record<Item>::operator<(const Record &record) const
{
	return m_info < record.m_info;
}

template <class Item>
bool Record<Item>::operator>=(const Record &record) const
{
	return m_info >= record.m_info;
}

template <class Item>
bool Record<Item>::operator<=(const Record &record) const
{
	return m_info <= record.m_info;
}

template <class Item>
std::ostream& operator<<(std::ostream &os,const Record<Item> &record)
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
