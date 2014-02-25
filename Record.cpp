template <class Item>
Record<Item>::Record(const Item &item,  Record *prev, Record *next) : m_info(item), m_prev(prev), m_next(next) {}

template <class Item>
Record<Item>::Record(const Record &record)
{
	if (*this != record)
	{
		m_info = record.m_info;
		m_prev = NULL;
		DeepCopy(this, record.m_next);
	}
}

template <class Item>
Record<Item>::~Record()
{
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
Record<Item>& Record<Item>::operator=(const Record &record)
{
	if (*this != record)
	{
		m_info = record.m_info;
		m_prev = NULL;
		DeepCopy(this, record.m_next);
	}
}

template <class Item>
std::ostream& operator<<(std::ostream &os,const Record<Item> &record)
{
	if (record.m_prev == NULL)
		os << "START -> \n";
	
	os << &record << " = | " << record.m_prev << " ";
	os << record.m_info << " ";
	os << record.m_next << " | -> \n" ;
	
	if (record.m_next == NULL)
		os << "END\n";
	else
		os << *(record.m_next);
		
	return os;
}

template <class Item>
void Record<Item>::DeepCopy(Record *r1, Record *r2)
{
	if (r2 == NULL)
		return;
	
	r1->m_next = new Record<Item>(r2->m_info, r1);
	DeepCopy(r1->m_next, r2->m_next);
}

template <class Item>
Record<Item>* Record<Item>::Next(Record *r)
{
	m_next = r;
	return r;
}
