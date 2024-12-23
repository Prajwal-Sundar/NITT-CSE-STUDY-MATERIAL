// Program 9

#include <stdio.h>
#include <stdlib.h>

// Definition of a node
struct Node
{
    int data; // data
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

// Push an element into a given linked list
struct Node * push(struct Node * head, int n)
{
    struct Node * node = create(n); // create a node
    node->next = head; // new link
    head = node; // change address of head node
    return head;
}

// Check if linked list is palindrome or not
int check(struct Node * head)
{
    struct Node * rev = NULL; // store reverse of given linked list
    struct Node * ptr = head; // pointer

    while (ptr)
    {
        rev = push(rev, ptr->data); // push in opposite direction
        ptr = ptr->next; // increment pointer
    }

    struct Node * P1 = head;
    struct Node * P2 = rev; // pointers to both lists
    while (P1 && P2)
    {
        if (P1->data != P2->data) // data don't match
            return 0; // not a palindrome
        
        P1 = P1->next;
        P2 = P2->next; // update pointers
    }

    return 1; // is palindrome
}

// Display the linked list
void display(struct Node * head)
{
    if (!head) // empty list
    {
        printf("List is empty.");
        return;
    }

    struct Node * ptr = head; // pointer
    printf("Your Linked List : ");

    while (ptr)
    {
        printf("%d ", ptr->data); // print data
        ptr = ptr->next; // increment pointer position by one
    }
}

// Main function
void main()
{
    printf("Welcome to C Palindrome Checker !\n\n");

    struct Node * head = NULL; // linked list
    int flag = 1;
    while (flag)
    {
        int ch; // choice
        int n; // data
        
        printf("Enter 'P' to push an element, 'D' to display the linked list, 'C' to check if palindrome and 'E' to exit : ");
        scanf(" %c", &ch);

        switch(ch)
        {
            case 'P':
                printf("Enter the element you want to push : ");
                scanf("%d", &n);
                head = push(head, n);
                printf("%d was succesfully pushed into the linked list.", n);
                break;
            
            case 'D':
                display(head);
                break;
            
            case 'C':
                if (check(head))
                    printf("It is a palindrome.");
                else
                    printf("It is not a palindrome.");
                break;
            
            case 'E':
                flag = 0;
                printf("Program Execution Terminated.");
                break;
            
            default:
                printf("Invalid Choice.");
        }

        printf("\n\n");
    }

    printf("Thank you for using C Palindrome Checker. Bye Bye !");
}