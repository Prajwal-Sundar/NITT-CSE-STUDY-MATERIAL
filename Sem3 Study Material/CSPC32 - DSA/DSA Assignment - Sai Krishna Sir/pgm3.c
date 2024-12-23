// Program 3

#include <stdio.h>
#include <stdlib.h>

// Structure of a node
struct Node
{
    int data; // store data
    struct Node * next; // address of next node
};

// Create a node with given data n
struct Node * create(int n)
{
    struct Node * node = (struct Node *) malloc(sizeof(struct Node));
    node->data = n; // set data
    node->next = NULL; // by default
    return node;
}

// Enqueue operation
struct Node * enqueue(struct Node * head, int n)
{
    struct Node * node = create(n); // create a new node
    if (!head) // empty queue
        return node;
    
    struct Node * ptr = head; // pointer
    while (ptr->next)
        ptr = ptr->next; // loop till last node
    ptr->next = node; // enqueue at last

    return head;
}

// Dequeue operation
struct Node * dequeue(struct Node * head)
{
    if (!head) // queue underflow
        return head;
    
    struct Node * tmp = head; // temperory pointer
    head = head->next; // bring head address forward
    free(tmp); // free memory

    return head;
}

// Push operation into stack using enqueue
struct Node * push(struct Node * head, int n)
{
    struct Node * node = create(n); // create new node
    struct Node * ptr = head; // pointer

    while (ptr)
    {
        node = enqueue(node, ptr->data); // enqueue
        ptr = ptr->next;
    }

    head = node; // change head address
    return head;
}

// Pop operation from stack using dequeue
struct Node * pop(struct Node * head)
{
    return dequeue(head); // both are same operations
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
    printf("Welcome to C Stack using Queue !\n\n");

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

    printf("Thank you for using Stack using Queue. Bye Bye !");
}