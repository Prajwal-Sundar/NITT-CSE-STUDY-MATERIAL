#include "bits/stdc++.h"
using namespace std;

// Banker's Algorithm Implementation
/*void banker(int p, int r, int A[p][r], int N[p][r], int F[p+1][r])
{
    cout << "Hello";
}*/

// Main Function
int main()
{
    cout << "Welcome to C++ Banker's Algorithm !" << endl << endl;

    int p; // number of processes
    cout << "Enter the number of processes : ";
    cin >> p;

    int r; // resources
    cout << "Enter the number of resources : ";
    cin >> r;

    int A[p][r]; // allocation matrix
    int M[p][r]; // maximum need matrix
    int N[p][r]; // need matrix
    int F[p+1][r]; // free (available) resources array

    cout << endl << "Enter your allocation matrix below :-" << endl;
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            cin >> A[i][j];
    
    cout << endl << "Enter the maximum need matrix below :-" << endl;
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            cin >> M[i][j];
    
    // Forming the need matrix
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            N[i][j] = M[i][j] - A[i][j]; // need = max-allocated
    
    cout << endl << "Enter the currently available resources array :-" << endl;
    for (int j = 0; j < r; j++)
        cin >> F[0][j];
    
    //banker(p, r, A, N, F); // banker's algorithm
    cout << endl << endl << "Thank you for using C++ Banker's Algorithm. Bye Bye !";
}