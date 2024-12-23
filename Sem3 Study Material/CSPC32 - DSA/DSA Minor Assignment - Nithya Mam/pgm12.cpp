/*
    Program-12
    Given an array A[] consisting of 0’s, 1’s and 2’s, Write a program to sort this array 
A[] using Quick Sort.
    @ Prajwal Sundar
*/

#include "bits/stdc++.h"
using namespace std;

// Partition Function
int partition(int * A, int L, int U)
{
    int i = L-1, j; // pointers
    for (j = L; j < U; j++)
    {
        if (A[j] < A[U])
        {
            i++; // increment pivot positioner
            swap(A[i], A[j]); // swap
        }
    }
    i++; // final pivot positioner
    swap(A[i], A[U]); // swap with pivot
    return i; // return pivot position
}

// Quick Sort Function
void sort(int * A, int L, int U)
{
    if (L < U)
    {
        int P = partition(A, L, U); // get partition
        sort(A, L, P-1); // sort elements left of partition
        sort(A, P+1, U); // sort elements right of partition
    }
}

// Main Function
int main()
{
    cout << "Welcome to C++ Quick Sort !" << endl << endl;

    int n; // number of elements of array
    cout << "Enter the size of your array : ";
    cin >> n;

    int A[n]; // array
    cout << "Enter your array : ";
    for (int i = 0; i < n; i++) cin >> A[i];

    sort(A, 0, n-1); // quick sort function
    cout << "Sorted Array : ";
    for (int i = 0; i < n; i++) cout << A[i] << " ";

    cout << endl << endl << "Thank you for using C++ Quick Sort. Bye Bye !";
}