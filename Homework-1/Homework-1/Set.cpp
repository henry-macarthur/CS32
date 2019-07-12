//
//  Set.cpp
//  Homework-1
//
//  Created by Henry Macarthur on 1/16/19.
//  Copyright © 2019 Henry Macarthur. All rights reserved.
//

#include "Set.h"

Set::Set()
{
    m_length = 0;
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
    if(m_length < DEFAULT_MAX_ITEMS) //make sure that the length is greater than the array length
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
    int length;
    if(m_length > other.m_length)
        length = m_length;
    else
        length = other.m_length;

    for(int i = 0; i < length; i++) {
        ItemType temp = m_stringList[i];
        m_stringList[i] = other.m_stringList[i];
        other.m_stringList[i] = temp;
    }

    int temp = m_length;
    m_length = other.m_length;
    other.m_length = temp;


}
