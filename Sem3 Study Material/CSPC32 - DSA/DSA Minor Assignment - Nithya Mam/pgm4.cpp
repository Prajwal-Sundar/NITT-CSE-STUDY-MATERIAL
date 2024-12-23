/*
    Program-4
    Given a singly linked list, write a program to find  
        (i) the last element from the beginning whose n%k == 0,  
        (ii)  the first from the end whose n%k == 0, 
    where n is the number of  elements in the list and k is an integer constant. For example, 
    if n = 19 and k = 3 then  (i) 18th node should be returned. (ii) 16th node should be returned.
    @ Prajwal Sundar
*/

#include "bits/stdc++.h"
using namespace std;

// Structure of a Linked List Node
struct Node
{
    int data; // data
    struct Node * next; // address to next node

    Node(int n) // constructor
    {
        data = n; // set data
        next = NULL; // set next pointer as NULL
    }
};

// Reverse a Linked List
struct Node * rev(struct Node * head)
{
    if (!head) return NULL;

    struct Node * prev = NULL;
    struct Node * curr = head;
    struct Node * next = NULL; // 3 pointer approach

    while (curr)
    {
        next = curr->next;
        curr->next = prev; // reverse link

        prev = curr;
        curr = next; // update pointers
    }

    return prev; // new head
}

// Main Function
int main()
{
    cout << "Welcome to C++ Singly Linked Lists !" << endl << endl;

    int n; // number of elements
    cout << "Enter the number of elements in your linked list : ";
    cin >> n;

    struct Node * head = NULL; // head of linked list
    struct Node * ptr = head; // pointer to head
    cout << "Enter your linked list : ";

    for (int i = 0; i < n; i++)
    {
        int tmp; cin >> tmp;
        struct Node * node = new Node(tmp);

        if (ptr)
        {
            ptr->next = node;
            ptr = node; // update pointer
        }

        else
        {
            head = node; // set head
            ptr = head; // set pointer
        }
    }

    int k; // divisor
    cout << "Enter k : ";
    cin >> k;

    head = rev(head); // reverse the linked list
    bool flag = false;
    ptr = head;

    while (ptr)
    {
        if (!(ptr->data % k)) // remainder 0 obtained
        {
            flag = true;
            cout << "Element " << ptr->data << " satisfies n % k = 0";
            break;
        }
        ptr = ptr->next; // move forward
    }

    if (!flag) cout << "No element in your linked list satisfies the given condition.";
    cout << endl << endl << "Thank you for using C++ Singly Linked Lists. Bye Bye !";
}