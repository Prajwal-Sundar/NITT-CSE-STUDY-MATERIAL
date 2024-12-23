#include "bits/stdc++.h"
using namespace std;

// Structure of a node
struct Node
{
    int data; // data of a node
    int degree; // degree (number of children) of a node
    int mark; // mark of a node (for deletion operation)

    struct Node * left; // link to left sibling
    struct Node * right; // link to right sibling
    struct Node * parent; // link to parent
    struct Node * child; // link to any one child

    // Constructor for structure
    Node(int n)
    {
        data = n; // set data
        degree = 0; // leaf by default
        left = right = parent = child = NULL; // isloated by default
    }
};

// Display Functions
void levelOrder(struct Node * root);
void display(struct Node * RL);
void order(struct Node * RL);

// Fibonacci Heap Functions
struct Node * merge(struct Node * RL1, struct Node * RL2);
struct Node * ins(struct Node * RL, int x);
int findMin(struct Node * RL);
struct Node * extractMin(struct Node * RL);
struct Node * dec(struct Node * RL, int x, int k);
struct Node * del(struct Node * RL, int x);

// Level order traversal of a fibonacci tree
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

            struct Node * head = ptr->child;
            ptr = head; // pointer to traverse

            if (ptr) do {
                Q.push(ptr); // enqueue
                ptr = ptr->right; // proceed
            } while (ptr->right != head);
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

// Display a Full Fibonacci Heap
void display(struct Node * RL)
{
    if (!RL) // empty list
    {
        cout << "NULL";
        return;
    }

    cout << "Root List : ";
    struct Node * ptr = RL;

    do
    {
        cout << ptr->data << " "; // print data
        ptr = ptr->right; // move forward
    } while (ptr->right != RL);

    ptr = RL; // refresh pointer
    do
    {
        cout << endl << "Fibonacci Tree of Order " << ptr->degree << " :-" << endl;
        levelOrder(ptr); // print level order
        ptr = ptr->right; // move right
    } while (ptr->right != RL);
}

// Merge two fibonacci heaps
struct Node * merge(struct Node * RL1, struct Node * RL2)
{
    struct Node * ptr = RL1; // pointer
    while (ptr->right != RL1) ptr = ptr->right; // go to last node
    ptr->right = RL2;
    RL2->left = ptr; // connect both root lists

    ptr = RL2; // pointer
    while (ptr->right != RL2) ptr = ptr->right; // go to last node
    ptr->right = RL1;
    RL1->left = ptr; // connect on other side

    return RL1;
}

// Insert a new node into the root list
struct Node * ins(struct Node * RL, struct Node * min, int x)
{
    struct Node * node = new Node(x); // form node
    if (!RL) // first node insertion
    {
        RL = node; // initialize root list
        RL->left = RL; RL->right = RL; // circular connections
        return RL;
    }
    
    struct Node * prev = min->left;
    prev->right = node; node->left = prev;
    min->left = node; node->right = min; // insert before minimum position

    if (!min || node->data < min->data) min = node; // update minimum pointer
    return RL;
}

int main()
{
    struct Node * RL = NULL;
    struct Node * min = NULL;
    RL = ins(RL, min, 6);
    min = RL;
    RL = ins(RL, min, 7);
    display(RL);
}