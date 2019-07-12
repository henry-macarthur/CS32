//
//  Set.cpp
//  Project-2
//
//  Created by Henry Macarthur on 1/23/19.
//  Copyright © 2019 Henry Macarthur. All rights reserved.
//

#include "Set.h"

Set::Set()
{
    m_dummy = new Node;
    m_length = 0;
    m_dummy->m_next = m_dummy; //ask about this, make it point to itself
    m_dummy->m_prev = m_dummy; //ask about this, make it point to itself
    m_head = m_dummy;
}
Set::Set(const Set& other)
{
    m_dummy = new Node;
    //m_length = other.m_length;
    m_head = m_dummy;
    m_length = 0;
    if(other.m_length == 0)
    {
        m_dummy->m_next = m_dummy;
        m_dummy->m_prev = m_dummy;
    }
    else
    {
        Node* otherNode = other.m_head->m_next;
        for(int i = 0; i < other.m_length; i++)
        {
            insert(otherNode->m_item);
            otherNode = otherNode->m_next;
        }
        
        
    }
   
}
Set& Set::operator=(const Set& rhs)
{
    //start at the end of the linked list: m_dummy->m_prev
    //if current length > rhs.length, then delete nodes till they are the same length
    //else, just keep adding nodes and replace the values within the current nodes
    if(m_length < rhs.m_length)
    {
        Node* temp = m_head->m_next;//->m_next;
        Node* rhsTemp = rhs.m_head->m_next;//->m_next;

        for(int i = 0; i < m_length; i++)
        {
            temp->m_item = rhsTemp->m_item;
            //std::cerr << temp-
            temp = temp->m_next;
            rhsTemp = rhsTemp->m_next;
        }

        temp = m_head->m_prev;
        //rhsTemp = rhs.m_head->m_next->m_nex;
        //now start at the end and add elements, also have to change the pointers
        int startL = m_length;
        for(int i = 0; i < (rhs.m_length - startL); i++)
        {
            Node* newN = new Node;
            newN->m_item = rhsTemp->m_item;
            newN->m_prev = m_head->m_prev;
            newN->m_next = m_head;
            m_head->m_prev->m_next = newN;
            m_head->m_prev = newN;
            rhsTemp = rhsTemp->m_next;

            m_length++;
        }
    }
    else
    {
        int itemsToDelete = m_length - rhs.m_length;

        Node* p = m_head->m_prev;
        for(int i = 0; i < itemsToDelete; i++)
        {
            Node* nextNode = p->m_prev;
            delete p;

            p = nextNode;
        }
        p->m_next = m_head;
        m_dummy->m_prev = p;
        //std::cerr << m_dummy->m_prev->m_item << std::endl;
        m_length = rhs.m_length;


        Node* rhsTemp = rhs.m_head->m_next;
        p = m_head->m_next;
        for(int i = 0; i < rhs.m_length; i++)
        {
            p->m_item = rhsTemp->m_item;
            rhsTemp = rhsTemp->m_next;
            p = p->m_next;
            m_length++;
        }
        m_length = rhs.m_length;
    }
    //Set temp(rhs);
    //swap(temp);
    
    return *this;
}

Set::~Set()
{
    Node* p = m_head;//->m_next;
    
    for(;p->m_next != m_head; )
    {
        Node* nextNode = p->m_next;
        delete p;
        p = nextNode;
    }
    delete p;
    
}

bool Set::empty() const
{
    return m_length == 0;
}

int Set::size() const
{
    return m_length;
}

