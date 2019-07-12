//
//  linear.cpp
//  Homework-3-1
//
//  Created by Henry Macarthur on 2/6/19.
//  Copyright © 2019 Henry Macarthur. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

bool somePredicate(double x);

bool somePredicate(double x)
{
    return x < 0;
}

bool anyTrue(const double a[], int n)
{
    if(n <= 0)
        return false;
    
    int index = n - 1;
    if(index >= 0 && somePredicate(a[index]))
        return true;
    else
        return anyTrue(a, index);

}

int countTrue(const double a[], int n)
{
    if(n <= 0)
        return 0;
    
    int index = n-1;
    if(index >= 0 && somePredicate(a[index]))
    {
        return 1 + countTrue(a, index);
    }
    else
        return countTrue(a, index);
}

int firstTrue(const double a[], int n)
{
    if(n <= 0)
        return -1;
    
    int index = n-1;
    if(index >= 0 && firstTrue(a, index) == -1 && somePredicate(a[index]) )
        return index;
    else
        return firstTrue(a, index);
}

int positionOfMin(const double a[], int n)
{
    int index = n -1;
    if(n <= 0)
        return -1;
    else if(index == 0)
        return 0;
    int rest = positionOfMin(a, index);
    if(a[index] < a[rest])
        return index;
    else
        return rest;
}

bool includes(const double a1[], int n1, const double a2[], int n2)
{
    //check to make sure that n1 < 0 - false
    if(n2 <= 0)
        return true;
    else if(n1 <= 0)
        return false;
    else if(n2 > n1)
        return false;
    
    if(a2[n2-1] == a1[n1-1])
    {
        return includes(a1, n1-1, a2, n2-1);
    }
    else
    {
        return includes(a1, n1-1, a2, n2);
    }        


    //return false;  // This is not always correct.
}

//int main()
//{
//    double arr[7] = {0,2,3,1, -13, -15, 1};
//    int n = 5;
//    
//    double arr1[5] = {1, 2, 3, 4, 5};
//    double arr2[4] = {2, 3, 4, 5};
//    
//    assert(anyTrue(arr, 7));
//    assert(countTrue(arr, 7) == 2);
//    assert(countTrue(arr, 4) == 0);
//    assert(firstTrue(arr,4) == -1);
//    assert(firstTrue(arr, 7) == 4);
//    assert(positionOfMin(arr, 1) == 0);
//    assert(positionOfMin(arr, 7) == 5);
//    assert(!includes(arr, 7, arr1, 5));
//    assert(includes(arr1, 5, arr2, 4));
//    
//    
//    cout << "DONE!" << endl;
//}
