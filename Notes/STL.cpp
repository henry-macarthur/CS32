stack
queque
================================================================================
vector -> dynamically resizeable array
  * #include <vector>
  * vector<itemType> vi;
  * push_back(item) -> adds item to the encounered
  * front() -> fist item
  * back() -> last item
  * [i] -> gives reference to the current item, can look at it or change it
    * undefined behavior to access eldment outside of the array, or if the array is empty
    * does not have built in error checking
  * pop_back() -> remove the last item from the vector
    * undefined behavior to call this when the list is empty
  * empty()
  * size() -> how many elements exist in the array
  * at(index)
    * gives a reference to the item at current index
    * does error checking for us! -> throws exception and stops, but ww do not have undefined behavior
  * constructor(int howManyElements) -> initializes the vector with x amount of howManyElements
    * initialized with default values, int is 0
  * constructor(int n, int defalutValues)
  * constructor(pointer to where it starts, pointer to one past wher it ends); //if we want to initialize it with the contents of another vector
    * gives us the contents of the array we are copying as well as its length
  * = {10, 20, 30, 40, 50, ...}
    * equal sign is optional

Common vector mistakes:
  vector<int> vi;
  vi[0] = 10; <-- there are no valid values in the vector, the vector is empty; undefined behavior
              <-- to add an element we need to use a pushback() call

* if you store pointers to vectors while you are inserting items into a vector
  * be careful, when reallocation occurs these pointers become invalid!!!
================================================================================
#include <list> <-- linked list

list<int> li; <-- is a double linked list!
  * push_back();
  * push_front();
  * pop_back();
  * pop_front();
  * cannot use the [] or .at() operators
    * not cheap!
  * .begin() gives a pointer to the beginning of the list
  * .end() gives a pointer to one past the last elements

  visit each element:

  for(list<int>::iterator p = li.begin(); p != li.end(); p++)
    cout << * p << endl;

*iterator acts like a pointer
 *iterators point to the items in the node, not the nodes;

* in general, an iterator cannot hold the value of nullptr
  * if it is empty, it holds the value of end()
 ===================LIST ITERATORS
 * it is undefined behavior to call -- on the firtst element
 * it is undefiuned behavior to call anything on the end pointers
 * it is undefined behavior to call ++ on the last item
 * inserting into a list doesn not invalidate other iterators/pointers
 * erase gives a pointer back to the item afte the one you deleted
 ==================VECTOR ITERATORS
 * iterators for vectors support general pointer arithmatic
 * vector has a .insert() function
  * same as a list, insert before the desired index
  * pushes EVERYTHING back
 * Once insert is called on a vector, all pointers pointing into the vector become invalid
  * no longer points to the desired value
  * even the iterator pointer may be invalid
 * insert returns a value -> iterator pointing to the newly inserted item;
 * all pointers/iteraters after the item you call erase on becomes invalid
  * the ones before are considered valid though
 * the return value of insert gives a pointer to the element after you removed
 ================STL ALGORITHMS
  * the find ALGORITHM
    * only works on items that provide the == operator
      * passing in "FRED" is not a string, its a character array
      * string("FRED") does work though
  * can compare a string to a char array
