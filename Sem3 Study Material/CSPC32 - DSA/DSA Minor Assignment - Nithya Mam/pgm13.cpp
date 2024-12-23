/*
    Program-13
    Write a program for finding the kth smallest element in min-heap.
    @ Prajwal Sundar
*/

#include "bits/stdc++.h"
using namespace std;

struct Element
{
    int num;
    int pos;
};

bool comp(struct Element A, struct Element B)
{
    return (A.num < B.num);
}

// Get kth smallest element from a min-heap
int kSmall(vector<int> MH, int k)
{
    int n = MH.size(); // size of min-heap

    vector<struct Element> V; // candidates for smallest node property
    V.push_back({MH[0], 0});

    int ans = INT_MAX;
    for (int i = 1; i <= k; i++)
    {
        sort(V.begin(), V.end(), comp); // sort vector
        ans = V[0].num; // smallest element currently

        int L = (2 * V[0].pos) + 1; // position of left child
        int R = (2 * V[0].pos) + 2; // position of right child

        if (L < n) V.push_back({MH[L], L});
        if (R < n) V.push_back({MH[R], R}); // push children

        V.erase(V.begin()); // remove first element
    }

    return ans;
}

// Main Function
int main()
{
    cout << "Welcome to C++ Min Heaps !" << endl << endl;

    int n; // size of heap
    cout << "Enter the number of elements in your heap : ";
    cin >> n;

    vector<int> MH; // min heap vector
    cout << "Enter your min-heap : ";
    for (int i = 0; i < n; i++)
    {
        int tmp; cin >> tmp;
        MH.push_back(tmp);
    }

    int k; // kth smallest element
    cout << "Enter k to get kth smallest element : ";
    cin >> k;

    if ((k >= 1) && (k <= n)) cout << "The kth smallest element in your min-heap is : " << kSmall(MH, k);
    else cout << "k should be in the range [1,n].";
    cout << endl << endl << "Thank you for using C++ Min Heaps. Bye Bye !";
}