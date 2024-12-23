/*
    Program-3
    Given two unordered circular doubly linked lists, write a program for the printing 
common elements of them.
    @ Prajwal Sundar
*/

#include "bits/stdc++.h"
using namespace std;

// Structure of a Node
struct Node
{
    int data; // data
    struct Node * prev; // address of previous node
    struct Node * next; // address of next node

    Node(int n) // constructor
    {
        data = n; // set data
        prev = next = NULL;
    }
};

// Get a list as user input
struct Node * input()
{
    int n; // size
    cout << "Enter the list size : ";
    cin >> n;

    struct Node * head = NULL; // head pointer
    struct Node * ptr = head; // pointer

    cout << "Enter your list : ";
    for (int i = 0; i < n; i++)
    {
        int tmp; cin >> tmp; // get the number
        struct Node * node = new Node(tmp); // node

        if (i == 0) // first number
        {
            head = node; // set head
            head->next = head->prev = head; // set links
            ptr = head;
        }

        else // general case
        {
            ptr->next = node;
            node->prev = ptr; // doubly links
            node->next = head;
            head->prev = node; // circular links
            ptr = node; // update last node
        }
    }

    return head;
}

// Main Function
int main()
{
    cout << "Welcome to C++ Circular Doubly Linked Lists !" << endl << endl;

    cout << "LIST-I :" << endl;
    struct Node * headA = input();

    cout << endl << "LIST-II :" << endl;
    struct Node * headB = input();

    struct Node * ptrA = headA;
    struct Node * ptrB = headB; // pointers to lists
    int c = 0; // number of common elements

    cout << endl << "COMMON ELEMENTS : " << endl;
    do
    {
        do
        {
            if (ptrA->data == ptrB->data)
            {
                c++;
                cout << ptrA->data << " ";
            }
            ptrB = ptrB->next; // increment pointerB
        } while (ptrB != headB);
        ptrA = ptrA->next; // increment pointerA
    } while (ptrA != headA);

    if (!c) cout << "NONE";
    cout << endl << endl << "Thank you for using C++ Circular Doubly Linked Lists. Bye Bye !";
}