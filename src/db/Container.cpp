template <class Item>
Container<Item>::Container()
{
	SetEmpty();
}

template <class Item>
Container<Item>::Container(const Item &item)
{
	m_base = new Record(item);
	m_end = m_base;
	m_size = 1;
}

template <class Item>
Container<Item>::Container(const Container &cont)
{
	if (this != &cont)
	{
		if (cont.IsEmpty() == false) // "cont" has elements to copy
		{
			m_base = new Record(*(cont.m_base)); // Call to Record copy constructor for a deep copy
			m_size = cont.m_size;
		
			if (m_size == 1)
				m_end = m_base;
			else
				SetEnd(m_base); // Find the new end of the list
		}
		else // "cont" is empty
			SetEmpty();
	}
}

template <class Item>
void Container<Item>::SetEnd(Record *record)
{   
	if (record == NULL || record->m_next == NULL)
		m_end = record;
	else
		SetEnd(record->m_next);
}

template <class Item>
Container<Item>::~Container()
{
	delete m_base;
	
	// Prevent pointers from referencing to un-allocated memory
	m_base = NULL;
	m_end = NULL;
	m_size = 0;
}

template <class Item>
bool Container<Item>::operator==(const Container &cont) const
{
	if (IsEmpty() && cont.IsEmpty()) // both containers are empty
		return true;
		
	if (Size() != cont.Size()) // if they have a different amount of elements, they cant be equal
		return false;
	
	for (Const_iterator i = Begin(); i != End(); ++i)
		if (cont.Find((*i)->GetInfo()) == NULL)
			return false; // exit as soon as i cant find an item from the caller object in "cont"
		
	return true;
}

template <class Item>
bool Container<Item>::operator!=(const Container &cont) const
{
	return (*this == cont) == false;
}

template <class Item>
Container<Item>& Container<Item>::operator=(Container<Item> cont)
{
	Swap(*this, cont); // swap list pointers

	// we dont need to delete our old data since it now
	// belongs to "cont", which is a local copy and will
	// be destroyed after the return statement
	return *this;
}

// Concatenates two Containers into a new one
template <class Item>
Container<Item> Container<Item>::operator+(Container cont) const
{
	for(Const_iterator i = Begin(); i != End(); ++i) 
		cont.Insert((*i)->GetInfo());
	
	return cont;
}

// Returns a new object removing all items inside "cont" from the caller object.
// In case of multiple occurencies of the same item, only the first will be removed
template <class Item>
Container<Item> Container<Item>::operator-(const Container &cont) const
{
	Container<Item> res;

	if (this->IsEmpty()) // caller object is empty, return an empty object
		return res;

	if (cont.IsEmpty()) // A - 0 = A
		return *this;

	res = *this;
	for(Const_iterator i = cont.Begin(); i != cont.End(); ++i)
		res.Remove((*i)->GetInfo());

	return res;
}

template <class Item>
std::ostream& operator<<(std::ostream &os, const Container<Item> &cont)
{
	os << "<qDB>\n";
	if (cont.IsEmpty() == false)
	os << *(cont.m_base); // call op<< overloaded on Record object
	os << "\t<size>" << cont.Size() << "</size>\n";
	os << "</qDB>\n";
}

// Inserts a new record to the back of the list
template <class Item>
void Container<Item>::Insert(const Item &item)
{
	if (m_base == NULL && m_end == NULL) // empty list, push on front...
	{
		m_base = new Record(item, m_end);
		m_end = m_base;
	}
	else // ...otherwise, push on back
	{
		m_end->m_next = new Record(item, m_end);
		m_end = m_end->m_next;
	}
	
	m_size++;
}

// Removes a record from the list
template <class Item>
void Container<Item>::Remove(Record *record)
{
	if (record == NULL || IsEmpty()) // Nothing to do
		return;
		
	if (Size() == 1 && record == m_base) // We are removing the only Record in our list
	{
		Clear();
		return;
	}
	
	if (record == m_base || record == m_end) // Removing the start or the end of the list with size > 1
	{
		RemoveBoundaries(record);
		return;
	}
	
	// General scenario, removing an element in the middle of the list ( size > 2 )
	
	// Save links to other elements
	Record *prev = record->m_prev;
	Record *next = record->m_next;
	
	ASSERT_PTR(prev != NULL);
	prev->m_next = next;
		
	ASSERT_PTR(next != NULL);
	next->m_prev = prev;
	
	record->m_next = NULL; // avoid cascade deletion
	
	delete record;
	
	m_size--;
}

