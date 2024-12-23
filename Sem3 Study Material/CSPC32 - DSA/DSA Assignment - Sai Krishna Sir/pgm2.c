// Program 2

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

// Enqueue an element into the queue
struct Node * enqueue(struct Node * head, int n)
{
    struct Node * node = create(n); // create new node
    if (!head) // empty queue
        return node;
    
    struct Node * ptr = head; // pointer
    while (ptr->next)
        ptr = ptr->next; // loop till penultimate node
    ptr->next = node; // enqueue at last

    return head;
}

// Dequeue an element from the queue
struct Node * dequeue(struct Node * head)
{
    struct Node * tmp = head; // temperory pointer
    head = head->next; // bring head address forward
    free(tmp); // free memory
    return head;
}

// Display the queue
void display(struct Node * head)
{
    if (!head) // empty queue
        printf("Your Queue : EMPTY");
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
    printf("Welcome to C Queue as a Linked List !\n\n");

    int flag = 1; // flag variable
    struct Node * head = NULL; // queue

    while (flag)
    {
        char ch; // choice
        int n; // number to push

        printf("Enter 'E' to enqueue, 'D' to dequeue, 'd' to display and 'e' to exit : ");
        scanf(" %c", &ch);

        switch(ch)
        {
            case 'E': // enqueue operation
                printf("Enter the element you wish to enqueue : ");
                scanf("%d", &n);
                head = enqueue(head, n);
                printf("%d was enqueued successfully.", n);
                break;
            
            case 'D': // dequeue operation
                if (head)
                {
                    printf("%d was dequeued successfully.", head->data);
                    head = dequeue(head);
                }
                else
                    printf("Error : QUEUE UNDERFLOW");
                break;
            
            case 'd': // dispaly linked list
                display(head);
                break;
            
            case 'e': // exit from code
                flag = 0;
                printf("Program Execution Terminated.");
                break;
            
            default:
                printf("Invalid Choice.");
        }

        printf("\n\n");
    }

    printf("Thank you for using Queue as a Linked List. Bye Bye !");
}