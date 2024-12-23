/*
    Program-7
    Give an algorithm for checking the existence of path with given sum. That means, 
given a sum, check whether there exists a path from root to any of the nodes.
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

void sum(struct Node * root, int s, string str, int * c)
{
    if (!root) return;

    s -= root->data; // reduce sum
    if (!s) // sum obtained
    {
        cout << "Sum Obtained in Path : " << str << endl;
        (*c)++; // increment count variable
    }
    
    sum(root->left, s, str+"L", c);
    sum(root->right, s, str+"R", c);
}

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

int main()
{
    cout << "Welcome to C++ Binary Tree Path Sum Checker !" << endl << endl;

    cout << "Enter the root : ";
    struct Node * root = form();

    int s; // sum
    cout << endl << "Enter the sum you wish to obtain : ";
    cin >> s;

    int c = 0; // count variable
    sum(root, s, "", &c);

    if (!c) cout << "Path with given sum does not exist.";
    else cout << "Therefore, number of paths with given sum = " << c;

    cout << endl << endl << "Thank you for using C++ Binary Tree Path Sum Checker. Bye Bye !";
}