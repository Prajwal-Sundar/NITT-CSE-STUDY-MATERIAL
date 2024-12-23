// Program 16

#include <stdio.h>
#include <stdlib.h>

// Structure of a tree node
struct tNode
{
    int data; // store data
    struct tNode * left; // address of left child
    struct tNode * right; // address of right child
};

// Structure of a stack node
struct sNode
{
    struct tNode * node; // store a tree node
    struct sNode * next; // address of next node
};

// Create a tree node with given data
struct tNode * CtNode(int n)
{
    struct tNode * node = (struct tNode *) malloc(sizeof(struct tNode));
    node->data = n; // set data
    node->left = node->right = NULL; // by default
    return node;
}

// Create a stack node with a given tree node
struct sNode * CsNode(struct tNode * node)
{
    struct sNode * newNode = (struct sNode *) malloc(sizeof(struct sNode));
    newNode->node = node; // set the node
    newNode->next = NULL;
    return newNode;
}

// Push a tree node into the stack
struct sNode * push(struct sNode * head, struct tNode * node)
{
    struct sNode * newNode = CsNode(node); // new node
    newNode->next = head; // set link
    head = newNode; // change address of head
    return head;
}

// Pop a tree node from the stack
struct sNode * pop(struct sNode * head)
{
    struct sNode * tmp = head; // temperory pointer
    head = head->next; // bring forward head
    free(tmp); // free memory
    return head;
}

// Iterative pre-order traversal of a tree
void pre(struct tNode * root)
{
    struct sNode * head = CsNode(root);

    while (head) // loop while head is not empty
    {
        struct tNode * ptr = head->node; // get top element
        head = pop(head); // pop top element
        printf("%d ", ptr->data);

        if (ptr->right)
            head = push(head, ptr->right); // push right child
        if (ptr->left)
            head = push(head, ptr->left); // push left child
    }
}

// Iterative in-order traversal of a tree
void in(struct tNode * root)
{
    struct sNode * head = NULL; // stack
    struct tNode * ptr = root; // pointer

    while (head || ptr)
    {
        if (ptr) // pointer is NOT NULL
        {
            head = push(head, ptr); // push pointer
            ptr = ptr->left; // go left
        }

        else // pointer is NULL
        {
            ptr = head->node; // point to topmost element
            head = pop(head); // pop topmost element
            printf("%d ", ptr->data);
            ptr = ptr->right; // go right
        }
    }
}

// Iterative post-order traversal of a tree
void post(struct tNode * root)
{
    struct sNode * head = NULL; // stack
    struct tNode * ptr = root; // pointer

    while (head || ptr)
    {
        if (ptr) // pointer is NOT NULL
        {
            if (ptr->right)
                head = push(head, ptr->right); // push right child
            head = push(head, ptr); // push root
            ptr = ptr->left; // go left
        }

        else // pointer is NULL
        {
            ptr = head->node; // point to topmost element
            head = pop(head); // pop topmost element

            if ((ptr->right) && (head) && (ptr->right->data == head->node->data))
            {
                head = pop(head); // pop right child
                head = push(head, ptr); // push root
                ptr = ptr->right; // go right
            }

            else
            {
                printf("%d ", ptr->data); // print data
                ptr = NULL; // set pointer to NULL
            }
        }
    }
}

// Get binary tree as input from the user
struct tNode * form()
{
    int n; // root data
    scanf("%d", &n);
    struct tNode * root = CtNode(n); // create node with given data

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

void main()
{
    printf("Welcome to C Binary Tree Iterative Traversals !\n\n");

    printf("Enter root value : ");
    struct tNode * root = form();
    printf("\n");

    printf("Pre-Order Traversal : ");
    pre(root);
    printf("\nIn-Order Traversal : ");
    in(root);
    printf("\nPost-Order Traversal : ");
    post(root);

    printf("\n\nThank you for using C Binary Tree Iterative Traversals. Bye Bye !");
}