//
//   Some of your code goes here.hpp
//  Homework-1
//
//  Created by Henry Macarthur on 1/17/19.
//  Copyright © 2019 Henry Macarthur. All rights reserved.
//

#ifndef SSN
#define SSN

#include <stdio.h>
#include "Set.h"

//using ItemType = unsigned long;
class SSNSet
{
public:
    SSNSet();          // Create an empty SSN set.
    
    bool add(ItemType ssn);
    // Add an SSN to the SSNSet.  Return true if and only if the SSN
    // was actually added.
    
    int size() const;  // Return the number of SSNs in the SSNSet.
    
    void print() const;
    // Write every SSN in the SSNSet to cout exactly once, one per
    // line.  Write no other text.
    
private:
    // Some of your code goes here.
    //long m_SSNList[DEFAULT_MAX_ITEMS];
    //int m_length = 0;
    Set s;
    
};

#endif /* _Some_of_your_code_goes_here_hpp */
