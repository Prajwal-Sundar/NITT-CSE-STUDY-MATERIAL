#include "bits/stdc++.h"
using namespace std;

string longestPalindrome(string s) {
        int n = s.size();
        int M[n][n]; // matrix for dynamic programming
        memset(M, 0, sizeof(M));

        for (int d = 0; d < n; d++)
        {
            // Traversing through diagonal d, j-i=d
            for (int i = 0, j = d; i < n && j < n; i++, j++)
            {
                if (d == 0) M[i][j] = 1; // base case
                else if (s[i] == s[j]) M[i][j] = 2 + M[i+1][j-1];
                else M[i][j] = max(M[i][j-1], M[i+1][j]);
            }
        }

        string a, b;
        int i = 0, j = n-1; // matrix pointers
        while (true)
        {
            if (i >= j)
            {
                if (i == j) a += s[i];
                break;
            }

            else if (s[i] == s[j])
            {
                a += s[i]; b = s[j] + b;
                i++; j--;
            }

            else if (M[i][j-1] == M[i][j]) j--;
            else i++;
        }

        return a+b;
    }

int main()
{
    cout << "Welcome to C++ Longest Palindromic Subsequence !" << endl << endl;
    
     string str;
     cout << "Enter your string : ";
     cin >> str;
     
     cout << "The Longest Palindromic Subsequence is : " << longestPalindrome(str);
     cout << endl << endl << "Thank you for using C++ Longest Palindromic Subsequence. Bye Bye !";
}