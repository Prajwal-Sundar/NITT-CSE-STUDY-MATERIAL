/*
    CSLR41 Algorithms Laboratory-2
    Prajwal Sundar - Roll Number 106121092
    Program-1
    Merge Sort
*/

#include "bits/stdc++.h"
using namespace std;

// Merge Function
void merge(int * A, int L, int U)
{
    int M = (L+U) / 2; // median position
    int * B = (int *) malloc((U-L+1) * sizeof(int)); // temperory array to store

    int P1 = L, P2 = M+1, P = 0; // pointers
    while ((P1 <= M) && (P2 <= U))
    {
        if (A[P1] < A[P2]) B[P++] = A[P1++];
        else B[P++] = A[P2++]; // store lesser element
    }

    while (P1 <= M) B[P++] = A[P1++]; // remaining elements in first half
    while (P2 <= U) B[P++] = A[P2++]; // remaning elements in second half
    for (int i = 0; i < U-L+1; i++) A[i+L] = B[i]; // copy into original array
}

// Sort Function
void sort(int * A, int L, int U)
{
    if (L < U)
    {
        int M = (L+U) / 2; // middle position
        sort(A, L, M); // sort left half
        sort(A, M+1, U); // sort right half
        merge(A, L, U); // merge both sorted portions
    }
}

// Main Function
int main()
{
    cout << "Welcome to C++ Merge Sorter !" << endl << endl;

    int n; // number of elements in array
    cout << "Enter the number of elements in your array : ";
    cin >> n;

    int * A = (int *) malloc(n * sizeof(int)); // array
    cout << "Enter the elements of your array : ";
    for (int i = 0; i < n; i++) cin >> A[i];

    sort(A, 0, n-1); // sort the whole array
    cout << "Your sorted array is : ";
    for (int i = 0; i < n; i++) cout << A[i] << " ";

    cout << endl << endl << "Thank you for using C++ Merge Sorter. Bye Bye !";
}