// Removes all the occurrences of "item" from the list
template <class Item>
void Container<Item>::RemoveAll(const Item &item)
{
	if (IsEmpty())
		return;
   
	for(Iterator i = Begin(); i != End();)
		if ((*i)->GetInfo() == item)
		{
			Iterator next((*i)->m_next); // Save next pointer
			Remove(*i);
			
			i = next; // move iterator to the next element
		}
		else
			++i;
}

// Returns a new container with all occurencies found
template <class Item>
Container<Item> Container<Item>::Find(const Item &item)
{
	Container<Item> c;
	if (IsEmpty())
		return c;
		
	for (Iterator i = Begin(); i != End(); ++i)
		if ((*i)->GetInfo() == item)
			c.Insert((*i)->GetInfo());
	
	return c;
}

template <class Item>
const Container<Item> Container<Item>::Find(const Item &item) const
{
	Container<Item> c;
	if (IsEmpty())
		return c;
		
	for (Const_iterator i = Begin(); i != End(); ++i)
		if ((*i)->GetInfo() == item)
			c.Insert((*i)->GetInfo());
	
	return c;
}

// Updates a Record with a new Item
template <class Item>
void Container<Item>::Update(Record *record, const Item &item)
{
	if (record != NULL)
		record->m_info = item;
}

// Returns a record using the strict equality on item members
template <class Item>
typename Container<Item>::Record* Container<Item>::GetRecord(const Item &item)
{
	if (IsEmpty())
		return NULL;
		
	for (Iterator i = Begin(); i != End(); ++i)
		if ((*i)->GetInfo().StrictEqual(&item))
			return *i;
	
	return NULL;
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
bool Container<Item>::IsEmpty() const
{
	return m_size == 0;
}

template <class Item>
void Container<Item>::Clear()
{
	delete m_base; // cascade deletion on Records
	
	SetEmpty(); // reset pointers and size
}

template <class Item>
unsigned int Container<Item>::Size() const
{
	return m_size;
}

template <class Item>
void Container<Item>::SetEmpty()
{
	m_base = NULL;
	m_end = NULL;
	m_size = 0;
}

template <class Item>
void Container<Item>::RemoveBoundaries(Record *limit)
{
	if (limit == m_base)
	{
		m_base = limit->m_next;
		ASSERT_PTR(m_base != NULL);
		m_base->m_prev = NULL;
	}
	else
	{
		m_end = limit->m_prev;
		ASSERT_PTR(m_end != NULL);
		m_end->m_next = NULL;
	}
		
	limit->m_next = NULL; // avoid cascade deletion
	delete limit;
		
	m_size--;
}

template <class Item>
void Container<Item>::Swap(Container &c1, Container &c2)
{
	// Not worth to create a copy of one of the containers
	// since we just need to swap pointers

	// Save list boundaries
	Record *c1base = c1.m_base;
	Record *c1end = c1.m_end;
	unsigned int c1size = c1.m_size;
	
	Record *c2base = c2.m_base;
	Record *c2end = c2.m_end;
	unsigned int c2size = c2.m_size;
	
	// Swap
	c1.m_base = c2base;
	c1.m_end = c2end;
	c1.m_size = c2size;
	
	c2.m_base = c1base;
	c2.m_end = c1end;
	c2.m_size = c1size;
}

template <class Item>
void Container<Item>::Swap(Record &r1, Record &r2)
{
	// Save list information
	Record *r1prev = r1.m_prev;
	Record *r1next = r1.m_next;
	Item r1info = r1.m_info;
	
	Record *r2prev = r2.m_prev;
	Record *r2next = r2.m_next;
	Item r2info = r2.m_info;
	
	// Swap
	r1.m_prev = r2prev;
	r1.m_next = r2next;
	r1.m_info = r2info;
	
	r2.m_prev = r1prev;
	r2.m_next = r1next;
	r2.m_info = r1info;
}

template <class Item>
void Container<Item>::Save() const
{
	std::ofstream output;
	output.open ("qDB.xml");
	output << *this;
	output.close();
}