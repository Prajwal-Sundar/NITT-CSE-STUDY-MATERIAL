#include "bits/stdc++.h"
using namespace std;

// Structure of a node
struct Node
{
    int data; // store data of a node
    int degree; // degree (number of children) of a node

    struct Node * parent; // link to parent
    struct Node * child; // link to leftmost child
    struct Node * sibling; // link to next sibling

    // Constructor for structure
    Node(int n)
    {
        data = n; // set data
        degree = 0; // leaf node by default
        parent = child = sibling = NULL; // alone by default
    }
};

// Auxiallary Functions
struct Node * rev(struct Node * head);
struct Node * insArr(struct Node * RL, int n);

// Display Functions
void levelOrder(struct Node * root);
void display(struct Node * RL);
void order(struct Node * RL);

// Binomial Heap Functions
struct Node * merge(struct Node * RL1, struct Node * RL2);
struct Node * ins(struct Node * RL, int x);
int findMin(struct Node * RL);
struct Node * extractMin(struct Node * RL);
struct Node * dec(struct Node * RL, int x, int k);
struct Node * del(struct Node * RL, int x);

// Main Function
int main();

// Function to reverse a linked list
struct Node * rev(struct Node * head)
{
    struct Node * prev = NULL, * curr = head, * next = NULL; // 3-pointer approach

    while (curr)
    {
        next = curr->sibling; // link to next node
        curr->sibling = prev; // reverse pointer link

        prev = curr;
        curr = next; // bring pointers forward
    }

    head = prev; // final head
    return head;
}

// Function to insert n elements into binomial heap's root list
struct Node * insArr(struct Node * RL, int n)
{
    int arr [n]; // declare array
    printf("Enter your elements : ");

    for (int i = 0; i < n; i++)
        cin >> arr[i]; // get elements
    for (int i = 0; i < n; i++)
        RL = ins(RL, arr[i]); // insert one by one
    
    return RL;
}

// Level order traversal of a binomial tree
void levelOrder(struct Node * root)
{
    queue<struct Node *> Q; // queue of addresses
    struct Node * ptr = root; // pointer
    Q.push(NULL); // enqueue NULL

    int l = 0; // current level
    cout << "\t" << "Level 0 : ";

    while (!Q.empty())
    {
        if (ptr) // element exists
        {
            cout << ptr->data << "(P:";
            if (ptr->parent) cout << ptr->parent->data << ")";
            else cout << "-) ";

            ptr = ptr->child; // move to child
            while (ptr) // enqueue all children
            {
                Q.push(ptr);
                ptr = ptr->sibling; // move to sibling
            }
        }

        else // NULL encountered
        {
            cout << endl << "\t" << "Level " << ++l << " : ";
            Q.push(NULL); // enqueue NULL
        }

        ptr = Q.front(); // frontmost element
        Q.pop(); // dequeue
    }
}

// Display a Full Binomial Heap
void display(struct Node * RL)
{
    if (!RL) // empty list
    {
        cout << "NULL";
        return;
    }

    cout << "Root List : ";
    struct Node * ptr = RL;
    while (ptr)
    {
        cout << ptr->data << " "; // print data
        ptr = ptr->sibling; // increment pointer
    }

    ptr = RL; // refresh pointer
    while (ptr)
    {
        cout << endl << "Binomial Tree of Order " << ptr->degree << " :-" << endl;
        levelOrder(ptr);
        ptr = ptr->sibling;
    }
}

// Insert-ordered Traversal of a Binomial Heap
void order(struct Node * root)
{
    if (root)
    {
        order(root->sibling);
        cout << root->data << " ";
        order(root->child);
    }
}

// Merge two binomial heaps, given pointers to their root lists' heads
struct Node * merge(struct Node * RL1, struct Node * RL2)
{
    struct Node * RL = new Node(-1); // dummy node
    struct Node * P1 = RL1, * P2 = RL2, * P = RL; // pointers to root lists

    while (P1 && P2)
    {
        if (P1->degree <= P2->degree)
        {
            P->sibling = P1; // insert into new root list
            P1 = P1->sibling; // update pointer1
        }

        else
        {
            P->sibling = P2; // insert into new root list
            P2 = P2->sibling; // update pointer2
        }

        P = P->sibling; // update pointer
    }

    while (P1) // remaining trees of root list 1
    {
        P->sibling = P1; // insert
        P1 = P1->sibling; // update pointer1
        P = P->sibling; // update pointer
    }

    while (P2) // remaining trees of root list 2
    {
        P->sibling = P2; // insert
        P2 = P2->sibling; // update pointer2
        P = P->sibling; // update pointer
    }

    struct Node * tmp = RL;
    RL = RL->sibling;
    free(tmp); // delete dummy

    struct Node * prev = NULL; // previous pointer
    struct Node * curr = RL; // root list pointer
    struct Node * next = NULL; // next pointer
    struct Node * nextNext = NULL;

