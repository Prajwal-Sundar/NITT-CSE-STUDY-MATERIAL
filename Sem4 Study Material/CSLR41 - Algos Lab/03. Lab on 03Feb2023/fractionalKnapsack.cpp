#include "bits/stdc++.h"
using namespace std;

// Sort based on value/weight ratio
void sort(int * WT, int * val, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            double first = (1.0 * val[j]) / (1.0 * WT[j]);
            double second = (1.0 * val[j+1]) / (1.0 * WT[j+1]);
            if (first > second) // exchange
            {
                int tmp = val[j]; val[j] = val[j+1]; val[j+1] = tmp; // exchange values
                tmp = WT[j]; WT[j] = WT[j+1]; WT[j+1] = tmp; // exchange weights
            }
        }
    }
}

// Fractional Knapsack Program
double get(int W, int n, int * WT, int * val)
{
    sort(WT, val, n); // sort based on value/weight ratio
    double s = 0; // sum value variable
    for (int j = n-1; j >= 0; j--)
    {
        if (W >= WT[j]) // full weight can be taken
        {
            cout << "Item with weight = " << WT[j] << " taken, profit = " << val[j] << endl;
            s += val[j]; // take item
            W -= WT[j]; // reduce weight left
        }

        else // full weight cannot be taken, take fraction instead
        {
            double frac = (1.0 * W) / (1.0 * WT[j]); // fraction
            double value = (frac * val[j]); // value of fraction taken
            cout << frac << " parts of item with weight = " << WT[j] << " taken, profit = " << value << endl;
            s += value; // take item
            W = 0; // capacity filled
            break; // exit
        }
    }
    return s;
}

int main()
{
    cout << "Welcome to C++ Fractional Knapsack Problem !" << endl << endl;

    int n; // number of objects
    cout << "Enter the number of objects : ";
    cin >> n;

    int W; // weight of bag
    cout << "Enter the weight of your bag : ";
    cin >> W;

    int WT[n]; // weights of objects
    cout << "Enter the weights of your objects : ";
    for (int i = 0; i < n; i++) cin >> WT[i];

    int val[n]; // value of objects
    cout << "Enter the values of your objects : ";
    for (int i = 0; i < n; i++) cin >> val[i];

    cout << endl;
    double profit = get(W, n, WT, val);
    cout << "Therefore, maximum profit = " << profit;
    cout << endl << endl << "Thank you for using C++ Fractional Knapsack Problem. Bye Bye !";
}