bool Set::insert(const ItemType& value)
{
    
    if(m_length == 0)
    {
        Node* temp = new Node;
        temp->m_item = value;
        temp->m_next = m_dummy;
        temp->m_prev = m_dummy;
        
        m_dummy->m_next = temp;
        m_dummy->m_prev = temp;
        
        m_length++;
        return true;
        
    } else {
        if(contains(value))
        {
            return false;
        }
       Node* temp = new Node;
        if(value > m_dummy->m_prev->m_item)
        {
            temp->m_item = value;
            temp->m_next = m_dummy;
            temp->m_prev = m_dummy->m_prev;

            m_dummy->m_prev->m_next = temp;
            m_dummy->m_prev = temp;
        }
        else
        {
            Node *p = m_dummy->m_next;
            for(; p->m_item < value; p = p->m_next)
            {}
            temp->m_item = value;
            temp->m_next = p;
            temp->m_prev = p->m_prev;
            
            p->m_prev->m_next = temp;
            p->m_prev = temp;
  
        }
        
        m_length++;
        return true;
    }
    return false;
}

bool Set::contains(const ItemType& value) const
{
    Node* p = m_dummy->m_next;
    for(int i = 0; i < m_length; i++)
    {
        if(p->m_item == value)
        {
            return true;
        }
        p = p->m_next;
    }
    
    return false;
}

bool Set::erase(const ItemType& value)
{
    if(contains(value))
    {
        for(Node* p = m_dummy->m_next;;p = p->m_next)
        {
            if(p->m_item == value)
            {
                p->m_prev->m_next = p->m_next;
                p->m_next->m_prev = p->m_prev;
                m_length--;
                
                delete p;
                return true;
            }
        }
    }
    
    return false;
}

bool Set::get(int pos, ItemType& value) const
{
    if(pos >= 0 && pos < m_length)
    {
        Node* p = m_head->m_next;
        for(int i = 0; i < pos; i++)
        {
            p = p->m_next;
        }
        
        value = p->m_item;
        return true;
    }
    else
    {
        return false;
    }
}
void Set::dump() const
{
    Node* p = m_head->m_next;
    for(;p != m_head;){//int i = 0; i < m_length; i++){
        std::cerr << p->m_item << std::endl;
        p = p -> m_next;
    }
    
}

void Set::swap(Set& other)
{
    //also need to swap the length values!
    int tempLength = m_length;
    m_length = other.m_length;
    other.m_length = tempLength;
    //swap the head nodes and this should work
    //swapping one set of pointers is constant, does not depend on n items
    Node* temp = m_head;
    m_head = other.m_head;
    other.m_head = temp;
    
    
    
}

void unite(const Set& s1, const Set& s2, Set& result)
{

    int length1 = s1.size();
    for(int i = 0; i < length1; i++) //the list should have nothing but the dummy node
    {
        ItemType value;
        s1.get(i, value); //get the current value from s1
        result.insert(value); //insert it into the result linked list
    }
    
    int length2 = s2.size();
    for(int i = 0; i < length2; i++)
    {
        ItemType value;
        s2.get(i, value); //get the current value from s2
        result.insert(value); //insert it into the result linked list
    }
    
    //int length3 = result.size();
    
    for(int i = 0; i < result.size(); i++)
    {
        ItemType value;
        result.get(i, value);
        if(!s1.contains(value) && !s2.contains(value))
        {
            result.erase(value);
            i--;
        }
    }
    
}

void subtract(const Set& s1, const Set& s2, Set& result)
{
  
    int length1 = s1.size();
    for(int i = 0; i < length1; i++) //the list should have nothing but the dummy node
    {
        ItemType value;
        s1.get(i, value); //get the current value from s1
        if(!s2.contains(value) && !result.contains(value))
        {
            result.insert(value); //insert it into the result linked list
        }
    }
    
    int length2 = s2.size();
    for(int i = 0; i < length2; i++)
    {
        ItemType value;
        s2.get(i, value); //get the current value from s2
        if(!s1.contains(value) && !result.contains(value))
            result.insert(value); //insert it into the result linked list
    }
    
    for(int i = 0; i < result.size(); i++)
    {
        ItemType value;
        result.get(i, value);
        if(!s1.contains(value) && !s2.contains(value))
        {
            result.erase(value);
            i--;
        }
    }
    
    
}
