#include "bits/stdc++.h"
using namespace std;

// Declare a matrix of required dimensions
int ** create(int r, int c)
{
    int ** X = (int **) malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++)
    {
        X[i] = (int *) malloc(c * sizeof(int));
        for (int j = 0; j < c; j++)
            X[i][j] = 0;
    }
    return X;
}

// Banker's Algorithm Implementation
void banker(int p, int r, int ** A, int ** M, int ** N, int ** F)
{
    bool flag[p]; // flag variable for processes
    memset(flag, false, sizeof(flag));
    int P = 0; // pointer to currently available resources
    cout << endl << "Safe Sequence : ";

    while (P < p)
    {
        int process = -1; // next process to be allocated resources

        for (int i = 0; i < p; i++)
        {
            if (flag[i]) continue; // process already scheduled
            
            bool check = true;
            for (int j = 0; j < r; j++)
            {
                if (N[i][j] > F[P][j]) // insufficient resources
                {
                    check = false;
                    break;
                }
            }

            if (!check) continue; // process can't be scheduled
            else
            {
                process = i;
                break;
            }
        }

        if (process == -1) // deadlock case
        {
            cout << "Unsafe";
            break;
        }

        else // allocate resources to process
        {
            cout << "P" << process << " ";
            P++; // increment pointer
            for (int j = 0; j < r; j++)
                F[P][j] = F[P-1][j] + A[process][j]; // update available resources
            flag[process] = true;
        }
    }

    cout << endl << "Tables are as follows :-" << endl;
    cout << "Allocation Matrix, Maximum Need Matrix, Need Matrix and Available Matrix :-" << endl;

    cout << "\t";
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < r; j++)
            cout << "R" << j << "\t";
    cout << endl;

    for (int i = 0; i < p; i++)
    {
        cout << "P" << i << "\t";
        for (int j = 0; j < r; j++) cout << A[i][j] << "\t";
        for (int j = 0; j < r; j++) cout << M[i][j] << "\t";
        for (int j = 0; j < r; j++) cout << N[i][j] << "\t";
        for (int j = 0; j < r; j++) cout << F[i][j] << "\t";
        cout << endl;
    }

    cout << "\t";
    for (int j = 0; j < (3*r); j++) cout << "\t";
    for (int j = 0; j < r; j++) cout << F[p][j] << "\t";
}

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

    int ** A = create(p, r); // allocation matrix
    int ** M = create(p, r); // maximum need matrix
    int ** N = create(p, r); // need matrix
    int ** F = create(p+1, r); // free (available) resources matrix

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
    
    banker(p, r, A, M, N, F); // banker's algorithm
    cout << endl << endl << "Thank you for using C++ Banker's Algorithm. Bye Bye !";
}