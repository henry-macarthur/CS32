//
//  main.cpp
//  Project-2
//
//  Created by Henry Macarthur on 1/23/19.
//  Copyright © 2019 Henry Macarthur. All rights reserved.
//
#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
//    Set s1;
//    assert(s1.insert("animal"));
//    assert(s1.insert("boo!"));
//    assert(s1.insert("cat"));;
//    assert(s1.insert("dog"));
//    assert(s1.insert("e"));
//    assert(s1.erase("animal"));
//    assert(s1.insert("animal"));
//    assert(!s1.insert("animal"));
//    assert(!s1.insert("dog"));
//
//    string temp;
//    assert(s1.get(0, temp) && temp == "animal");
//    assert(s1.get(4, temp) && temp == "e");
//    assert(!s1.get(-1, temp));
//    assert(!s1.get(6, temp));
//    assert(temp == "e");
//
//    assert(s1.insert("fan"));
//    assert(s1.contains("fan"));
//    assert(s1.erase("boo!") && !s1.contains("boo!"));
//
//    Set s2;
//    assert(s2.empty() && s2.size() == 0);
//    s2.insert("item1");
//    assert(s2.size() == 1);
//    s2.insert("item2");
//
//    Set s3(s1);
//    assert(s3.size() == 5);
//    s3.insert("zzz");
//    assert(!s1.contains("zzz"));
//    s1.insert("xxx");
//    assert(!s3.contains("xxx"));
//
//    Set s4;
//    s4.insert("something1");
//    s4.insert("something2");
//
//    s4 = s1;
//
//    for(int i = 0; i < s4.size(); i++)
//    {
//        string a, b;
//        s4.get(i, a);
//        s1.get(i, b);
//        assert(a == b);
//    }
//
//    s4 = s2;
//    assert(s4.insert("new Item 3"));
//    assert(!s2.contains("new Item 3"));
//    s4.dump();
//    string f;
//    s4.get(2, f);
//    //assert( f == "new Item 3");
//    //s4.dump();
//    Set s5;
//    s5 = s1;
//    assert(s5.size() == s1.size());
//
//    Set n;
//    n.insert("a");
//    n.insert("b");
//
//    Set b;
//    b.insert("1");
//    b.insert("2");
//
//    n.swap(b);
//    n.dump();
//    b.dump();
//
//
//    Set s6;
//    s6.insert("item1");
//    s6.insert("item3");
//    s6.insert("item4");
//
//    Set s7;
//    s7.insert("item2");
//    s7.insert("item4");
//
//    Set s8;
//    s8.insert("a");
//    s8.insert("b");
//
//    unite(s6, s7, s6);
//
//    assert(s6.size() == 4);
//    //s6.dump();
//
//    subtract(s6, s7, s8);
//    assert(s8.size() == 2);
//
    Set a;
    Set b;
    a.insert("a");
    a.insert("b");
    a.insert("c");
    b.insert("1");
    b.insert("2");
    
    a.swap(b);
    
    //a.dump();
    //b.dump();
    assert(a.size() == 2 && b.size() == 3);
    
    Set c;
    c.insert("11");
    c.insert("22");
    
    Set d;
    d.insert("aa");
    d.insert("bb");
    d.insert("dd");
    
    Set f(d);
    
    f.insert("cc");
    //f.dump();
    
    Set g = f;
    g.insert("b");
    //g.dump();
    
    Set h;
    h.insert("Some item");
    
    h = g;
    h.insert("ee");
    h.dump();
    cerr << "FINISHED!!!" << endl;
    return 0;
}

