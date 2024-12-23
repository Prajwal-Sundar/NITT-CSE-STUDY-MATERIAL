/*
    Program-11
    Write a program to implement Warshall’s algorithm on weighted as well as unweighted graphs.
    @ Prajwal Sundar
*/

#include "bits/stdc++.h"
using namespace std;

// Floyd-Warshall Algorithm on given Matrix
int ** warshall(int ** M, int n)
{
    for (int k = 0; k < n; k++)
    {
        int ** T = new int * [n];
        for (int i = 0; i < n; i++)
        {
            T[i] = new int [n];
            for (int j = 0; j < n; j++)
                T[i][j] = min(M[i][j], M[i][k] + M[k][j]);
        }
        M = T;
    }
    return M;
}

// Main Function
int main()
{
    cout << "Welcome to C++ Floyd Warshall Algorithm !" << endl << endl;

    int v; // number of vertices
    cout << "Enter the number of vertices : ";
    cin >> v;

    int e; // number of edges
    cout << "Enter the number of edges : ";
    cin >> e;

    int ** M = new int * [v]; // adjacency matrix
    for (int i = 0; i < v; i++)
    {
        M[i] = new int [v];
        for (int j = 0; j < v; j++)
        {
            if (i == j) M[i][j] = 0;
            else M[i][j] = INT_MAX;
        }
    }

    cout << "Enter each edge as (source destination weight) :-" << endl;
    int maxW = INT_MIN;

    for (int i = 0; i < e; i++)
    {
        int x, y, w; cin >> x >> y >> w;
        M[x][y] = w; // set value in adjacency matrix
        maxW = max(maxW, w);
    }

    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            if (M[i][j] == INT_MAX) M[i][j] = maxW+1;

    M = warshall(M, v); // apply shortest path algorithm
    cout << endl << "All Pair Shortest Paths are :-" << endl;

    cout << "\t";
    for (int i = 0; i < v; i++) cout << "V" << i << "\t";
    cout << endl;

    for (int i = 0; i < v; i++)
    {
        cout << "V" << i << "\t";
        for (int j = 0; j < v; j++)
        {
            if (M[i][j] == maxW+1) cout << "-" << "\t";
            else cout << M[i][j] << "\t";
        }
        cout << endl;
    }

    cout << endl << "Thank you for using C++ Floyd Warshall Algorithm. Bye Bye !";
}