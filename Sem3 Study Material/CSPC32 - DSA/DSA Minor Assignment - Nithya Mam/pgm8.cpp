/*
    Program-8
    Given a tree with a special property where leaves are represented with ‘L’ and 
internal node with ‘I’. Also, assume that each node has either 0 or 2 children. Given 
preorder traversal of this tree, write a program to construct the tree and display it 
in the tree format as shown below.
    @ Prajwal Sundar
*/

#include "bits/stdc++.h"
using namespace std;

// Structure of a Binary Tree Node
struct Node
{
    string data; // data
    struct Node * left; // address of left child
    struct Node * right; // address of right child

    Node(string ch) // constructor
    {
        data = ch; // set data
        left = right = NULL;
    }
};

// Return tree of a given string
struct Node * form(string str)
{
    struct Node * root = new Node("-");
    bool mode = false; // left = false, right = true
    stack<struct Node *> S; // stack
    S.push(root);

    int len = str.size();
    for (int i = 0; i < len; i++)
    {
        if (str[i] == 'I')
        {
            struct Node * node = new Node("I");

            if (!mode) S.top()->left = node;
            else S.top()->right = node; // push based on mode

            S.push(node); // push newly formed internal node
            mode = false; // reset mode
        }

        else if (str[i] == 'L')
        {
            if (!mode)
            {
                S.top()->left = new Node("L");
                mode = true; // change mode to right
            }

            else
            {
                S.top()->right = new Node("L");
                S.pop(); // pop topmost node
            }
        }
    }

    return root->left;
}

// Get height of the binary tree
int height(struct Node * root)
{
    if (!root) return -1;
    else return 1 + max(height(root->left), height(root->right));
}

// Fill Matrix Function
void fill(string ** M, struct Node * root, int r, int c, int h)
{
    M[r][c] = root->data;
    int n = pow(2, h-1);

    if (root->left) // recursion in left-subtree
    {
        int i, j, x;
        for (i = r+1, j = c-1, x = 0; x < n; i++, j--, x++) M[i][j] = "/";
        fill(M, root->left, i, j, h-1);
    }

    if (root->right) // recursion in right-subtree
    {
        int i, j, x;
        for (i = r+1, j = c+1, x = 0; x < n; i++, j++, x++) M[i][j] = "\\";
        fill(M, root->right, i, j, h-1);
    }
}

// Display a tree
void display(struct Node * root)
{
    int h = height(root);

    int r = pow(2, h) + h; // number of rows in matrix
    int c = pow(2, h+1) + (2*h) - 1; // number of columns in matrix

    string ** M = new string * [r]; // string matrix to store tree
    for (int i = 0; i < r; i++)
    {
        M[i] = new string [c];
        for (int j = 0; j < c; j++) M[i][j] = " "; // empty string by default
    }

    fill(M, root, 0, r-1, h); // fill matrix function
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++) cout << M[i][j];
        cout << endl; // next line
    }
}

// Main Function
int main()
{
    cout << "Welcome to C++ Trees !" << endl << endl;

    string str;
    cout << "Enter your pre-order string : ";
    cin >> str;

    struct Node * root = form(str); // form tree
    cout << "Your Tree is : " << endl;
    display(root);

    cout << endl << "Thank you for using C++ Trees. Bye Bye !";
}