//
//   Some of your code goes here.cpp
//  Homework-1
//
//  Created by Henry Macarthur on 1/17/19.
//  Copyright © 2019 Henry Macarthur. All rights reserved.
//

#include "SSNSet.h"
#include <iostream>

SSNSet::SSNSet()
{
    
    //SSNlist
}

int SSNSet::size() const
{
    return s.size();
}

void SSNSet::print() const
{
    for(int i = 0; i < size(); i++)
    {
        ItemType currentVal;
        s.get(i, currentVal);
        std::cout << currentVal << std::endl;
    }
}

bool SSNSet::add(ItemType ssn)
{
    return s.insert(ssn);
}
