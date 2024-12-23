#include "bits/stdc++.h"
using namespace std;

// Count partition function
int count(string str)
{
    int L = 0, R = 0; // count of L's and R's
    int c = 0; // count of partitions

    for (char ch : str)
    {
        if (ch == 'L') L++; // L encountered
        else if (ch == 'R') R++; // R encountered
        if (L == R) c++; // one partition possible
    }

    return c; // return number of partitions
}

// Main Function
int main()
{
    cout << "Welcome to C++ Balanced String Counter !" << endl << endl;

    string str; // string
    cout << "Enter your balanced string of L's and R's : ";
    cin >> str;

    cout << "The number of partitions is : " << count(str);
    cout << endl << endl << "Thak you for using C++ Balanced String Counter. Bye Bye !";
}