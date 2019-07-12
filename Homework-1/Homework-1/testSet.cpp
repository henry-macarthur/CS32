
#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;


int main()
{
//    Set s;
//    assert(s.empty());
//    ItemType y = "arepa";
//    assert(!s.get(42, y) && y == "arepa"); // x unchanged by get failure
//    s.insert("chapati");
//    assert(s.size() == 1);
//    s.insert("arepa");
//    assert(s.size() == 2);
//    assert(!s.insert("arepa"));
//    assert(s.size() == 2);
//    assert(s.insert("aRepa"));
//    assert(s.size() == 3);
//    //s.dump();
//    s.insert("a");
//    s.insert("b");
//    assert(s.insert("c"));
//    assert(s.size() == 6);
//    assert(s.contains("chapati") && s.contains("arepa") && s.contains("aRepa"));
//    assert(s.erase("chapati"));
//    assert(s.size() == 5);
//    assert(s.contains("arepa") && s.contains("aRepa") && s.contains("a") && s.contains("b") && s.contains("b") && !s.contains("chapati"));
//    assert(!s.contains("bla"));
//    assert(!s.erase("asf"));
//    //s.dump();
//
//    // Empty String Test Cases
//    Set ss;
//    ss.insert("dosa");
//    assert(!ss.contains(""));
//    ss.insert("tortilla");
//    ss.insert("");
//    ss.insert("focaccia");
//    assert(ss.contains(""));
//    ss.erase("dosa");
//    assert(ss.size() == 3 && ss.contains("focaccia") && ss.contains("tortilla") &&
//           ss.contains(""));
//    //ss.dump();
//    string v;
//    assert(ss.get(2, v) && v == "tortilla");
//    assert(ss.get(1, v) && v == "focaccia");
//    assert(!ss.get(3, v) && v == "focaccia");
//    assert(!ss.get(4, v) && v == "focaccia");
//    assert(ss.get(0, v) && v == "");
//
//    // Swap, Copy Constructor, and Assignment Operator Test Cases
//    Set ss1;
//    ss1.insert("laobing");
//    Set ss2;
//    ss2.insert("matzo");
//    ss2.insert("pita");
//    ss1.swap(ss2);
//    assert(ss1.size() == 2 && ss1.contains("matzo") && ss1.contains("pita") &&
//           ss2.size() == 1 && ss2.contains("laobing"));
//    ss1.insert("piazza");
//    ss2.swap(ss1);
//    //ss1.dump();
//    //ss2.dump();
//    Set new1 = ss2;
//    Set new2(ss2);
//    Set new3;
//    new3 = ss2;
//    new3 = new3;
//    //new1.dump();
//    //new2.dump();
//    //new3.dump();
//    assert(ss2.erase("matzo"));
//    assert(ss2.erase("piazza"));
//    assert(ss2.erase("pita"));
//    assert(!ss2.erase(""));
//    //ss2.dump();
//
//    cerr << "Passed all tests" << endl;
////    Set s;
////    assert(s.empty());
////    ItemType x = 9876543;
////    assert( !s.get(42, x)  &&  x == 9876543);  //x unchanged by get failure
////    s.insert(123456789);
////    assert(s.size() == 1);
////    assert(s.get(0, x)  &&  x == 123456789);
////    s.insert(123);
////    assert(s.get(0, x) && x == 123);
////
////    s.erase(123456789);
////    assert(s.size() == 1);
////
////    s.insert(1);
////    s.insert(12);
////    s.insert(1234);
////
////    Set s2;
////    s2.insert(345);
////    s2.insert(3456);
////
////    s.swap(s2);
////
////    assert(s.size() == 2 && s2.size() == 4);
////
////    Set s3;
////
////    s3.swap(s);
////
////    ItemType xx;
////    ItemType yy;
////    assert(s.size() == 0 && s3.size() == 2);
////    s3.get(0, xx);
////    //cout << xx << endl;
////    assert(s3.get(0, xx) && xx == 345 && s3.get(1, yy)&& yy == 3456);
////    assert(!s2.insert(1) && !s2.insert(12));
////
////    Set s4;
////    s4.insert((1));
////    s4.insert(2);
////    assert(!s4.insert(2));
////    assert(!s4.insert(1));
////    assert(s4.erase(1));
////    assert(s4.insert(1));
////    s4.insert(2);
////    s4.insert(3);
////    s4.insert(5);
////    s4.insert(4);
////
////    Set s6;
////    s6.insert(7);
////    s6.insert(6);
////    s6.insert(8);
////    s6.insert(9);
////    s6.insert(10);
////
////    s6.swap(s4);
////    for(int i = 0; i < 5; i++) {
////        unsigned long t;
////        s4.get(i, t);
////        //cerr<< t <<endl;
////    }
//
//
//    /*
//    Set s;
//    assert(s.empty());
//    ItemType x = "arepa";
//    assert( !s.get(42, x)  &&  x == "arepa");  //x unchanged by get failure
//    s.insert("chapati");
//    assert(s.size() == 1);
//    assert(s.get(0, x)  &&  x == "chapati");
//    s.insert("arepa");
//
//    assert(!s.insert("chapati") && !s.insert("arepa"));
//
//    Set s2;
//    s2.swap(s);
//
//    assert(s.empty());
//    assert(s2.size() == 2);
//
//    s2.erase("arepa");
//    assert(s2.size() == 1);
//
//
//    Set ss;
//    assert(ss.insert("roti"));
//    assert(ss.insert("pita"));
//    assert(ss.size() == 2);
//    assert(ss.contains("pita"));
//    ItemType x = "laobing";
//    assert(ss.get(0, x)  &&  x == "pita");
//    assert(ss.get(1, x)  &&  x == "roti");
//    */
//
//    /*
//    Set uls;
//    assert(uls.insert(20));
//    assert(uls.insert(10));
//    assert(uls.size() == 2);
//    assert(uls.contains(10));
//    ItemType x = 30;
//    assert(uls.get(0, x)  &&  x == 10);
//    assert(uls.get(1, x)  &&  x == 20);
//    //cout << "Passed all tests" << endl;
//    Set uls2;
//    assert(uls2.insert(20));
//    assert(uls2.insert(10));
//    assert(uls2.size() == 2);
//    assert(uls2.contains(10));
//    ItemType xx = 30;
//    assert(uls.get(0, x)  &&  x == 10);
//    assert(uls.get(1, x)  &&  x == 20);
//     */
//    //cerr << "Passed all tests" << endl;
//
   }
