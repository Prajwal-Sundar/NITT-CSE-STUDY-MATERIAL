// Program 1

#include <stdio.h>
#include <stdlib.h>

// Structure of a node
struct Node
{
    int data; // store data
    struct Node * next; // address of next node
};

// Create a node wih given data
struct Node * create(int n)
{
    struct Node * node = (struct Node *) malloc(sizeof(struct Node));
    node->data = n; // set data
    node->next = NULL; // by default
    return node;
}

// Push an element into the stack
struct Node * push(struct Node * head, int n)
{
    struct Node * newNode = create(n); // create a new node
    newNode->next = head; // new link
    head = newNode; // change address of head
    return head;
}

// Pop an element from the stack
struct Node * pop(struct Node * head)
{
    struct Node * tmp = head; // temperory pointer
    head = head->next; // bring head address forward
    free(tmp); // free memory
    return head;
}

// Display the stack
void display(struct Node * head)
{
    if (!head) // empty stack
        printf("Your Stack : EMPTY");
    else
    {
        struct Node * ptr = head; // pointer
        while (ptr)
        {
            printf("%d ", ptr->data); // print data
            ptr = ptr->next; // bring pointer forward
        }
    }
}

void main()
{
    printf("Welcome to C Stack as a Linked List !\n\n");

    int flag = 1; // flag variable
    struct Node * head = NULL; // stack

    while (flag)
    {
        char ch; // choice
        int n; // number to push

        printf("Enter 'P' to push, 'p' to pop, 'D' to display and 'E' to exit : ");
        scanf(" %c", &ch);

        switch(ch)
        {
            case 'P': // push operation
                printf("Enter the element you wish to push : ");
                scanf("%d", &n);
                head = push(head, n);
                printf("%d was pushed successfully.", n);
                break;
            
            case 'p': // pop operation
                if (head)
                {
                    printf("%d was popped successfully.", head->data);
                    head = pop(head);
                }
                else
                    printf("Error : STACK UNDERFLOW");
                break;
            
            case 'D': // dispaly linked list
                display(head);
                break;
            
            case 'E': // exit from code
                flag = 0;
                printf("Program Execution Terminated.");
                break;
            
            default:
                printf("Invalid Choice.");
        }

        printf("\n\n");
    }

    printf("Thank you for using Stack as a Linked List. Bye Bye !");
}