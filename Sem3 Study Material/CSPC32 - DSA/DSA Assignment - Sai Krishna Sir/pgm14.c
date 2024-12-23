// Program 14

#include <stdio.h>
#include <stdlib.h>

// Definition of a node
struct Node
{
    int data;
    struct Node * left;
    struct Node * right;
};

// Create a node
struct Node * create(int n)
{
    struct Node * node = (struct Node *) malloc(sizeof(struct Node));
    node->data = n; // set data
    node->left = node->right = NULL; // leaf by default
    return node;
}

// Maximum of 2 variables function
int max(int x, int y)
{
    return (x > y) ? x : y;
}

// Height of a binary tree function
int height(struct Node * root)
{
    if (root == NULL)
        return -1; // to delete an extra edge traversed
    else
        return 1 + max(height(root->left), height(root->right)); // normal case
}

// Search an element in an array
int search(int * A, int L, int U, int n)
{
    for (int i = L; i <= U; i++)
        if (*(A + i) == n)
            return i; // element found
    return -1; // element not found
}

// Consturct a Tree Using Pre-Order and In-Order Traversals
struct Node * formTree(int pre [], int in [], int L1, int U1, int L2, int U2)
{
	if (L1 > U1)
		return NULL;
	
	struct Node * root = create(pre[L1]);
	if (L1 == U1)
		return root;
	
	int P = search(in, L2, U2, root->data);
	root->left = formTree(pre, in, L1+1, P+L1-L2, L2, P-1);
	root->right = formTree(pre, in, P+L1-L2+1, U1, P+1, U2);
	
	return root;
}

struct Node * form(int pre [], int in [], int l)
{
	return formTree(pre, in, 0, l-1, 0, l-1);
}

void main()
{
    printf("Welcome to C Binary Tree Height Evaluator !\n\n");

    int n; // number of nodes
    printf("Enter the number of nodes in your tree : ");
    scanf("%d", &n);

    int pre [n], in [n]; // arrays to store traversals
    printf("Enter the pre-order traversal : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pre[i]);
    printf("Enter the in-order traversal : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &in[i]);
    
    printf("Height of the Tree Generated is : %d.", height(form(pre, in, n)));
    printf("\n\nThank you for using C Binary Tree Height Evaluator. Bye Bye !");
}