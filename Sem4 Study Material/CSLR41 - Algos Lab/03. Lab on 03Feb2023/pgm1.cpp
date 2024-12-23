#include "bits/stdc++.h"
using namespace std;

// Get smallest integer
string get(string num, int k)
{
    stack<char> S; // stack to store digits

    // Remove peaks in the graph
    for (char c : num) // loop through the string number
    {
        while (!S.empty() && (k > 0) && S.top() > c) // peak exists
        {
            S.pop(); // remove peak
            k--; // decrement number of digits to be removed
        }
        if (!S.empty() || c != '0') // push final number into stack
            S.push(c);
    }

    // Remove largest numbers in the graph
    while (!S.empty() && k--)
        S.pop();
    
    string res = ""; // resultant string
    while (!S.empty())
    {
        res = S.top() + res; // add in the front
        S.pop(); // pop from the stack
    }

    return res;
}

// Main Function
int main()
{
    cout << "Welcome to C++ Lowest Number Generator !" << endl << endl;

    string num; // number
    cout << "Enter the original number : ";
    cin >> num;

    int k; // number of digits to remove
    cout << "Enter the number of digits to remove : ";
    cin >> k;

    cout << "The lowest possible number formed after removing " << k << " digits is : " << get(num, k);
    cout << endl << endl << "Thank you for using C++ Lowest Number Generator. Bye Bye !";
}