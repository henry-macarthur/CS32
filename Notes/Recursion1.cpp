=====;
NOTES
=====;
* Break big problems/taks into smaller sub problems/tasks and then solve those
* Can keep breaking sub problems into smaller sub problems until we get a managable problem
* Sort a pile of N Items:
  if(N > 1)
  {
  * split the pile into two unsorted piles of about N/2 items each
  * sort the left subpile
  * sort the right subpile
  * merge the two resulting sorted subpiles into one sorted pile
  }

* Requirements for a proper recursive algorithm
  * One or more base cases -- situations that can be solved without a recursive call
  * Recursive case(s) -- must solve a "smaller" problem: closer to a basse case

* When does recursion pay off?
  * Usually recursion is beneficial when you need more than one recursive call
  * Any time we have one recursive call, especially just looking at the last item of an array, an iterative process is just as efficient if not more efficient
  *

====;
CODE
====;
void sort(int a[], int b, int e)
{
  if (e - b > 1) //1 or less items --> already sorted
  {
    int mid = (b + e) / 2; //find the middle --> doesn't have to be exact so its ok if each part is a different size
    sort(a, b, mid); //from b up to but not including mid is the left half
    sort(a, mid, e); //mid is just past the end of the left half, so it is the start of the right half
    merge(a, b, m, e);
  }
}


bool contains(int [], int n, int target)
{
  if(n <= 0)
    return false;
  if(a[n-1] == target)
    return true;
  return contains(a, n-1, target);
}

//need a base case
//need to check to see wether or not we have already encounered the current spot
bool sove(start, goal)
{
  if(start == goal)
    return true;
  mark this position as visited
  for each direction
    if moving one step in that direction is possible and the spot has not been visited,
      if(solve(pos reached by that move, goal))
        return true;
    return false;
}
====;
