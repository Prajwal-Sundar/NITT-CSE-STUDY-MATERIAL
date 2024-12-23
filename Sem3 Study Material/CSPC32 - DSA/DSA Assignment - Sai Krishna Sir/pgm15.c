// Program 15

#include <stdio.h>
#include <stdlib.h>

// Structure of a tree node
struct tNode
{
    int data; // store data
    struct tNode * left; // address of left child
    struct tNode * right; // address of right child
};

// Structure of a queue node
struct qNode
{
    struct tNode * node; // store node
    struct qNode * next; // address to next node
};

// Create a tNode with given data
struct tNode * CtNode(int n)
{
    struct tNode * node = (struct tNode *) malloc(sizeof(struct tNode));
    node->data = n; // set given data
    node->left = node->right = NULL; // by default
    return node;
}

// Create a qNode with a given tNode
struct qNode * CqNode(struct tNode * node)
{
    struct qNode * newNode = (struct qNode *) malloc(sizeof(struct qNode));
    newNode->node = node; // set tNode
    newNode->next = NULL; // by default
    return newNode;
}

// Enqueue function
struct qNode * enqueue(struct qNode * head, struct tNode * node)
{
    struct qNode * newNode = CqNode(node); // create a new qNode
    if (!head) // empty queue
        return newNode;
    
    struct qNode * ptr = head; // pointer
    while (ptr->next)
        ptr = ptr->next; // loop till last node
    ptr->next = newNode; // enqueue at last

    return head;
}

// Dequeue function
struct qNode * dequeue(struct qNode * head)
{
    if (!head) // empty queue - underflow
        return head;
    
    struct qNode * tmp = head; // temperory pointer
    head = head->next; // dequeue
    free(tmp); // free memory

    return head;
}

// Function to perform level order traversal
void levelOrder(struct tNode * root)
{
    struct qNode * head = CqNode(root); // enqueue root
    head->next = CqNode(NULL); // enqueue NULL
    int l = 0; // level 0
    printf("Level 0 : ");

    while (1) // loop elements
    {
        struct tNode * ptr = head->node; // store front element
        head = dequeue(head); // dequeue front position

        if (!head) // queue is empty
            break; // end loop

        if (ptr) // NOT NULL
        {
            printf("%d ", ptr->data); // print data
            if (ptr->left)
                head = enqueue(head, ptr->left); // enqueue left child
            if (ptr->right)
                head = enqueue(head, ptr->right); // enqueue right child
        }

        else // NULL
        {
            head = enqueue(head, NULL); // enquue a NULL position
            printf("\nLevel %d : ", ++l); // print new line for new level
        }
    }
}

// Find the position of an element in an array
int search(int arr [], int L, int U, int n)
{
    for (int i = L; i <= U; i++)
        if (arr[i] == n)
            return i; // element found, return position
    return -1; // element not found
}

// Form a binary tree using given post order and in order traversals
struct tNode * formTree(int post [], int in [], int L1, int U1, int L2, int U2)
{
    if (L1 > U1)
		return NULL;
	
	struct tNode * root = CtNode(post[U1]);
	if (L1 == U1)
		return root;
	
	int P = search(in, L2, U2, root->data);
	root->left = formTree(post, in, L1, P+L1-L2-1, L2, P-1);
	root->right = formTree(post, in, P+L1-L2, U1-1, P+1, U2);
	
	return root;
}

struct tNode * form(int post [], int in [], int l)
{
    return formTree(post, in, 0, l-1, 0, l-1); // set default limits
}

// Main function
void main()
{
    printf("Welcome to C Level Order Traversal !\n\n");

    int n; // number of elements
    printf("Enter the number of elements in your tree : ");
    scanf("%d", &n);

    int post [n];
    int in [n]; // array to store traversals
    printf("Enter the post order traversal of your tree : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &post[i]);
    printf("Enter the in order traversal of your tree : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &in[i]);
    
    printf("\nThe Level Order Traversal of your tree is as follows :-\n");
    levelOrder(form(post, in, n));

    printf("\n\nThank you for using C Level Order Traversal. Bye Bye !");
}