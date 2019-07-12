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
    Node* m_dummy = new Node; //create a dummy node so we never have to deal with empty list issues
    m_length = 0;
    m_dummy->m_next = m_dummy; //make the dummy node point to itself to maintain circular structure
    m_dummy->m_prev = m_dummy;
    m_head = m_dummy; //have the head point to the dummy node
}
Set::Set(const Set& other)
{
    Node* m_dummy = new Node; //since nothing has been constructed, i have to initialize a dummy node
    m_head = m_dummy;
    m_length = 0;
    if(other.m_length == 0) //if the length is 0, just make the dummy node point to this element
    {
        m_head->m_next = m_head;
        m_head->m_prev = m_head;
    }
    else
    {
        Node* otherNode = other.m_head->m_next; //start at the other sets first element
        for(int i = 0; i < other.m_length; i++) //loop through other linked list
        {
            insert(otherNode->m_item); //insert each item of the other list
            otherNode = otherNode->m_next; //increment the pointer of the other list
        }
    }
}
Set& Set::operator=(const Set& rhs)
{
    if(this != &rhs) //check for aliasing
    {
        Set temp(rhs); //create a copy of the rhs set
        swap(temp); //swap the copy with the current set values
    }
    
    return *this;
}

Set::~Set()
{
    Node* p = m_head;//->m_next;
    
    for(;p->m_next != m_head; ) //loop until i get to the last pointer
    {
        Node* nextNode = p->m_next;
        delete p; //delete each node
        p = nextNode;
    }
    delete p; //this deletes the dummy node
    
}

bool Set::empty() const
{
    return m_length == 0; //trivial
}

int Set::size() const
{
    return m_length; //trivial
}

bool Set::insert(const ItemType& value) //insert each item in order!
{
    
    if(m_length == 0)
    { //if the length is 0, just have the dummy point to this, and this node points to the dummy
        Node* temp = new Node;
        temp->m_item = value;
        temp->m_next = m_head;
        temp->m_prev = m_head;
        
        m_head->m_next = temp;
        m_head->m_prev = temp;
        
        m_length++;
        return true;
        
    } else {
        if(contains(value))
        {
            return false; //dont wanna add an item if the list already contains it
        }
        Node* temp = new Node; //create a new node
        if(value > m_head->m_prev->m_item) //if the element is greater than the last element
        {
            temp->m_item = value;
            temp->m_next = m_head; //have the node point to the head
            temp->m_prev = m_head->m_prev; //have the prev pointer of the node point to the last element of the list
            
            m_head->m_prev->m_next = temp; ///make the last element in the list point to the new node
            m_head->m_prev = temp; //set the dummy's previous pointer point to the newly added node
        }
        else
        {
            Node *p = m_head->m_next;
            for(; p->m_item < value; p = p->m_next)
            {} //loop through the array until we find the first value that is greater than the value passed in
            temp->m_item = value; //set the nodes value
            temp->m_next = p; //have the node point to the value that is greater than it
            temp->m_prev = p->m_prev; //have the node point to the value directly less than it
            
            p->m_prev->m_next = temp; //initialize the other node's pointers so that they point to the new node
            p->m_prev = temp;
            
        }
        
        m_length++; //keep track of current length
        return true;
    }
    return false;
}

bool Set::contains(const ItemType& value) const
{
    Node* p = m_head->m_next; //start at the dummy node
    for(int i = 0; i < m_length; i++) //loop through each element in the list
    {
        if(p->m_item == value)
        {
            return true; //if we find the value, we can return right away
        }
        p = p->m_next;
    }
    
    return false; //returns false if there are no values equal to it in the array
}

bool Set::erase(const ItemType& value)
{
    if(contains(value)) //only want to look if the list actuallty contains the desired value
    {
        for(Node* p = m_head->m_next;;p = p->m_next)//this won't result in an infinite loop because we now know the item exists in the array
        {
            if(p->m_item == value) //found our item
            {
                p->m_prev->m_next = p->m_next; //the node after the one we are removing should now point the the node previous to it
                p->m_next->m_prev = p->m_prev; //the node previous to the one we are removing should point to the one after it
                m_length--;
                
                delete p; //must deallocate the node because it was created with the new operator
                return true;
            }
        }
    }
    
    return false; //return false if the element is not in the list
}

bool Set::get(int pos, ItemType& value) const
{
    if(pos >= 0 && pos < m_length) //make sure the pos is not out of bounds
    {
        Node* p = m_head->m_next;
        for(int i = 0; i < pos; i++) //loop through the list until we get to the desired pos, the list is in order so I don't have to do any special checking
        {
            p = p->m_next; //increment the pointer
        }
        
        value = p->m_item; //we are now at the node we want to access
        return true;
    }
    else
    {
        return false; //return false if the element does not exist in the list
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
    int tempLength = m_length; //make a temp val for the current length
    m_length = other.m_length; //set the length = to the other length
    other.m_length = tempLength; //set the other length equal to the original length
    Node* temp = m_head; //create a temporary pointer of the current head
    m_head = other.m_head;//swap the current head with the other head
    other.m_head = temp;
}

void unite(const Set& s1, const Set& s2, Set& result)
{
    Set temp(s1); //make a copy of s1
    for(int i = 0; i < s2.size(); i++) //loop through every element of s2
    {
        ItemType value;
        s2.get(i, value);
        temp.insert(value); //if the current item of the s2 list isnt in the s1 list, add it
    }
    
    result = temp; //now assign all the elements of the new set we created to result
                    //this takes care of the fact that result might not be empty
}

void subtract(const Set& s1, const Set& s2, Set& result)
{
    Set temp(s1); //create a copy of s1
    for(int i = 0; i < s2.size(); i++) //loop through s2
    {
        ItemType value;
        s2.get(i, value); //get each value of s2
        if(temp.contains(value)) //if s1 list contains the current value of s2
        {
            temp.erase(value); //remove that element from the temp set
        } else {
            temp.insert(value); //if it is not, that means the element is unique so we should add it
        }
    }

    result = temp; //assign result to the temp Set, this gets rid of the possibility that result might not be empty
}
