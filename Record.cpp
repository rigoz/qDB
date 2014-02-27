template <class Item>
Container<Item>::Record::Record(const Item &item,  Container<Item>::Record *prev, Record *next) : m_info(item), m_prev(prev), m_next(next) {}

template <class Item>
Container<Item>::Record::Record(const Container<Item>::Record &record)
{
	if (*this != record)
	{
		m_prev = NULL;
		m_info = record.m_info;
		m_next = DeepCopy(this, record.m_next);
	}
}

template <class Item>
Container<Item>::Record::~Record()
{
	delete m_next;
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
typename Container<Item>::Record& Container<Item>::Record::operator=(const Record &record)
{
	if (*this != record)
	{
		m_info = record.m_info;
		m_prev = NULL;
		DeepCopy(this, record.m_next);
	}
}

template <class Item>
typename Container<Item>::Record* Container<Item>::Record::DeepCopy(Container<Item>::Record *prev , Container<Item>::Record *curr)
{	
	if (curr == NULL)
	    return NULL;
	
	Record *t = new Record(curr->m_info);
	t->m_prev = prev;
	t->m_next = DeepCopy(t, curr->m_next);
	return t;                                                   
}

template <class Item>
void Container<Item>::Record::Update(const Item &item, Container<Item>::Record *prev, Container<Item>::Record *next)
{
	m_info = item;
	
	if (prev != NULL)
	    m_prev = prev;
	
	if (next != NULL)
	    m_next = next;
}

template <class Item>
Item Container<Item>::Record::GetData() const
{
	return m_info;
}
