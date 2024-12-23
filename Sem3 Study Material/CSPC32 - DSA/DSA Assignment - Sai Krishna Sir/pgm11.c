// Program 11

#include <stdio.h>
#include <stdlib.h>

// Structure of a node
struct Node
{
    int data; // store data
    struct Node * next; // address of next node
    int visited; // node is visited or not
};

// Create a node
struct Node * create(int n)
{
    struct Node * node = (struct Node *) malloc(sizeof(struct Node));
    node->data = n; // set data
    node->next = NULL; // by default
    node->visited = 0; // not visited by default
}

// Locate the intersection point
int getPoint(struct Node * A, struct Node * B)
{
    struct Node * ptr = A; // pointer to first list
    while (ptr)
    {
        ptr->visited = 1; // mark visited
        ptr = ptr->next; // move pointer forward
    }

    ptr = B; // pointer to second list
    while (ptr)
    {
        if (ptr->visited) // intersection point reached
            return ptr->data;
        ptr = ptr->next; // move pointer forward
    }

    return -1; // no intersection point found
}

// Display a linked list
void display(struct Node * head)
{
    struct Node * ptr = head; // pointer to head
    while (ptr)
    {
        printf("%d ", ptr->data); // print data
        ptr = ptr->next; // increment pointer
    }
}

// Main function
void main()
{
    printf("Welcome to C Linked List Intersection Locator !\n\n");

    struct Node * A = create(3), * ptr = A;
    ptr->next = create(6); ptr = ptr->next;
    ptr->next = create(9); ptr = ptr->next;
    ptr->next = create(15); ptr = ptr->next;
    struct Node * point = ptr;
    ptr->next = create(30); ptr = ptr->next; // fill first list

    struct Node * B = create(5); ptr = B;
    ptr->next = create(10); ptr = ptr->next;
    ptr->next = point; ptr = ptr->next; // fill second list

    printf("List 1 : ");
    display(A); // print the first list
    printf("\nList 2 : ");
    display(B); // print the second list

    printf("\nThe intersection point of the lists is : %d.\n", getPoint(A, B));
    printf("\nThank you for using C Linked List Intersection Locator. Bye Bye !");
}