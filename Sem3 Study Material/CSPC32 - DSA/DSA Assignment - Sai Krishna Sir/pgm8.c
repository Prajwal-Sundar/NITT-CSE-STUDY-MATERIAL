// Program 8

#include <stdio.h>
#include <stdlib.h>

// Definition of a node
struct Node
{
    int data; // store data
    struct Node * next; // address of next node
};

// Create a node with given data
struct Node * create(int n)
{
    struct Node * node = (struct Node *) malloc(sizeof(struct Node));
    node->data = n; // set data
    node->next = NULL; // by default
    return node;
}

// Check if loop exists
int isLoop(struct Node * head)
{
    if (!head) // base case
        return 0;
    
    else if (!head->next) // single node
        return 0;
    
    struct Node * slow = head; // slow pointer
    struct Node * fast = head->next; // fast pointer

    while (fast != NULL)
    {
        if (slow->data == fast->data)
            return 1; // loop found
        
        slow = slow->next; // update slow pointer by one position
        fast = fast->next; // update fast pointer by one position
        if (fast) fast = fast->next; // update fast pointer by one more position if possible
    }

    return 0; // no loop found
}

void main()
{
    printf("Welcome to C Linked List Loop Checker !\n\n");

    struct Node * head = create(1);
    head->next = create(2);
    head->next->next = create(3);
    head->next->next->next = create(4);

    printf("Does Loop Exist in the Linked List ? Result is : %d.\n", isLoop(head));

    head->next->next->next->next = head->next;
    printf("Now Loop is made. Result is : %d.\n\n", isLoop(head));

    printf("Thank you for using C Linked List Loop Checker. Bye Bye !");
}