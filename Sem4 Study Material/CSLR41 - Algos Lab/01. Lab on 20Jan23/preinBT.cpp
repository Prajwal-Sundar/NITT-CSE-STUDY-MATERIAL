/*
    CSLR41 Algorithms Laboratory
    Prajwal Sundar - Roll Number 106121092
    Program-2
    Form a binary tree using the given pre-order and in-order traversals
*/

#include "bits/stdc++.h"
using namespace std;

// Structure of a Binary Tree Node
struct Node
{
    int data; // data
    struct Node * left, * right; // left and right children

    Node(int n) // constructor
    {
        data = n; // set data
        left = right = NULL; // leaf node by default
    }
};

// Search an element in a sorted array between two given positions
int search(int * A, int n, int L, int U)
{
    for (int i = L; i <= U; i++)
        if (A[i] == n) return i; // element found
    return -1; // element not found
}

// Construct a binary tree using given pre and post orders
struct Node * formTree(int pre [], int in [], int L1, int U1, int L2, int U2)
{
    if (L1 > U1) return NULL;

    struct Node * root = new Node(pre[L1]);
    if (L1 == U1) return root;

    int P = search(in, pre[L1], L2, U2); // locate root in in-order
    root->left = formTree(pre, in, L1+1, P+L1-L2, L2, P-1); // form left subtree
    root->right = formTree(pre, in, P+L1-L2+1, U1, P+1, U2); // form right subtree

    return root;
}

// Print a binary tree with NULL children included
void print(struct Node * root)
{
    if (!root) cout << "N ";
    else
    {
        cout << root->data << " "; // root
        print(root->left); // recursion in left subtree
        print(root->right); // recursion in right subtree
    }
}

int main()
{
    cout << "Welcome to C++ Pre-In Order Binary Tree Creator !" << endl << endl;

    int n; // number of elements
    cout << "Enter the number of elements in your tree : ";
    cin >> n;

    int pre[n]; // pre-order array
    cout << "Enter the pre-order traversal of your array : ";
    for (int i = 0; i < n; i++) cin >> pre[i];

    int in[n]; // in-order array
    cout << "Enter the in-order traversal of Syour array : ";
    for (int i = 0; i < n; i++) cin >> in[i];

    struct Node * root = formTree(pre, in, 0, n-1, 0, n-1);
    cout << endl << "Binary Tree was formed successfully ! The tree is : " << endl;
    print(root);

    cout << endl << endl << "Thank you for using C++ Pre-In Binary Tree Creator. Bye Bye !";
}