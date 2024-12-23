#include "bits/stdc++.h"
using namespace std;

int * computeLPS(string pat)
{
    int PL = pat.size();
    int * LPS = new int [PL];
    LPS[0] = 0;
    
    int i = 0, j = 1;
    while (j < PL)
    {
        if (pat[i] == pat[j])
            LPS[j++] = ++i;
        else if (i == 0)
            LPS[j++] = 0;
        else
            i = LPS[i-1];
    }
    
    return LPS;
}

int main()
{
    string txt;
    cout << "Enter text : ";
    cin >> txt;
    
    string pat;
    cout << "Enter pattern : ";
    cin >> pat;
    
    int * LPS = computeLPS(pat);
    int TL = txt.size(), PL = pat.size();
    int i = 0, j = 0;
    vector<int> V;
    
    while ((i < TL) && (j < PL))
    {
        if (txt[i] == pat[j])
        {
            i++; j++;
        }
        else if (j != 0)
            j = LPS[j-1];
        
        if ((i <= TL) && (j == PL))
        {
            V.push_back(i-PL);
            j = LPS[j-1];
        }
    }
    
    if (!V.size()) cout << "Pattern not found";
    else
    {
        cout << "Pattern found at location(s) : ";
        for (int x = 0; x < V.size(); x++) cout << V[x] << " ";
    }
}