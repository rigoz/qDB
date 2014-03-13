// <--------- Iterator -----------
template <class Item>
typename Container<Item>::Iterator& Container<Item>::Iterator::operator++()
{
	m_data = m_data->m_next;
	return *this;
}

template <class Item>	
typename Container<Item>::Iterator Container<Item>::Iterator::operator++(int)
{
	Iterator t(*this);
	++(*this);
	return t;
}

template <class Item>
typename Container<Item>::Iterator& Container<Item>::Iterator::operator--()
{
	m_data = m_data->m_prev;
	return *this;
}

template <class Item>
typename Container<Item>::Iterator Container<Item>::Iterator::operator--(int)
{
	Iterator t(*this);
	--(*this);
	return t;
}

template <class Item>
typename Container<Item>::Record* Container<Item>::Iterator::operator*()
{
	return m_data; 
}
// ------------------------------>



// <------ Const_iterator --------
template <class Item>
typename Container<Item>::Const_iterator& Container<Item>::Const_iterator::operator++()
{
	m_data = m_data->m_next;
	return *this;
}

template <class Item>
typename Container<Item>::Const_iterator Container<Item>::Const_iterator::operator++(int)
{
	Const_iterator t(*this);
	++(*this);
	return t;
}

template <class Item>
typename Container<Item>::Const_iterator& Container<Item>::Const_iterator::operator--()
{
	m_data = m_data->m_prev;
	return *this;
}

template <class Item>
typename Container<Item>::Const_iterator Container<Item>::Const_iterator::operator--(int)
{
	Const_iterator t(*this);
	--(*this);
	return t;
}

template <class Item>
const typename Container<Item>::Record* Container<Item>::Const_iterator::operator*() const
{
	return m_data;
}
// ------------------------------>
