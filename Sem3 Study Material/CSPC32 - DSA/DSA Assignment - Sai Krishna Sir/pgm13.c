// Program 13

#include <stdio.h>
#include <stdlib.h>

// Definition of a tree node
struct Node
{
    int data;
    struct Node * left;
    struct Node * right;
};

// Create a binary tree node
struct Node * create(int n)
{
    struct Node * node = (struct Node *) malloc(sizeof(struct Node));
    node->data = n; // set data
    node->left = node->right = NULL; // leaf node by default
    return node;
}

// Sort a given array using bubble sort
void sort(int * A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (A[j] > A[j+1])
            {
                int tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp; // swap adjacent positions
            }
        }
    }
}

// Search for an element in an array
int search(int A[], int l, int n)
{
    for (int i = 0; i < l; i++)
        if (A[i] == n)
            return i; // element found
    return -1; // element not found
}

struct Node * formTree(int pre [], int in [], int l, int L1, int U1, int L2, int U2)
{
    if (L1 > U1) // null position
        return NULL;
    
    struct Node * root = create(pre[L1]); // form root
    if (L1 == U1) // leaf node
        return root;
    
    int P = search(in, l, root->data);
    root->left = formTree(pre, in, l, L1+1, P+L1-L2, L2, P-1);
    root->right = formTree(pre, in, l, P+L1-L2+1, U1, P+1, U2);

    return root;
}

// Construct a binary tree using pre-order and in-order traversals
struct Node * form(int pre [], int in [], int l)
{
    return formTree(pre, in, l, 0, l-1, 0, l-1);
}

// Print the post-order traversal of a binary tree
void post(struct Node * root)
{
    if (root != NULL)
    {
        post(root->left); // left
        post(root->right); // right
        printf("%d ", root->data); // root
    }
}

void main()
{
    printf("Welcome to C BST from PreOrder Generator !\n\n");

    int n;
    printf("Enter the number of elements in the BST : ");
    scanf("%d", &n);

    int pre [n], in[n]; // arrays to store traversals
    printf("Enter the pre-order traversal of the BST : ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pre[i]);
        in[i] = pre[i]; // first copy pre-order as such into in-order
    }

    sort(in, n); // sort the pre-order traversal in ascending order to get in-order
    struct Node * root = form(pre, in, n);

    printf("In-Order Traversal : ");
    for (int i = 0; i < n; i++)
        printf("%d ", in[i]);
    
    printf("\nPost-Order Traversal : ");
    post(root);

    printf("\n\nThank you for using C BST from Pre-Order Generator. Bye Bye !");
}