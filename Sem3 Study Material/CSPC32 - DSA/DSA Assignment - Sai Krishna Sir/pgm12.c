// Program 12

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Definition of a tree node
struct Node
{
    int data;
    struct Node * left;
    struct Node * right;
};

// Create a binary tree node with given data
struct Node * create(int n)
{
    struct Node * node = (struct Node *) malloc(sizeof(struct Node));
    node->data = n; // set data
    node->left = node->right = NULL; // leaf node by default
    return node;
}

// Check if a given tree is a BST or not
int isBST(struct Node * root, int min, int max)
{
    if (root == NULL) // null reached
        return 1;
    
    int rootChk = (root->data > min) && (root->data < max); // check if root satisfies condition
    int leftChk = isBST(root->left, min, root->data); // check if left subtree is a BST or not
    int rightChk = isBST(root->right, root->data, max); // check if right subtree is a BST or not

    return (rootChk && leftChk && rightChk); // all 3 conditions must satisfy
}

int check(struct Node * root)
{
    return isBST(root, INT_MIN, INT_MAX); // default minimum and maximum limits
}

// Get binary tree as input from the user
struct Node * form()
{
    int n; // root data
    scanf("%d", &n);
    struct Node * root = create(n); // create node with given data

    int l, r; // do left and right subtrees exist or not
    printf("Does %d have a left child ? Enter 0/1 : ", n);
    scanf("%d", &l);
    if (l)
    {
        printf("Enter the left child of %d : ", n);
        root->left = form(); // left subtree
    }
    printf("Does %d have a right child ? Enter 0/1 : ", n);
    scanf("%d", &r);
    if (r)
    {
        printf("Enter the right child of %d : ", n);
        root->right = form(); // right subtree
    }
    
    return root;
}

// In-Order Traversal of a Binary Tree
void in(struct Node * root)
{
    if (root)
    {
        in(root->left); // left
        printf("%d ", root->data); // root
        in(root->right); // right
    }
}

void main()
{
    printf("Welcome to C Binary Search Tree Checker !\n\n");

    printf("Enter root value : ");
    struct Node * root = form();
    printf("\n");
    
    printf("In-Order Traversal : ");
    in(root);

    if (root)
        printf("\nThe tree is a binary search tree.");
    else
        printf("\nThe tree is not a binary search tree.");
    
    printf("\n\nThank you for using C Binary Search Tree checker. Bye Bye !");
}