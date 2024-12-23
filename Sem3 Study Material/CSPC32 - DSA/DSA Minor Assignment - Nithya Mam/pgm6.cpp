/*
    Program-6
    Given a BST and two integers (minimum and maximum integers) as parameters, 
write a program to remove (prune) elements that are not within that range. 
    @ Prajwal Sundar
*/

#include "bits/stdc++.h"
using namespace std;

// Structure of a Binary Tree Node
struct Node
{
    int data; // data
    struct Node * left; // address of left child
    struct Node * right; // address of right child

    Node(int n) // constructor
    {
        data = n;
        left = right = NULL;
    }
};

struct Node * form()
{
    int n; cin >> n;
    struct Node * root = new Node(n);

    int l; // left child existence
    cout << "Does " << n << " have a left child ? Enter 0/1 : ";
    cin >> l;

    if (l)
    {
        cout << "Enter the left child of " << n << " : ";
        root->left = form(); // left subtree
    }

    int r; // right child existence
    cout << "Does " << n << " have a right child ? Enter 0/1 : ";
    cin >> r;

    if (r)
    {
        cout << "Enter the right child of " << n << " : ";
        root->right = form(); // right subtree
    }

    return root;
}

// Prune a given BST
struct Node * prune(struct Node * root, int L, int U)
{
    if (!root) return NULL;

    root->left = prune(root->left, L, U); // prune left subtree
    root->right = prune(root->right, L, U); // prune right subtree

    // Now come to root

    if (root->data < L) // lesser than minimum element
    {
        struct Node * right = root->right;
        delete root;
        return right;
    }

    else if (root->data > U) // greater than maximum element
    {
        struct Node * left = root->left;
        delete root;
        return left;
    }

    else // in range
        return root;
}

// Binary Tree Display Function
void display(struct Node * root)
{
    if (!root) cout << "N ";
    else
    {
        cout << root->data << " "; // root
        display(root->left); // left
        display(root->right); // right
    }
}

// Main Function
int main()
{
    cout << "Welcome to C++ Binary Tree Pruner !" << endl << endl;

    cout << "Enter root value : ";
    struct Node * root = form(); // get binary tree as user input

    int L, U; // lower and upper limits
    cout << endl << "Enter the range you wish to retain : ";
    cin >> L >> U;

    root = prune(root, L, U); // prune BST
    cout << "Pruned BST : ";
    display(root);

    cout << endl << endl << "Thank you for using C++ Binary Tree Pruner. Bye Bye !";
}