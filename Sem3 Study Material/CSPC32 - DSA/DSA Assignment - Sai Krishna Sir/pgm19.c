// Program 19

#include <stdio.h>
#include <stdlib.h>

// Defintion of a node
struct Node
{
    int data;
    struct Node * next;
};

// Create a new node
struct Node * create(int n)
{
    struct Node * node = (struct Node *) malloc(sizeof(struct Node));
    node->data = n; // store data
    node->next = NULL;
    return node;
}

// Display the hash table
void display(struct Node ** A, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Position %d : ", i);
        if (A[i])
            printf("%d\n", A[i]->data); // print data
        else
            printf("-\n"); // print nothing
    }
}

// Insert a new number into the hash table
void insert(struct Node ** A, int size, int c, int num)
{
    if (c >= size)
    {
        printf("Array is FULL. More elements cannot be accomodated.\n");
        return;
    }

    int key = (num % size);
    while (A[key] != NULL)
        key = (key+1) % size;
    A[key] = create(num);

    printf("%d inserted successfully into the hash table.\n");
}

// Search a number in the hash table
int search(struct Node ** A, int size, int num)
{
    int c = 0;
    int key = num;

    while (c < size)
    {
        key = key % size;
        if (A[key] && A[key]->data == num)
            return key;
        key++; c++;
    }

    return -1;
}

// Delete a number from the hash table
void delete(struct Node ** A, int size, int num)
{
    int p = search(A, size, num);
    
    if (p == -1) // element not found
    {
        printf("%d was not found in your hash table.\n", num);
        return;
    }

    else
    {
        free(A[p]); // delete the node at position p
        A[p] = NULL;
        printf("%d was successfully deleted from your hash table.\n", num);
    }
}

// Main function
void main()
{
    printf("Welcome to C Hash Table : Linear Probing \n");

    int size;
    printf("Enter the size of your hash table : ");
    scanf("%d", &size);
    printf("\n");

    struct Node ** A = (struct Node **) malloc(size * sizeof(struct Node *));
    for (int i = 0; i < size; i++)
        A[i] = NULL;

    int flag = 1;
    int c = 0;
    while (flag)
    {
        char ch;
        int num;

        printf("Enter 'I' to insert, 'D' to delete, 'S' to search, 'd' to display and 'E' to exit : ");
        scanf(" %c", &ch);

        switch(ch)
        {
            case 'I':
                printf("Enter the number you wish to insert : ");
                scanf("%d", &num);
                insert(A, size, c++, num);
                break;
            
            case 'D':
                printf("Enter the number you wish to delete : ");
                scanf("%d", &num);
                delete(A, size, num);
                c--;
                break;
            
            case 'S':
                printf("Enter the number you wish to search : ");
                scanf("%d", &num);
                int p = search(A, size, num);
                if (p == -1)
                    printf("%d was not found in your hash table.\n", num);
                else
                    printf("%d was found in your hash table at position %d.\n", num, p);
                break;
            
            case 'd':
                display(A, size);
                break;
            
            case 'E':
                flag = 0;
                break;

            default:
                printf("Invalid Choice.\n");
        }

        printf("\n");
    }

    printf("Thank you for using C Hash Table : Linear Probing. Bye Bye !");
}