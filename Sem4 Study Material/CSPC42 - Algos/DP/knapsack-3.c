#include <stdio.h>
#include <string.h>

// Maximum function
int max(int x, int y)
{
    return (x > y) ? x : y;
}

// Knapsack Function
int knapsack(int wt [], int val [], int n, int w, int t[n+1][w+1])
{
    for (int i = 0; i < n+1; i++)
    {
        for (int j = 0; j < w+1; j++)
        {
            if ((i == 0) || (j == 0)) // base case
                t[i][j] = 0;
            
            else if (wt[i-1] <= j) // include and exclude
                t[i][j] = max(val[i-1] + t[i-1][j-wt[i-1]], t[i-1][j]);
            
            else // only exclude
                t[i][j] = t[i-1][j];
        }
    }

    return t[n][w]; // return required value
}

// Main Function
void main()
{
    printf("Welcome to C Knapsack Problem Solver (Top-Down Method) !\n\n");

    int n; // number of items
    printf("Enter the number of items : ");
    scanf("%d", &n);

    int w; // weight of bag
    printf("Enter the weight of the bag : ");
    scanf("%d", &w);

    int wt [n]; // weights of items
    printf("Enter the weights of the items : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &wt[i]);
    
    int val[n]; // values of items
    printf("Enter the values of the items : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &val[i]);
    
    int t[n+1][w+1]; // array for memoization purpose
    memset(t, -1, sizeof(t));

    int soln = knapsack(wt, val, n, w, t); // get solution
    printf("Maximum Profit : %d", soln);

    printf("\n\nThank you for using C Knapsack Problem Solver. Bye Bye !");
}