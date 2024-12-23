#include "bits/stdc++.h"
using namespace std;

void get(vector<int> W, vector<int> P, int Wt, int n)
{
    int M[n+1][Wt+1]; // matrix

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= Wt; j++)
        {
            if ((i == 0) || (j == 0)) // base cases
                M[i][j] = 0;
            else if (W[i-1] > j) // only exclusion
                M[i][j] = M[i-1][j];
            else // inclusion and exclusion
                M[i][j] = max(M[i-1][j], P[i-1]+M[i-1][j-W[i-1]]);
        }
    }

    cout << endl << "\t" << "W";
    for (int i = 0; i <= Wt; i++) cout << "\t" << i;
    cout << endl;

    for (int i = 0; i <= n; i++)
    {
        if (i == 0) cout << "Pi" << "\t" << "Wi" << "\t";
        else cout << P[i-1] << "\t" << W[i-1] << "\t";

        for (int j = 0; j <= Wt; j++)
            cout << M[i][j] << "\t";
        
        cout << endl;
    }

    cout << endl << "Maximized profit = " << M[n][Wt];
}

int main()
{
    cout << "Welcome to C++ DP: 0/1 Knapsack !" << endl << endl;

    int Wt; // weight of bag
    cout << "Enter the weight of your bag : ";
    cin >> Wt;

    int n; // number of objects
    cout << "Enter the number of objects : ";
    cin >> n;

    vector<int> W; // weights of objects
    cout << "Enter the weights of your objetcs : ";
    for (int i = 0; i < n; i++)
    {
        int tmp; cin >> tmp;
        W.push_back(tmp);
    }

    vector<int> P; // profits of objects
    cout << "Enter the profits of your objects : ";
    for (int i = 0; i < n; i++)
    {
        int tmp; cin >> tmp;
        P.push_back(tmp);
    }

    get(W, P, Wt, n); // invoke function
    cout << endl << endl << "Thank you for using C++ DP: 0/1 Knapsack. Bye Bye !";
}