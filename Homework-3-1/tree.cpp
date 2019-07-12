#include <iostream>
using namespace std;
// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then for this value of a2     the function must return
//    10 20 40            1
//    10 40 30            2
//    20 10 40            0
//    50 40 30            3
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    if(n2 <= 0)
        return 1;
    else if(n1 <= 0)
        return 0;
    else if(n2 > n1)
        return 0;
    
    int count = 0;

    if(a1[n1 -1] == a2[n2 -1])
    {
        count += countIncludes(a1, n1-1, a2, n2-1);
        count += countIncludes(a1, n1-1, a2, n2);
    }
    else
    {
        count += countIncludes(a1, n1-1, a2, n2);
    }

    return count;
}

// Exchange two doubles
void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}


void divide(double a[], int n, double divider,
            int& firstNotGreater, int& firstLess)
{
    if (n < 0)
        n = 0;
    
    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < divider)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > divider)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{
    int c, b;
    if(n <= 1)
        return;  // This is not always correct.
    else
    {
        divide(a, n, a[n-1],b,c);
        order(a, b);
        order(a+c, n-c);
    }
}


//int main()
//{
//    double arr1[7] = {10, 50, 40, 20, 50, 40, 30};
//    double arr2[3] = {10, 20, 40};
//    double arr3[3] = {10, 40, 30};
//    double arr4[3] = {20, 10, 40};
//    double arr5[3] = {50, 40, 30};
//    
//    double arr6[3] = {10, 10, 10};
//    double arr8[4] = {10, 10, 10, 10};
//    double arr7[7] = {10, 10, 10, 10, 10, 10, 10};
//    cout << countIncludes(arr7, 7, arr6, 3) << endl;
//    cout << countIncludes(arr7, 7, arr8, 4) << endl;
//    assert(countIncludes(arr1, 7, arr2, 3) == 1);
//    assert(countIncludes(arr1, 7, arr3, 3) == 2);
//    assert(countIncludes(arr1, 7, arr4, 3) == 0);
//    assert(countIncludes(arr1, 7, arr5, 3) == 3);
//    assert(countIncludes(arr1, 7, arr5, 0) == 1);
//    assert(countIncludes(arr1, 0, arr5, 0) == 1);
//    assert(countIncludes(arr1, -1, arr5, 1) == 0);
//    assert(countIncludes(arr1, -1, arr5, 0) == 1);
//
////    double orderA[5] = {5,3,2,4,1};
////    order(orderA, 5);
////    for(int i = 0; i < 5; i++)
////        cout << orderA[i] << " ";
////    cout << endl;
////
////    order(arr1, 7);
////    for(int i = 0; i < 7; i++)
////        cout << arr1[i] << " ";
////    cout << endl;
////
////    double orderB[2] = {1,2};
////    order(orderB, 2);
////    for(int i =0; i < 2; i++)
////        cout << orderB[i] << " ";
////    cout << endl;
////
//    cout << "DONE!" << endl;
//    
//}
// 
