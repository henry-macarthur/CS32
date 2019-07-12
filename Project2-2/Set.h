//
//  Set.hpp
//  Project-2
//
//  Created by Henry Macarthur on 1/23/19.
//  Copyright © 2019 Henry Macarthur. All rights reserved.
//

#ifndef Set_hp
#define Set_hp

#include <stdio.h>
#include <string>
#include <iostream>

using ItemType = int;//std::string;

class Set
{
public:
    Set();
    ~Set();
    Set(const Set& other);
    Set& operator=(const Set& rhs);
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
    
    void dump() const;
private:
    struct Node
    {
    public:
        ItemType m_item;
        Node* m_next;
        Node* m_prev;
    };
    Node* m_head;
    //Node* m_dummy;
    int m_length;
    
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);



#endif /* Set_hpp */
