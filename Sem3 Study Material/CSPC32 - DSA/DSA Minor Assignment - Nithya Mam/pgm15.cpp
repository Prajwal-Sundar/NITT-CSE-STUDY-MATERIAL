/*
    Program-15
    Implement Strassen’s Matrix multiplication using Divide and Conquer approach.
    @ Prajwal Sundar
*/

#include "bits/stdc++.h"
using namespace std;

// Padding Operation
int ** padding(int ** M, int r, int c, int n)
{
    int ** matrix = new int * [n];
    
    for (int i = 0; i < r; i++)
    {
        matrix[i] = new int [n];
        for (int j = 0; j < c; j++) matrix[i][j] = M[i][j];
        for (int j = c; j < n; j++) matrix[i][j] = 0;
    }

    for (int i = r; i < n; i++)
    {
        matrix[i] = new int [n];
        for (int j = 0; j < n; j++) matrix[i][j] = 0;
    }

    return matrix;
}

// Addition Operation
int ** Add(int ** A, int rA, int cA, int ** B, int rB, int cB, int n)
{
    int ** C = new int * [n];
    for (int i = 0; i < n; i++)
    {
        C[i] = new int [n];
        for (int j = 0; j < n; j++)
            C[i][j] = A[i+rA][j+cA] + B[i+rB][j+cB]; // addition operation
    }
    return C;
}

// Subtraction Operation
int ** Sub(int ** A, int rA, int cA, int ** B, int rB, int cB, int n)
{
    int ** C = new int * [n];
    for (int i = 0; i < n; i++)
    {
        C[i] = new int [n];
        for (int j = 0; j < n; j++)
            C[i][j] = A[i+rA][j+cA] - B[i+rB][j+cB]; // subtraction operation
    }
    return C;
}

// Strassen's Matrix Multiplication on two n x n matrices, where n is a power of 2
int ** Mul(int ** A, int rA, int cA, int ** B, int rB, int cB, int n)
{
    int ** C = new int * [n];
    for (int i = 0; i < n; i++) C[i] = new int [n];

    if (n == 1)
    {
        C[0][0] = A[rA][cA] * B[rB][cB]; // perform multiplication
        return C; // return
    }

    // Temperory M matrices
    int ** M1 = Add(A, rA, cA, A, rA + n/2, cA + n/2, n/2); // A11 + A22
    int ** M2 = Add(B, rB, cB, B, rB + n/2, cB + n/2, n/2); // B11 + B22
    int ** M3 = Add(A, rA + n/2, cA, A, rA + n/2, cA + n/2, n/2); // A21 + A22
    int ** M4 = Sub(B, rB, cB + n/2, B, rB + n/2, cB + n/2, n/2); // B12 - B22
    int ** M5 = Sub(B, rB + n/2, cB, B, rB, cB, n/2); // B21 - B11
    int ** M6 = Add(A, rA, cA, A, rA, cA + n/2, n/2); // A11 + A12
    int ** M7 = Sub(A, rA + n/2, cA, A, rA, cA, n/2); // A21 - A11
    int ** M8 = Add(B, rB, cB, B, rB, cB + n/2, n/2); // B11 + B12
    int ** M9 = Sub(A, rA, cA + n/2, A, rA + n/2, cA + n/2, n/2); // A12 - A22
    int ** M10 = Add(B, rB + n/2, cB, B, rB + n/2, cB + n/2, n/2); // B21 + B22

    // Intermediate Strassen's 7 Matrices
    int ** P = Mul(M1, 0, 0, M2, 0, 0, n/2);
    int ** Q = Mul(M3, 0, 0, B, rB, cB, n/2);
    int ** R = Mul(A, rA, cA, M4, 0, 0, n/2);
    int ** S = Mul(A, rA + n/2, cA + n/2, M5, 0, 0, n/2);
    int ** T = Mul(M6, 0, 0, B, rB + n/2, cB + n/2, n/2);
    int ** U = Mul(M7, 0, 0, M8, 0, 0, n/2);
    int ** V = Mul(M9, 0, 0, M10, 0, 0, n/2);

    // Some more intermediate matrices
    int ** M11 = Add(P, 0, 0, S, 0, 0, n/2);
    int ** M12 = Sub(V, 0, 0, T, 0, 0, n/2);
    int ** M13 = Add(P, 0, 0, R, 0, 0, n/2);
    int ** M14 = Sub(U, 0, 0, Q, 0, 0, n/2);

    // Final Strassen's Results
    int ** C11 = Add(M11, 0, 0, M12, 0, 0, n/2);
    int ** C12 = Add(R, 0, 0, T, 0, 0, n/2);
    int ** C21 = Add(Q, 0, 0, S, 0, 0, n/2);
    int ** C22 = Add(M13, 0, 0, M14, 0, 0, n/2);

    // Copy Values into C Matrix
    for (int i = 0; i < n/2; i++)
    {
        for (int j = 0; j < n/2; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j+n/2] = C12[i][j];
            C[i+n/2][j] = C21[i][j];
            C[i+n/2][j+n/2] = C22[i][j]; // copy
        }
    }

    return C; // return multiplied result
}

// Display a Matrix
void display(int ** M, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++) cout << M[i][j] << "\t";
        cout << endl;
    }
}

// Main Function
int main()
{
    cout << "Welcome to C++ Strassen's Matrix Multiplication !" << endl << endl;

    int rA, cA;
    cout << "Enter the dimensions of your first matrix : ";
    cin >> rA >> cA;

    int rB, cB;
    cout << "Enter the dimensions of your second matrix : ";
    cin >> rB >> cB;

    if (cA != rB) // multiplication not possible
        cout << "Sorry, multiplication not possible as the number of columns of the first matrix and number of rows of the second matrix are not equal." << endl;
    
    else
    {
        cout << endl << "Enter matrix A below :-" << endl;
        int ** A = new int * [rA];
        for (int i = 0; i < rA; i++)
        {
            A[i] = new int [cA];
            for (int j = 0; j < cA; j++) cin >> A[i][j];
        }

        cout << endl << "Enter matrix B below :-" << endl;
        int ** B = new int * [rB];
        for (int i = 0; i < rB; i++)
        {
            B[i] = new int [cB];
            for (int j = 0; j < cB; j++) cin >> B[i][j];
        }

        vector<int> D = {rA, cA, rB, cB}; int n = INT_MIN;
        for (int i = 0; i < 4; i++) n = max(n, D[i]); // get maximum dimension
        n = (int) pow(2, ceil(log(n)/log(2))); // convert to next nearest power of 2

        int ** X = padding(A, rA, cA, n);
        int ** Y = padding(B, rB, cB, n); // convert to square matrices by padding

        int ** C = Mul(X, 0, 0, Y, 0, 0, n); // strassen
        cout << endl << "Multiplied Result :-" << endl;
        display(C, rA, cB);
    }

    cout << endl << "Thank you for using C++ Strassen's Matrix Multiplication. Bye Bye !";
}