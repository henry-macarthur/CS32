//
//  newSet.cpp
//  Homework-1
//
//  Created by Henry Macarthur on 1/18/19.
//  Copyright © 2019 Henry Macarthur. All rights reserved.
//
#include <iostream>
#include "newSet.h"
//const int DEFAULT_MAX_ITEMS = 250;
Set::Set(int numItems)
{
    if(numItems == 0)
    {
        m_maxLength = DEFAULT_MAX_ITEMS;
    } else
    {
        m_maxLength = numItems;
    }
    m_length = 0;
    m_stringList = new ItemType[DEFAULT_MAX_ITEMS];
}
Set::~Set()
{
    
    delete [] m_stringList;
}
Set::Set(const Set& other)
{
    //delete m_stringList;
    m_length = other.m_length;
    m_stringList = new ItemType[DEFAULT_MAX_ITEMS];
    m_maxLength = other.m_maxLength;
    for(int i = 0; i < other.m_length; i++)
    {
        m_stringList[i] = other.m_stringList[i];
    }
}
Set& Set::operator=(const Set& rhs)
{
    if(this != &rhs)
    {
        Set temp(rhs);
        this->swap(temp);
    }
    
    return *this;
}

bool Set::empty() const
{
    return m_length == 0; //if the length is 0, then the list is empty
}

int Set::size() const
{
    return m_length;
}

bool Set::insert(const ItemType& value)
{
    if(m_length < DEFAULT_MAX_ITEMS && m_length < m_maxLength) //make sure that the length is greater than the array length
    {
        for(int i = 0; i < m_length; i++) //loop through initialized elements only
        {
            if(m_stringList[i] == value)
                return false; //return false if the value is inside of the list
        }
        
        m_stringList[m_length] = value; //set the next free item equal to the desired value
        m_length++; //increment array length
        
        return true;
    }
    
    return false;
    
}
//

bool Set::erase(const ItemType& value)
{
    bool contains = false;
    int index = 0;
    
    for(int i = 0; i < m_length; i++)
    {
        if(m_stringList[i] == value)
        {
            contains = true; //set contains equal to true if we find the desired item
            index = i; //set the index to current index of the loop
        }
        
        //do not have to worry about duplicated because the insert function guaruntees that we only have one of each element
    }
    
    if(contains)
    {
        //m_stringList[index] = m_stringList[m_length-1];
        
        for(int i = index; i < m_length - 1; i++)
        {
            m_stringList[i] = m_stringList[i+1]; //shift all items after the item we want to erase back one space
        }
        
        m_length--; //decrease length
        return true;
    }
    
    return false;
}

bool Set::contains(const ItemType& value) const
{
    for(int i = 0; i < m_length; i++)
    {
        if(m_stringList[i] == value) //return true as soon as we find the value
            return true;
    }
    
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    for(int j = 0; j < m_length; j++)
    {
        int count = 0;
        
        for(int k = 0; k < m_length; k++)
        {
            if( j!= k && m_stringList[j] > m_stringList[k])
            {
                count++; //if the current item is greater than any other item in the list, increase count
            }
        }
        
        if(count == i) //count must equal i because we are dealing with strictly greater than
        {
            value = m_stringList[j];
            return true;
        }
        
    }
    return false;
}

void Set::swap(Set& other)
{
    //exchange the contents of passed in list with the current list
    //they have the same max value so I do not have to worry about going out of bounds
    
    
    int tempLength = other.m_length;
    other.m_length = m_length;
    m_length = tempLength;
    
    int tempMaxLength = other.m_maxLength;
    other.m_maxLength = m_maxLength;
    m_maxLength = tempMaxLength;
    
    ItemType* tempPointer = m_stringList;
    m_stringList = other.m_stringList;
    other.m_stringList = tempPointer;
    
    
}

