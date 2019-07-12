
#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>

// Later in the course, we'll see that templates provide a much nicer
// way of enabling us to have Sets of different types.  For now,
// we'll use a type alias.

using ItemType = char;

class Set
{
public:
    Set();               // Create an empty set (i.e., one with no items).
    bool empty() const;  // Return true if the set is empty, otherwise false.
    int size() const;    // Return the number of items in the set.
    
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int i, ItemType& value) const;
    void swap(Set& other);
    ~Set();
    Set(const Set& other);
    Set& operator=(const Set& rhs);
    
private:
    struct Node
    {
        ItemType m_value;
        Node*    m_next;
        Node*    m_prev;
    };
    
    Node* m_head;
    int   m_size;
    void createEmpty();
    void insertBefore(Node* p, const ItemType& value);
    void doErase(Node* p);
    Node* findFirstAtLeast(const ItemType& value) const;

};



void unite(const Set& s1, const Set& s2, Set& result);


void subtract(const Set& s1, const Set& s2, Set& result);


inline
int Set::size() const
{
    return m_size;
}

inline
bool Set::empty() const
{
    return size() == 0;
}

inline
bool Set::contains(const ItemType& value) const
{
    Node* p = findFirstAtLeast(value);
    return p != m_head  &&  p->m_value == value;
}

#endif // SET_INCLUDED
