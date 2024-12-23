/*
    CSLR41 Algorithms Laboratory-2
    Prajwal Sundar - Roll Number 106121092
    Program-2
    Quick Sort
*/

#include "bits/stdc++.h"
using namespace std;

// Partition Function
int partition(int * A, int L, int U)
{
    int pvt = A[U]; // taking last element as pivot
    int i = L-1; // position of pivot
    
    for (int j = L; j < U; j++)
    {
        if (A[j] < pvt) // less than pivot
        {
            i++; // increment pivot position
            swap(A[i], A[j]); // swap
        }
    }
    
    i++; // final pivot position
    swap(A[i], A[U]); // bring pivot to correct position
    return i; // return pivot position
}

// Sort Function
void sort(int * A, int L, int U)
{
    if (L < U)
    {
        int P = partition(A, L, U); // get position of partition
        sort(A, L, P-1); // sort elements before the partition
        sort(A, P+1, U); // sort elements after the partition
    }
}

// Main Function
int main()
{
    cout << "Welcome to C++ Quick Sorter !" << endl << endl;

    int n; // number of elements in array
    cout << "Enter the number of elements in your array : ";
    cin >> n;

    int * A = (int *) malloc(n * sizeof(int)); // array
    cout << "Enter the elements of your array : ";
    for (int i = 0; i < n; i++) cin >> A[i];

    sort(A, 0, n-1); // sort the whole array
    cout << "Your sorted array is : ";
    for (int i = 0; i < n; i++) cout << A[i] << " ";

    cout << endl << endl << "Thank you for using C++ Quick Sorter. Bye Bye !";
}