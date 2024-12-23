#include <stdio.h>
#include <stdlib.h>

// Structure of a Node
struct Node
{
    int data; // data
    struct Node * left; // address of left child
    struct Node * right; // address of right child
    int s; // s-value
};

// Create a new node
struct Node * create(int n)
{
    struct Node * node = (struct Node *) malloc(sizeof(struct Node));

    node->data = n; // set data
    node->left = node->right = NULL; // leaf node by default
    node->s = 1; // s-value is 1 for a leaf

    return node;
}

// Minimum function
int min(int x, int y)
{
    return (x < y) ? x : y;
}

// Get the s-value of a node
int s(struct Node * root)
{
    if (!root)
        return 0; // NULL
    else
        return root->s;
}

// MERGE operation
struct Node * merge(struct Node * R1, struct Node * R2)
{
    if (!R1) return R2;
    if (!R2) return R1; // base cases

    struct Node * R; // final root
    struct Node * H; // returned heap

    if (R1->data < R2->data)
    {
        H = merge(R1->right, R2); // recursion
        R = R1;
    }
    else
    {
        H = merge(R1, R2->right); // recursion
        R = R2;
    }

    if (s(H) > s(R->left)) // swap and then insert onto left
    {
        struct Node * tmp = R->left;
        R->left = H; // place returned heap
        R->right = tmp;
    }
    else // insert onto right directly
        R->right = H;
    
    R->s = min(s(R->left), s(R->right)) + 1; // update s-value
    return R; // return final root
}

// Insert a new node into the leftist heap
struct Node * ins(struct Node * root, int n)
{
    struct Node * node = create(n); // create a new node
    return merge(root, node); // merge and return
}

// Delete the root of the leftist heap
struct Node * del(struct Node * root)
{
    struct Node * node = merge(root->left, root->right); // get merged of left and right
    free(root); // free memory
    return node;
}

// Display a binary tree
void display(struct Node * root)
{
    if (!root) // root is NULL
        printf("N ");
    
    else // root is not NULL
    {
        printf("%d ", root->data); // data
        display(root->left); // left subtree
        display(root->right); // right subtree
    }
}

// Search an element in an array with given range of subscripts
int search(int * arr, int L, int U, int n)
{
    for (int i = L; i <= U; i++)
        if (arr[i] == n)
            return i;
    return -1;
}

// Form a binary tree given pre-order and in-order traversals
struct Node* formTree(int pre [], int in [], int L1, int U1, int L2, int U2)
{
    if (L1 > U1) // no element here
        return NULL;
    
    struct Node * root = create(pre[L1]); // form root
    if (L1 == U1) // one element
        return root;
    
    int P = search(in, L2, U2, pre[L1]); // search root
    root->left = formTree(pre, in, L1+1, P+L1-L2, L2, P-1); // recursion in left subtree
    root->right = formTree(pre, in, P+L1-L2+1, U1, P+1, U2); // recursion in right subtree
    root->s = min(s(root->left), s(root->right)) + 1;

    return root;
}

struct Node * form(int pre [], int in [], int l)
{
    return formTree(pre, in, 0, l-1, 0, l-1);
}

// Clear the heap
void clear(struct Node * root)
{
    if (root)
    {
        clear(root->left);
        clear(root->right);
        free(root);
    }
}

// Input a full heap from the user
struct Node * input(struct Node * root, int n)
{
    int pre [n], in [n];

    printf("Enter the pre-order traversal : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pre[i]);
    
    printf("Enter the in-order traversal : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &in[i]);

    struct Node * tree = form(pre, in, n);
    return merge(root, tree);
}

// Main function
void main()
{
    printf("Welcome to C Leftist Heaps !\n\n");

    printf("The following operations are available :-\n");
    printf("1) 's' to show the leftist heap\n");
    printf("2) 'i' to insert a key into the leftist heap\n");
    printf("3) 'd' to delete the root of the leftist heap\n");
    printf("4) 'c' to clear the leftist heap\n");
    printf("5) 'I' to input a tree given pre and in order traversals and merge them into current heap\n");
    printf("6) 'e' to exit\n\n");

    struct Node * root = NULL;
    int flag = 1;
    while (flag)
    {
        char ch; // choice
        int n; // number

        switch(ch)
        {
            case 's':
                display(root);
                break;
            
            case 'i':
                printf("Enter the number you wish to insert : ");
                scanf("%d", &n);
                root = ins(root, n);
                printf("%d was inserted successfully.", n);
                break;
            
            case 'd':
                if (!root)
                    printf("Cannot delete as tree is empty.");
                else
                {
                    printf("%d was deleted successfully.", root->data);
                    root = del(root);
                }
                break;
            
            case 'c':
                clear(root);
                root = NULL;
                printf("Heap was cleared successfully.");
                break;
            
            case 'I':
                printf("Enter the number of elements you wish to insert : ");
                scanf("%d", &n);
                root = input(root, n);
                printf("The elements were inserted successfully.");
                break;
            
            case 'e':
                printf("Program Execution Terminated.");
                flag = 0;
                break;
            
            default:
                printf("Invalid Choice.");
        }

        printf("\n\n");
    }

    printf("Thank you for using C Leftist Heaps. Bye Bye !");
}

void main()
{
    struct Node * root = NULL;

    int A [] = {6, 2, 9, 8, 3, 4, 11, 18, 7, 24, 1, 5};
    for (int i = 0; i < 12; i++)
        root = ins(root, A[i]);

    display(root);
}