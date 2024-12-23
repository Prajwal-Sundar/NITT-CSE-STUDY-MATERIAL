/*
    Program-1
    Implement  Queue  using  two  stacks.  (Note:  the  functions  such  as  Enqueue, 
Dequeue and Display need to be implemented.)
    @ Prajwal Sundar
*/

#include "bits/stdc++.h"
using namespace std;

class Queue
{
    public:

    stack<int> S1; // first stack
    stack<int> S2; // second stack

    // Enqueue a number into the queue
    void enqueue(int n)
    {
        S1.push(n); // push element onto stack
        cout << "Enqueue " << n << " operation : SUCCESS";
    }

    // Dequeue the frontmost element from the queue
    void dequeue()
    {
        if (S1.empty())
        {
            cout << "Error : QUEUE UNDERFLOW";
            return;
        }
        
        while (!S1.empty())
        {
            int top = S1.top();
            S2.push(top);
            S1.pop();
        }

        S2.pop(); // pop topmost
        cout << "Dequeue : SUCCESS";

        while (!S2.empty())
        {
            int top = S2.top();
            S1.push(top);
            S2.pop();
        }
    }

    // Display the queue
    void display()
    {
        cout << "Your Queue : ";

        if (S1.empty())
        {
            cout << "EMPTY";
            return;
        }

        while (!S1.empty())
        {
            int top = S1.top();
            S2.push(top);
            S1.pop();
        }

        while (!S2.empty())
        {
            int top = S2.top();
            cout << top << " ";
            S1.push(top);
            S2.pop();
        }
    }
};

// Main Function
int main()
{
    cout << "Welcome to C++ Queue using Stacks !" << endl;
    cout << "'E' stands for enqueue, 'D' for dequeue, 'd' for display and 'e' for exit." << endl << endl;

    bool flag = true;
    Queue Q; // queue object

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

    cout << "Thank you for using C++ Queue using Stacks. Bye Bye !";
}