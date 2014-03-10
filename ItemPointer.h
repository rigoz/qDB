#ifndef ITEMPOINTER_H
#define ITEMPOINTER_H

class ItemPointer
{
private:
	Match *m_data;
	
public:
	ItemPointer() { m_data = NULL; }
	ItemPointer(AgrarianProduct *prod) { m_data = prod; }
	ItemPointer(const ItemPointer &ptr) { m_data = new AgrarianProduct(ptr.m_data); }
	~ItemPointer() { delete m_data; }
	
	bool operator==(const ItemPointer &ptr) const { return m_data == ptr.m_data; }
	bool operator!=(const ItemPointer &ptr) const { return m_data != ptr.m_data; }
};

#endif
