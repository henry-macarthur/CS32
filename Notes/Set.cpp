* A set doesn not allow for duplicate elements
* find gives back an iterator if an item has been found, or the end iterator if it has not been found
* If you have a lot of elements, finding items can be very efficient compared to a vector
* Uses < operator to iterate through, no you iterate through in order
* The type of the things in the set must have the < operator defined in the set
* uses !(a < b) and !(a < c), then a == b
  * Only works well with total ordering

set<int> s;
s.insert(10);
s.insert(30);
s.insert(30);
s.insert(20);
cout << s.size(); //writes 3;
if(s.find(20) == s.end())
  ... not found ...

for(set<int>::iterator p = s.begin(); p!= s.end(); p++)
  cout << *p << endl; //writes out in order
