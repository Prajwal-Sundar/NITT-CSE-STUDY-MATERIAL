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
    if ((n == 0) || (w == 0)) // base case
        return 0; // profit is 0
    
    else if (t[n][w] != -1) // already calculated
        return t[n][w];
    
    else if (wt[n-1] <= w)
        return t[n][w] = max((val[n-1] + knapsack(wt, val, n-1, w-wt[n-1], t)), (knapsack(wt, val, n-1, w, t))); // include and exclude
    
    else
        return t[n][w] = knapsack(wt, val, n-1, w, t); // only exclude
}

// Main Function
void main()
{
    printf("Welcome to C Knapsack Problem Solver (Recursion + Memoization) !\n\n");

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