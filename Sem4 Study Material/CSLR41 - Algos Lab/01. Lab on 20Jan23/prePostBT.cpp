/*
    CSLR41 Algorithms Laboratory
    Prajwal Sundar - Roll Number 106121092
    Program-3
    Form a binary tree using the given pre-order and post-order traversals
*/

#include "bits/stdc++.h"
using namespace std;

// Structure of a Binary Tree Node
struct Node
{
    char data; // data
    struct Node * left, * right; // left and right children

    Node(char n) // constructor
    {
        data = n; // set data
        left = right = NULL; // leaf node by default
    }
};

// Search an element in a sorted array between two given positions
int search(char * A, char n, int L, int U)
{
    for (int i = L; i <= U; i++)
        if (A[i] == n) return i; // element found
    return -1; // element not found
}

// Construct a binary tree using given pre and post orders
struct Node * formTree(char pre [], char post [], int L1, int U1, int L2, int U2)
{
    if (L1 > U1) return NULL;

    struct Node * root = new Node(pre[L1]);
    if (L1 == U1) return root;

    if (pre[L1+1] == post[U2-1]) // full binary tree not possible, make it left only
        root->left = formTree(pre, post, L1+1, U1, L2, U2-1);
    
    else
    {
        int P1 = search(post, pre[L1+1], L2, U2);
        int P2 = search(pre, post[U2-1], L1, U1);
        root->left = formTree(pre, post, L1+1, P2-1, L2, P1); // form left subtree
        root->right = formTree(pre, post, P2, U1, P1+1, U2-1); // form right subtree
    }
    
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
    cout << "Welcome to C++ Pre-Post Order Binary Tree Creator !" << endl << endl;

    int n; // number of elements
    cout << "Enter the number of elements in your tree : ";
    cin >> n;

    char pre[n]; // pre-order array
    cout << "Enter the pre-order traversal of your array : ";
    for (int i = 0; i < n; i++) cin >> pre[i];

    char post[n]; // post-order array
    cout << "Enter the post-order traversal of your array : ";
    for (int i = 0; i < n; i++) cin >> post[i];

    struct Node * root = formTree(pre, post, 0, n-1, 0, n-1);
    cout << endl << "Binary Tree was formed successfully ! The tree is : " << endl;
    print(root);

    cout << endl << endl << "Thank you for using C++ Pre-Post Binary Tree Creator. Bye Bye !";
}