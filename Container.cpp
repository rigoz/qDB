template <class Item>
Container<Item>::Container()
{
	m_base = NULL;
	m_end = NULL;
}

template <class Item>
Container<Item>::Container(const Item &item)
{
	m_base = new Record(item);
	m_end = m_base;
}

template <class Item>
Container<Item>::Container(const Container &cont)
{
    if (*this != cont)
    {
		m_base = new Record((cont.m_base)->m_info, (cont.m_base)->m_prev, );
		m_prev = NULL;
		Record::DeepCopy(this, record.m_next);
    }
}

template <class Item>
Container<Item>::~Container()
{
    delete m_base;
    
    // Prevent the pointers from referencing to un-allocated memory
    m_base = NULL;
    m_end = NULL;
}

template <class Item>
bool Container<Item>::operator==(const Container &cont) const
{
    // deep check
}

template <class Item>
bool Container<Item>::operator!=(const Container &cont) const
{
    // deep check
}

template <class Item>
Container<Item>& Container<Item>::operator=(const Container &cont)
{
  // deep copy  
    
}

template <class Item>
Container<Item> Container<Item>::operator+(const Container &cont) const
{
  // union  
    
}

template <class Item>
Container<Item> Container<Item>::operator-(const Container &cont) const
{
    // split
}

template <class Item>
std::ostream& operator<<(std::ostream &os, const Container<Item> &cont)
{
    if (cont.m_base == NULL)
	return os << "<Empty container>\n";
    
    return os << *(cont.m_base);
}

template <class Item>
void Container<Item>::Insert(const Item &item)
{
    if (m_base == NULL)
    {
	    m_base = new Record(item, m_end);
	    m_end = m_base;
    }
    else
    {
	    m_end->m_next = new Record(item, m_end);
	    m_end = m_end->m_next;
    }
}

template <class Item>
typename Container<Item>::Iterator Container<Item>::Begin()
{
    return Iterator(m_base);
}

template <class Item>
typename Container<Item>::Iterator Container<Item>::End()
{
    if (m_end != NULL)
      return Iterator(m_end->m_next);
    
    return NULL;
}

template <class Item>
typename Container<Item>::Iterator Container<Item>::First()
{
    if (m_base != NULL)
      return Iterator(m_base->m_prev);
    
    return NULL;
}

template <class Item>
typename Container<Item>::Iterator Container<Item>::Last()
{
    return m_end;
}

template <class Item>
typename Container<Item>::Const_iterator Container<Item>::Begin() const
{
    return Const_iterator(m_base);
}

template <class Item>
typename Container<Item>::Const_iterator Container<Item>::End() const
{
    if (m_end != NULL)
      return Const_iterator(m_end->m_next);
    
    return NULL;
}

template <class Item>
typename Container<Item>::Const_iterator Container<Item>::First() const
{
    if (m_base != NULL)
      return Const_iterator(m_base->m_prev);
    
    return NULL;
}

template <class Item>
typename Container<Item>::Const_iterator Container<Item>::Last() const
{
    return m_end;
}

template <class Item>
bool Container<Item>::IsEmpty()
{
    return m_base == NULL;
}

template <class Item>
void Container<Item>::Clear()
{
    ~Container();
}

#include "Record.cpp"
