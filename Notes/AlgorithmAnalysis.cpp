* Want to know wha tthe growth pattern is like
* Ignore lower order terms
* The highest order term conveys most of the important info
* Consider algorithm efficiency in terms of N
* A Function f(N) is O(g(N)) if there exists N_0, and k such that for all N >= N_0, |f(N)| <= k*g(N)
* F(N) is "order g(N)"
* can ignore the constant of proportionality for the highest order term as well
* Accessing elements in an array takes constant time
  * Proportiona to O(1)
* linear search, wether an array is sorted or not takes N time
* Binary seach on a sorted array takes LOGBASE-2-(N)
  * The base of the logarithm can go away - all logarithms are proportional to each other
* ignore the base when considering logarithmic functions
* Go from inside out. cannot just consider each for loop, etc, look at the run time of the if statemensts and the fucntions being called

O(2^N) > O(N^C) > O(N^2) > O(N) > O(NLog(N)) > O(N) > OLog(N) > O(1)

* for a set of n items, there are 2^n subsets
* sum of all numbers from 1 to n-1 is 1/2n^2 - 1/2n
  * still just O(n^2), ignore constant of proportionality for now

  //in total, the loop iterates N^2Log(N) times
  for(int i = 0; i < n; ...) //loop runs N times, its contents run Nlog(N) times
  {
    for(int j = 0; j < N; ...) //this loop goes N, times, but the conntents of the loop go Log(N) times
    {
      d[i][k] = f(a, N); //say this equals log(N)
    }
  }

for( ... R Times ...) //O(RClog(C))
{
  for(... C Times ...) // O(Clog(C))
    ...f(...C...) //O(log(C))
}
