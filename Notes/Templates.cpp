* It is annoying to write the same text twice
  * EX: have two funcitons that do the same thing but deal with differetn data types
* Match the template function
* The instantiated template must compile
* The compiled code must do what you want

=====================
template<typename T>
T minimum( T a, T b)
{
  if (a < b)
    return a;
  else
    return b;
}
--> This is a pattern for how to manufacture a function that will compute the minimum
--> If we have a pattern, we can then manufacture it later
--> typename is a language variable of C++
  --> T hold the value of the item type that we will be using: int, bool, char, ...

int main()
{
  int k;
  cin >> k;
  cout << minimum(k, 10)/2; --> T would hold the value of an int
  double x;
  ...
  double y = 3 * minimum(x*x, x+10); --> T would hold the value of a double
  ...
  int z = minimum(0, 3*k - k +4);
}

=====================
template<typename T, typename T2>
... minimum( T a, T2 b)
{
  if (a < b)
    return a;
  else
    return b;
}
--> what would the return type because what if we want to return a double in some cases or a int in other cases
  --> Templates cannot solve every problem, can only return if the types are matchibg

int main()
{
  int k;
  ... minimum(k, 3.5) ...
}
=====================
Chicken minimum(Chicken a, Chicken b)
{
  if(a < b) //crashes because we hav enot overloaded the < operator for type chicke!
    return a;
  else
    return b;
}
=====================
int main()
{
  char ca1[100];
  char ca2[100];
  ...
  char* ca3 = minimum(ca1, ca2); //returns a pointer to the desired char array
}

Our template function looks like:
char* minumum(char* a, char* b)
{
  if(a<b)
    return a;
  else
    return b;
--> this does not work becuase if compares pointer values, not the actual values;
  --> there is a way to get around this

char* minmum(char* a, char* b)
{
  if(strcmp(a, b) < 0)
    return a;
  else
    return b;
}

--> overload the minumum function so that we make specific cases that do not work with the origional template
--> A non template funcion takes precedence over a template function
=====================
string(10, '*'); --> gives a string of 10 '*';
string(); -> empty string, gives default type for the types
  --> string: "", double: 0, int: 0, bool:false, ptr: nullptr;

template<typename T>
T sum(const T a[], int n)
{
  T total = T();
  for(int k = 0; k < n; k++)
    total += a[k];
  return total;
}
