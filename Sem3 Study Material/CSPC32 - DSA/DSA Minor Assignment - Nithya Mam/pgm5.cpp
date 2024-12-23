/*
    Program-5
    Given a circular linked list with even and odd numbers, write a program to  make 
changes to the list in such a way that all even numbers appear at the beginning.
    @ Prajwal Sundar
*/

#include "bits/stdc++.h"
using namespace std;

// Structure of a Linked List Node
struct Node
{
    int data; // data
    struct Node * next; // link to next node

    Node(int n) // constructor
    {
        data = n; // set data
        next = NULL;
    }
};

// Modify list such that all even numbers appear first
struct Node * modify(struct Node * head)
{
    struct Node * odd = NULL;
    struct Node * oddPtr = odd; // odd numbers

    struct Node * even = NULL;
    struct Node * evenPtr = even; // even numbers

    struct Node * ptr = head;
    do
    {
        if (ptr->data % 2) // odd number encountered
        {
            if (odd)
            {
                oddPtr->next = ptr;
                oddPtr = ptr; // increment odd pointer
            }

            else // first odd number
                odd = oddPtr = ptr;
        }

        else // even number encountered
        {
            if (even)
            {
                evenPtr->next = ptr;
                evenPtr = ptr; // increment even pointer
            }

            else // first even number
                even = evenPtr = ptr;
        }

        ptr = ptr->next;
    } while (ptr != head);

    if (even && odd) // at least one of both odd and even exist
    {
        evenPtr->next = odd;
        oddPtr->next = even;
        return even; // even comes first
    }

    else if (even) // only even numbers exist
    {
        evenPtr->next = even; // circular link
        return even;
    }

    else if (odd) // only odd numbers exist
    {
        oddPtr->next = odd; // circular link
        return odd;
    }

    else // no numbers at all
        return NULL;
}

// Display Circular Linked List
void display(struct Node * head)
{
    if (!head)
    {
        cout << "EMPTY";
        return;
    }

    struct Node * ptr = head;
    do
    {
        cout << ptr->data << " ";
        ptr = ptr->next;
    } while (ptr != head);
}

// Main Function
int main()
{
    cout << "Welcome to C++ Circular Linked Lists !" << endl << endl;

    int n; // size of linked list
    cout << "Enter the number of elements in your linked list : ";
    cin >> n;

    struct Node * head = NULL; // head of linked list
    struct Node * ptr = head; // pointer

    cout << "Enter your list : ";
    for (int i = 0; i < n; i++)
    {
        int tmp; cin >> tmp;
        struct Node * node = new Node(tmp); // node

        if (ptr)
        {
            ptr->next = node; // insert
            ptr = node; // move pointer
        }

        else
        {
            head = node; // set head
            ptr = head; // set pointer
        }
    }

    ptr->next = head; // establish circular link
    head = modify(head); // perform modifications

    cout << "Modified List : ";
    display(head);
    cout << endl << endl << "Thank you for using C++ Circular Linked Lists. Bye Bye !";
}