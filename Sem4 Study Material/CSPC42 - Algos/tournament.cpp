#include "bits/stdc++.h"
using namespace std;

int findMin(vector<int> V, int S, int E)
{
    if (S == E) // base case
        return V[S];
    
    int M = (S+E) / 2; // middle element
    return min(findMin(V, S, M), findMin(V, M+1, E));
}

int main()
{
    cout << "Welcome to C++ Tournament Method (Minimum) !" << endl << endl;

    int n;
    cout << "Enter array size : ";
    cin >> n;

    vector<int> V;
    cout << "Enter array : ";
    for (int i = 0; i < n; i++)
    {
        int tmp; cin >> tmp;
        V.push_back(tmp);
    }

    cout << "Minimum Element is : " << findMin(V, 0, n-1);
    cout << endl << endl << "Thank you for using C++ Tournament Method (Minimum). Bye Bye !";
}