    while (curr)
    {
        next = curr->sibling;
        if (next) nextNext = next->sibling;

        int c1 = (next) && (curr->degree == next->degree);
        int c2 = (!nextNext) || (nextNext && (next->degree != nextNext->degree));

        if (c1 && c2) // merge both trees
        {
            struct Node * root = (curr->data < next->data) ? curr : next; // final root
            struct Node * other = (curr->data > next->data) ? curr : next; // other root

            other->parent = root;
            other->sibling = root->child;
            root->child = other;
            (root->degree)++; // set of merge operations

            if (prev) prev->sibling = root;
            else RL = root;
            root->sibling = nextNext; // pointer updations

            curr = root; // pointer increment
        }

        else // no merge needed
        {
            prev = curr;
            curr = next; // pointer increments
        }
    }

    return RL; // return merged root list
}

// Insert a key into the binomial heap
struct Node * ins(struct Node * RL, int x)
{
    struct Node * node = new Node(x);
    return merge(RL, node);
}

// Find Minmum Operation
int findMin(struct Node * RL)
{
    if (!RL) // no heap present
        return INT_MIN;

    int min = RL->data; // assumption
    struct Node * ptr = RL->sibling; // pointer
    
    while (ptr)
    {
        if (ptr->data < min)
            min = ptr->data; // update minimum
        ptr = ptr->sibling; // increment pointer
    }

    return min;
}

// Extract Minimum Operation
struct Node * extractMin(struct Node * RL)
{
    if (!RL)
        return NULL;
    int min = findMin(RL); // find the minimum node

    struct Node * prev = NULL;
    struct Node * curr = RL;
    struct Node * next = NULL; // pointers

    while (curr)
    {
        next = curr->sibling;

        if (curr->data == min)
            break; // exit from loop
        
        prev = curr;
        curr = next; // update pointers appropriately
    }

    struct Node * heap = rev(curr->child); // head of binary heap below
    if (prev) prev->sibling = next; // detach minimum element
    else RL = next;
    free(curr); // free from memory

    return merge(RL, heap); // merge and return
}

// Decrease the value of a key x to k in the binomial heap
struct Node * dec(struct Node * RL, int x, int k)
{
    if (!RL)
        return NULL; // base case
    
    else if (RL->data != x) // not found at current position
    {
        RL->child = dec(RL->child, x, k); // continue search at child
        RL->sibling = dec(RL->sibling, x, k); // conitnue search at sibling
        return RL;
    }

    else // found at current position
    {
        RL->data = k; // modify data

        struct Node * ptr = RL; // pointer to root list
        while (ptr->parent)
        {
            if (ptr->data < ptr->parent->data) // violates min heap property
            {
                int tmp = ptr->data;
                ptr->data = ptr->parent->data;
                ptr->parent->data = tmp; // swap data of parent and child
            }
            
            ptr = ptr->parent; // bring up
        }
        
        return RL;
    }
}

// Delete a key from the binomial heap
struct Node * del(struct Node * RL, int x)
{
    RL = dec(RL, x, INT_MIN);
    RL = extractMin(RL);
    return RL;
}

// Main function
int main()
{
    cout << "Welcome to C++ Binomial Heaps !" << endl << endl;

    char code [] = {'s', 'o', 'm', 'e', 'i', 'I', 'd', 'D', 'E'};
    string arr [] = {"show the binary heap", "show insert-ordered traversal of the binary heap",
        "find minimum", "extract minimum", "insert a single element", "insert multiple elements",
        "decrease a key to a particular value", "delete a particular key", "exit"};

    for (int i = 0; i < 9; i++)
        cout << (i+1) << ") '" << code[i] << "' to " << arr[i] << endl;
    cout << endl;

    struct Node * RL = NULL;
    int flag = 1;
    while (flag)
    {
        char ch; // choice
        int n; // number
        int k; // key to decrease to

        cout << "Enter your choice : ";
        cin >> ch;

        switch(ch)
        {
            case 's':
                display(RL);
                break;
            
            case 'o':
                cout << "Insert Ordered Traversal is : ";
                order(RL);
                break;

            case 'm':
                if (RL)
                    cout << "The minimum number is : " << findMin(RL) << ".";
                else
                    cout << "The binomial heap is currently empty.";
                break;
            
            case 'e':
                if (RL)
                    cout << "The minimum element " << findMin(RL) << " was extracted out successfully.";
                else
                    cout << "The binomial heap is currently empty.";
                RL = extractMin(RL);
                break;
            
            case 'i':
                cout << "Enter the number to insert : ";
                cin >> n;
                RL = ins(RL, n);
                cout << n << " was inserted successfully.";
                break;
            
            case 'I':
                cout << "Enter the number of elements you wish to insert : ";
                cin >> n;
                RL = insArr(RL, n);
                cout << "The elements were inserted successfully.";
                break;
            
            case 'd':
                cout << "Enter the number to modify : ";
                cin >> n;
                cout << "Enter the new decreased value : ";
                cin >> k;
                if (k > n)
                    cout << "Only decrease operation is allowed.";
                else
                {
                    RL = dec(RL, n, k);
                    cout << n << " was decreased to " << k << " successfully.";
                }
                break;
            
            case 'D':
                cout << "Enter the number to delete : ";
                cin >> n;
                RL = del(RL, n);
                cout << n << " was deleted successfully.";
                break;
            
            case 'E':
                cout << "Program Terminated.";
                flag = 0;
                break;
            
            default:
                cout << "Invalid Choice.";
        }

        cout << endl << endl;
    }

    cout << "Thank you for using C++ Binomial Heaps. Bye Bye !";
}