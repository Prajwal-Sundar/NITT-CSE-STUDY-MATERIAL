// Program 7

#include <stdio.h>
#include <stdlib.h>

// Definition of a node
struct Node
{
    int data; // data
    struct Node * next; // address to next node
};

// Create a node with given data
struct Node * create(int n)
{
    struct Node * node = (struct Node *) malloc(sizeof(struct Node));
    node->data = n; // store data
    node->next = NULL; // by default
    return node;
}

// Function to reverse a linked list
struct Node * rev(struct Node * head)
{
    struct Node * prev = NULL;
    struct Node * curr = head;
    struct Node * next = NULL;

    while (curr != NULL)
    {
        next = curr->next; // store next node
        curr->next = prev; // reverse link
        prev = curr;
        curr = next; // bring forward
    }

    head = prev; // new head
    return head; // return head
}

// Push an element (in front) into the linked list
struct Node * push(struct Node * head, int n)
{
    struct Node * node = create(n); // create node
    node->next = head; // push
    head = node; // bring back head pointer
    return head;
}

void display(struct Node * head)
{
    if (!head) // empty linked list
        printf("EMPTY");
    
    else
    {
        struct Node * ptr = head; // pointer to traverse
        while (ptr != NULL)
        {
            printf("%d ", ptr->data); // print data
            ptr = ptr->next; // update pointer
        }
    }
}

void main()
{
    printf("Welcome to C Linked Lists !\n\n");

    struct Node * head = NULL;
    int flag = 1;

    while (flag)
    {
        char ch; // choice
        int n; // element to insert

        printf("Enter 'P' to push, 'D' to display, 'R' to reverse and 'E' to exit : ");
        scanf(" %c", &ch); // get choice from user

        switch(ch)
        {
            case 'P': // push an element into the linked list
                printf("Enter the element you wish to push : ");
                scanf("%d", &n);
                head = push(head, n);
                printf("%d was pushed successfully.", n);
                break;
            
            case 'D': // display the linked list
                printf("Your Linked List : ");
                display(head);
                break;
            
            case 'R': // reverse the linked list
                head = rev(head);
                printf("Linked List was reversed successfully.");
                break;
            
            case 'E': // exit the program loop
                flag = 0;
                printf("Program Execution Terminatied.");
                break;
            
            default: // invalid choice
                printf("Invalid Choice.");
        }

        printf("\n\n");
    }

    printf("Thank you for using C Linked Lists. Bye Bye !");
}