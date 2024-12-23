// Program 6

#include <stdio.h>
#include <stdlib.h>

// Structure of a node
struct Node
{
    int data; // number
    struct Node * next; // address of next node
};

// Create a node with given data
struct Node * create(int n)
{
    struct Node * node = (struct Node *) malloc(n * sizeof(struct Node));
    node->data = n; // set data
    node->next = NULL; // by default 
    return node;
}

// Get middle node of a linked list
void middle(struct Node * head)
{
    if (!head) // empty list
    {
        printf("List is Empty.");
        return;
    }

    struct Node * slow = head; // slow pointer
    struct Node * fast = head; // fast pointer

    // Loop
    while (1)
    {
        if (!fast->next) // odd termination case
        {
            printf("The middle node of your linked list is %d.", slow->data);
            return;
        }

        else if (!fast->next->next) // even termination case
        {
            printf("The middle nodes of your linked list are %d and %d.", slow->data, slow->next->data);
            return;
        }

        else // other cases
        {
            slow = slow->next; // forward by one position
            fast = fast->next->next; // forward by two positions
        }
    }
}

// Push an element into the beginning of a linked list
struct Node * push(struct Node * head, int n)
{
    struct Node * node = create(n); // create a node
    node->next = head; // new link
    head = node; // change head address to new node
    return head;
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
    printf("Welcome to C Middle Node Locator !\n\n");

    struct Node * head = NULL; // linked list
    int flag = 1;
    while (flag)
    {
        int ch; // choice
        int n; // data
        
        printf("Enter 'P' to push an element, 'D' to display the linked list, 'M' to locate middle node and 'E' to exit : ");
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
            
            case 'M':
                middle(head);
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

    printf("Thank you for using C Middle Node Locator. Bye Bye !");
}