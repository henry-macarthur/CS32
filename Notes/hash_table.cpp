collision: two different keys map to the same bucket

hash function     key->unsigned int

hash function: deterministic, cheap, uniformly distributed result

FNV-1

*take remainder mod by number of buckets;

unsinged int h = 2166136261U;

for(int k = 0; k < key.size(); k++)
{
  h += key[k];
  h *= 16777619;
}

load factor = # of items / # of buckets = average bucket size;

*If we resize the array containing buckets, then we have to rehash everything so that the hash function maps to the correct bucket
*Visit each item then modify some pointers and add them to the new array
*Delete old array
*Then we can add each item to the new array


*Keep adding items
*When wew hit the limit, resize the array and rehash everything
  *This can be problematic because when we move over a large amout of elements in can slow our program down

*INCREMENTAL REHASHING
*When we hit the max of a has table:
  *Keep adding a certain amount of items to a new array
  *Once we empty the origional array
    *delete origional array and just use the new table
  *If we are in a state where we have two tables, we look at both tables(this only happens 1/5 of the time)
    *This is still constant time

*HASH TABLE V BINARY TREE
*There is a startup cost of initializing the array and all of the buckets even though we won't use them all right away
  *Always remeber to initialize pointers
*BST have no initial startup cost


.....
#include <unordered_map>
using namespace std;

...

string name;
double amt;
while(cin >> name >> amt)
  ious[name] += amt;

for(unordered_map<string, double>::iterator p = ious.begin(); p != ious.end(); p++)
  cout << p->first << "owes me $" << p->second << endl;


*Type for a key of a hash function needs a == operator define
*type for a key of a tree needs a < defined
*For non defined elements for hash tables, go to cpp.com to find out how to write your own hash function

*Takes NlogN to sort a hash tables
  *Takes N to inout all of the items
*Takes NlogN to fill up an entire search tree, then takes n to go through all the items
*Both have to pay the NLogN price somewhere
