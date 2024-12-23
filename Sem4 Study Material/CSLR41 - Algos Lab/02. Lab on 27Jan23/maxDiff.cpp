#include "bits/stdc++.h"
using namespace std;

// Get maximum difference
int get(int * A, int n)
{
    int min = INT_MAX; // minimum element of the array
    int max = -1; // maximum difference in the array

    for (int i = 0; i < n; i++)
    {
        if (A[i] < min) min = A[i];
        else
        {
            int d = A[i]-min; // current difference
            if (d > max) max = d; // update maximum difference
        }
    }

    return max; // return maximum difference
}

// Main Function
int main()
{
    cout << "Welcome to C++ Maximum Difference Calculator !" << endl << endl;

    int n; // size of array
    cout << "Enter the size of your array : ";
    cin >> n;

    int * A = (int *) malloc(n * sizeof(int)); // array
    cout << "Enter the elements of your array : ";
    for (int i = 0; i < n; i++) cin >> A[i];

    cout << "The maximum difference in the array is : " << get(A, n) << ".";
    cout << endl << endl << "Thank you for using C++ Maximum Difference Calculator. Bye Bye !";
}