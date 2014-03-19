#ifndef ITEMPOINTER_H
#define ITEMPOINTER_H

#include "Match.h"
#include "BasketballMatch.h"
#include "FootballMatch.h"
#include "VolleyballMatch.h"
#include "TennisMatch.h"

class ItemPointer
{
private:
	Match *m_data;
	
public:
	ItemPointer(Match *mtc = NULL) { m_data = mtc; }
	
	bool StrictEqual(const ItemPointer &ptr) const
	{
		return m_data == ptr.m_data;
	}
	
	bool operator==(const ItemPointer &ptr) const
	{
		BasketballMatch *bptr = dynamic_cast<BasketballMatch*>(m_data);
		if (bptr != NULL)
			return bptr->operator==(*(ptr.m_data));
			
		FootballMatch *fptr = dynamic_cast<FootballMatch*>(m_data);
		if (fptr != NULL)
			return fptr->operator==(*(ptr.m_data));
		
		VolleyballMatch *vptr = dynamic_cast<VolleyballMatch*>(m_data);
		if (vptr != NULL)
			return vptr->operator==(*(ptr.m_data));
		
		TennisMatch *tptr = dynamic_cast<TennisMatch*>(m_data);
		if (tptr != NULL)
			return tptr->operator==(*(ptr.m_data));
		
		return m_data->operator==(*(ptr.m_data));
	}
	
	bool operator!=(const ItemPointer &ptr) const
	{
		BasketballMatch *bptr = dynamic_cast<BasketballMatch*>(m_data);
		if (bptr != NULL)
			return bptr->operator!=(*(ptr.m_data));
			
		FootballMatch *fptr = dynamic_cast<FootballMatch*>(m_data);
		if (fptr != NULL)
			return fptr->operator!=(*(ptr.m_data));
		
		VolleyballMatch *vptr = dynamic_cast<VolleyballMatch*>(m_data);
		if (vptr != NULL)
			return vptr->operator!=(*(ptr.m_data));
		
		TennisMatch *tptr = dynamic_cast<TennisMatch*>(m_data);
		if (tptr != NULL)
			return tptr->operator!=(*(ptr.m_data));
		
		return m_data->operator!=(*(ptr.m_data));
	}
	
	ItemPointer& operator=(const ItemPointer &ptr)
	{
		*m_data = *(ptr.m_data);
		return *this;
	}
	
	Match* operator*() const { return m_data; }
	
	friend std::ostream& operator<<(std::ostream &os, const ItemPointer &ptr)
	{
		BasketballMatch *bptr = dynamic_cast<BasketballMatch*>(ptr.m_data);
		if (bptr != NULL)
			return os << *bptr;
			
		FootballMatch *fptr = dynamic_cast<FootballMatch*>(ptr.m_data);
		if (fptr != NULL)
			return os << *fptr;
		
		VolleyballMatch *vptr = dynamic_cast<VolleyballMatch*>(ptr.m_data);
		if (vptr != NULL)
			return os << *vptr;
		
		TennisMatch *tptr = dynamic_cast<TennisMatch*>(ptr.m_data);
		if (tptr != NULL)
			return os << *tptr;
		
		return os << *(ptr.m_data);
	}
};

#endif
