O(NLog(N)) average case:
quicksort: worst case O(N^2), const of proportionality for N log N is best of the three
  introsort: worst case O(N Log N)

mergesort: requires extra storage to have a good constant of proportionality, worst case O(NlogN)
  -->choice of sorting collections that are not in an array or vector

heapsort: const of prop. not as good as quicksort, worst case O(N log N)
  *can be used as part of introsort
  *looking to find x best items in order, heapsort is good.

SORT STABILITY
-a stable sort maintinst the items that have equal value in the origional order they were in
  -merge sort
