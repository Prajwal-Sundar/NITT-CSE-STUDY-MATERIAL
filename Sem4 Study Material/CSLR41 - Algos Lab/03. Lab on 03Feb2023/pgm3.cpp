#include "bits/stdc++.h"
using namespace std;

// Get maximum length of subarray with positive product
int maxL(int * arr, int n)
{
    int ans = 0; // answer
    int P = 0, N = 0; // length of positive and negative product subarray

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > 0) // positive number obtained
        {
            P++;
            if (N) N++;
        }

        else if (arr[i] < 0) // negative number obtained
        {
            swap(P, N); // negative number reverses sign
            N++;
            if (P) P++;
        }

        else // zero obtained
            P = N = 0; // reset
        
        ans = max(ans, P); // maximize the positive length
    }

    return ans;
}

// Main Function
int main()
{
    cout << "Welcome to C++ Subarrays !" << endl << endl;

    int n; // size of array
    cout << "Enter the size of your array : ";
    cin >> n;

    int * arr = (int *) malloc(n * sizeof(int)); // array
    cout << "Enter the elements of your array : ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "The maximum length of a subarray with positive product is : " << maxL(arr, n);
    cout << endl << endl << "Thank you for using C++ Subarrays. Bye Bye !";
}