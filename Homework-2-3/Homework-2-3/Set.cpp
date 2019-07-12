#include "Set.h"

Set::Set()
{
    createEmpty();
}

bool Set::insert(const ItemType& value)
{
    // Fail if value already present
    
    Node* p = findFirstAtLeast(value);
    if (p != m_head  &&  p->m_value == value)
        return false;
    
    // Insert new Node preserving ascending order and incrementing m_size
    
    insertBefore(p, value);
    return true;
}

bool Set::erase(const ItemType& value)
{
    // Find the Node with the value, failing if there is none.
    
    Node* p = findFirstAtLeast(value);
    if (p == m_head  ||  p->m_value != value)
        return false;
    
    // Erase the Node, decrementing m_size
    doErase(p);
    return true;
}

bool Set::get(int i, ItemType& value) const
{
    if (i < 0  ||  i >= m_size)
        return false;
    
    
    Node* p;
    if (i < m_size / 2)  // closer to head
    {
        p = m_head->m_next;
        for (int k = 0; k != i; k++)
            p = p->m_next;
    }
    else  // closer to tail
    {
        p = m_head->m_prev;
        for (int k = m_size-1; k != i; k--)
            p = p->m_prev;
    }
    
    value = p->m_value;
    return true;
}

void Set::swap(Set& other)
{
    // Swap head pointers
    
    Node* p = other.m_head;
    other.m_head = m_head;
    m_head = p;
    
    int s = other.m_size;
    other.m_size = m_size;
    m_size = s;
}

Set::~Set()
{
    while (m_head->m_next != m_head)
        doErase(m_head->m_next);
    
    
    delete m_head;
}

Set::Set(const Set& other)
{
    createEmpty();
    
    for (Node* p = other.m_head->m_next; p != other.m_head; p = p->m_next)
        insertBefore(m_head, p->m_value);
}

Set& Set::operator=(const Set& rhs)
{
    if (this != &rhs)
    {
        
        Set temp(rhs);
        swap(temp);
    }
    return *this;
}

void Set::createEmpty()
{
    m_size = 0;
    m_head = new Node;
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
}

void Set::insertBefore(Node* p, const ItemType& value)
{
    Node* newp = new Node;
    newp->m_value = value;
    
   
    newp->m_prev = p->m_prev;
    newp->m_next = p;
    newp->m_prev->m_next = newp;
    newp->m_next->m_prev = newp;
    
    m_size++;
}

void Set::doErase(Node* p)
{
    p->m_prev->m_next = p->m_next;
    p->m_next->m_prev = p->m_prev;
    delete p;
    
    m_size--;
}

Set::Node* Set::findFirstAtLeast(const ItemType& value) const
{
    
    Node* p = m_head->m_next;
    for ( ; p != m_head  &&  p->m_value < value; p = p->m_next)
        ;
    return p;
}

void unite(const Set& s1, const Set& s2, Set& result)
{
    
    const Set* sp = &s2;
    if (&result == &s1)
    {
        if (&result == &s2)
            return;
    }
    else if (&result == &s2)
        sp = &s1;
    else
    {
        result = s1;
        if (&s1 == &s2)
            return;
    }
    for (int k = 0; k < sp->size(); k++)
    {
        ItemType v;
        sp->get(k, v);
        result.insert(v);
    }
}

void subtract(const Set& s1, const Set& s2, Set& result)
{
    
    Set s2copy(s2);
    result = s1;
    for (int k = 0; k < s2copy.size(); k++)
    {
        ItemType v;
        s2copy.get(k, v);
        result.erase(v);
    }
}
