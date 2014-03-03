// <--------- Iterator -----------
template <class Item>
typename Container<Item>::Iterator& Container<Item>::Iterator::operator++()
{
	pointer = pointer->m_next;
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
	pointer = pointer->m_prev;
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
	return pointer; 
}
// ------------------------------>



// <------ Const_iterator --------
template <class Item>
typename Container<Item>::Const_iterator& Container<Item>::Const_iterator::operator++()
{
	pointer = pointer->m_next;
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
	pointer = pointer->m_prev;
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
	return pointer; 
}
// ------------------------------>
