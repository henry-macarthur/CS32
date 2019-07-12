============================
PRIORITY QUEUES
============================

*A Queue is first in first out
*What if we want to look at elements in terms of priority
  *EX: printing out pages, 1 page has higher priority than 1000 page

*We take element out based on its highest priority, not when it was added to the queue;
  *We could have the priorty change over time
    *This is to deal with starvation because higher priority items could keep being added and then the item with the lowest priority isnt ever accessed
    *Could havce priority change with how long it has been in the queue

*A Stack and a Queue are kind of like a Prioroty Queue because highest priority is determined off of when an item is added

USING SOME SORT OF LIST OR VECTOR
*Insert O(N)
*Remove O(1)

USING A BINARY TREE
*insert O(logN)
*remove O(logN)

HEAP
*A complete binary TREE
  *fully filled binary tree from left to right
*insertion(O(LogN)) --> load a heap with n items is Nlog(N) steps
  *first add the item to keep the heap a complete binary TREE
  *next, keep swapping newly added item with parent until it is (less/greater) than the parent
*Removal(O(Log(N))
  *remove root
  *move bottom right most item to the root
  *trickle down the root node to its proper place

MAX HEAP
*value at any level is greater than or equal to everything below it
*Does not matter about order of left or right children, it just cares about parent/child relationships

MIN HEAP
*each node has a value less than all node in its subtree

HEAP SORT
*Uses a heap to partially sort an array
  *Sort only certain ammount of elements(ex: top 10%) in an array
*NLog(N)

HEAP USING A VECTOR/ARRAY
*Number to items in a tree from left to right
  *Start on the first row and associate it with 0
  *Take the left child, set it to the apropriate count, go across and label
    *repeat
*bottom right most value is just the last item
*no reason to insert into a tree
*given node numner i, is there a formula to determine what the partent is?
  *(i-1)/2 ---> parent(i) = ((i-1)/2)
*given node number i, how do i get the children of it?
  *children(j) = [2j+1, 2j+2] ==>provided that the calculation gives us a number less than or equal to num items in the tree

                  80
            65           70
        40     62       60 20
      10  30  52

80, 65, 70, 40, 62, 60, 20, 10, 20, 50

insert item(ex. 66)
*is the current item bigger than its parent?-->place it in the last item in the array
  *swap them if this is true
  *repeat

get rid of the biggest items
*will always be at 0
  *replace the index with the bottom right most item
  *compare the root with its children, swap if it is less than either 1

*sort the HEAP
  *dump all the items into a heap
  *pull them out one by one

HEAP SORT[O(NLog(N))]
-->Part1 O(NLog(N))
*Take a given array of elements
*consider that array a complete binary tree representing those items
  *does not necessarily represent a tree because we do not care about order when inderting
*starting from the bottom most item, make a HEAP
  *any leaft item in the tree is a HEAP
*find first node with one child
  *Take number of items and divide by 2: where we are going to start
*We know that all of the items below it are already a heap
*remake the heap by trickling down the item to from a HEAP relative to that item
*Then we look at the current items parent, then make that a Heap until we get to the root of a tree
---->done with the first phase of heapsort
--->Part 2 O(NLog(N))
*Now we just have to go remove each item from the HEAP
  *Take the root(want we want)-> swap it with the item we replaced it with
    *trickle down the item->furthest we should go is to the barrier we just established
-->we can keep doing this until we get to the last item
*maintain a barrier that is just before the last item we just swapped from
We can just resort to swapping the last two elements when the barrier is just past i == 1(second index)
