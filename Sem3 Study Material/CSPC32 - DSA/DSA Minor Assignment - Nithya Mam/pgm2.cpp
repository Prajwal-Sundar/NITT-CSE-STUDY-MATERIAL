/*
    Program-2
    Implement  circular  descending  priority  queue.  (Note:  the  functions  such  as 
Enqueue, Dequeue and Display need to be implemented.)
    @ Prajwal Sundar
*/

#include "bits/stdc++.h"
using namespace std;

// Circular Descending Order Priority Queue
class CDPQ
{
    public:

    int C; // capacity
    int F, R; // front and rear pointers
    int * Q; // queue

    CDPQ(int n) // constructor
    {
        C = n; // initialize capacity
        F = R = -1; // initialize pointers
        Q = new int [C]; // initialize queue
    }

    void enqueue(int n) // enqueue an element n
    {
        if (((F == 0) && (R == C-1)) || (R+1 == F)) // overflow
        {
            cout << "Error : QUEUE OVERFLOW";
            return;
        }
        else if ((F == -1) && (R == -1)) // first element enqueue
            F = R = 0;
        else if (R == C-1) // circle cross enqueue
            R = 0;
        else // normal enqueue
            R++;
        
        Q[R] = n; // enqueue
        cout << "Enqueue " << n << " : SUCCESS";

        sort();
    }

    void dequeue() // dequeue frontmost element
    {
        if ((F == -1) && (R == -1))
        {
            cout << "Error : QUEUE UNDERFLOW";
            return;
        }

        cout << "Dequeue " << Q[F] << " : SUCCESS";

        if (F == R) // last element dequeue
            F = R = -1;
        else if (F == C-1) // circle cross dequeue
            F = 0;
        else // normal dequeue
            F++;
    }

    void display()
    {
        cout << "QUEUE : ";

        if ((F == -1) && (R == -1)) // empty
            cout << "EMPTY";
        else if (F <= R) // normal display
            for (int i = F; i <= R; i++) cout << Q[i] << " ";
        else // circle cross display
        {
            for (int i = F; i < C; i++) cout << Q[i] << " ";
            for (int i = 0; i <= R; i++) cout << Q[i] << " ";
        }
    }

    void sort() // sort in descending order using insertion sort
    {
        bool flag = (F <= R);
        if (!flag) R += C;

        int P = R, elem = Q[R%C];
        while ((P > F) && (Q[(P-1)%C] < Q[P%C]))
        {
            swap(Q[P%C], Q[(P-1)%C]); // swap
            P--; // decrement pointer
        }
        Q[P%C] = elem;

        if (!flag) R -= C;
    }
};

// Main Function
int main()
{
    cout << "Welcome to C++ Circular Descending Order Priority Queue !" << endl;
    cout << "'E' stands for enqueue, 'D' for dequeue, 'd' for display and 'e' for exit." << endl << endl;

    int n; // capacity
    cout << "Enter the maximum capcity of your queue : ";
    cin >> n;
    cout << endl;

    bool flag = true;
    CDPQ Q(n); // queue object

    while (flag)
    {
        int n; // number

        char ch; // choice
        cout << "Enter your choice : ";
        cin >> ch;

        switch(ch)
        {
            case 'E': // enqueue
                cout << "Enter the element you wish to enqueue : ";
                cin >> n;
                Q.enqueue(n); // perform enqueue
                break;
            
            case 'D': // dequeue
                Q.dequeue();
                break;
            
            case 'd': // display
                Q.display();
                break;
            
            case 'e': // exit
                flag = false;
                cout << "Program Execution Terminated.";
                break;
            
            default:
                cout << "Invalid Choice.";
        }

        cout << endl << endl;
    }

    cout << "Thank you for using C++ Circular Descending Order Priority Queue. Bye Bye !";
}