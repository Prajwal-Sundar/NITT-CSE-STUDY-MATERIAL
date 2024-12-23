#include "bits/stdc++.h"
using namespace std;

struct Fit
{
    string name;
    vector<int> empty;
    vector<int> allocated;
    bool done;
    int emp;
};

struct Fit create(string name, int mp, int p, vector<int> MP, vector<int> P)
{
    struct Fit S; // structure
    S.name = name;

    for (int i = 0; i < mp; i++)
    {
        S.empty.push_back(MP[i]);
        S.emp += MP[i]; // initially whole space is empty
    }

    for (int i = 0; i < p; i++) S.allocated.push_back(-1); // initially nothing is allocated
    S.done = true; // positive assumption that process can be completed
    
    return S;
}

struct Fit FirstFit(int mp, int p, vector<int> MP, vector<int> P)
{
    struct Fit S = create("First-Fit", mp, p, MP, P); // new structure
    cout << "First Fit Allocation :-" << endl;

    for (int i = 0; i < p; i++)
    {
        // Allocate to process i
        
        int ptr = 0; // pointer
        while (ptr < mp)
        {
            if ((S.empty[ptr] == MP[ptr]) && (MP[ptr] >= P[i])) break; // unalloacted partition found
            else ptr++;
        }

        if (ptr == mp) // run out of memory partitions
        {
            S.done = false;
            cout << P[i] << "K process -> not allocated" << endl;
        }
        
        else // allocate process 'i' to partition 'ptr'
        {
            S.empty[ptr] -= P[i]; // reduce empty space left
            S.emp -= P[i];
            S.allocated[i] = MP[ptr]; // process allocated
            cout << P[i] << "K process -> " << MP[ptr] << "K partition" << endl;
        }
    }
    
    cout << endl;
    return S;
}

struct Fit BestFit(int mp, int p, vector<int> MP, vector<int> P)
{
    sort(MP.begin(), MP.end()); // sort memory partitions
    struct Fit S = create("Best-Fit", mp, p, MP, P); // new structure
    cout << "Best Fit Allocation :-" << endl;

    for (int i = 0; i < p; i++)
    {
        // Allocate to process i
        
        int ptr = 0; // pointer
        while (ptr < mp)
        {
            if (MP[ptr] >= P[i]) break; // enough size reached
            else ptr++; // move forward
        }

        while (ptr < mp)
        {
            if (S.empty[ptr] == MP[ptr]) break; // unalloacted partition found
            else ptr++;
        }

        if (ptr == mp) // run out of memory partitions
        {
            S.done = false;
            cout << P[i] << "K process -> not allocated" << endl;
        }
        
        else // allocate process 'i' to partition 'ptr'
        {
            S.empty[ptr] -= P[i]; // reduce empty space left
            S.emp -= P[i];
            S.allocated[i] = MP[ptr]; // process allocated
            cout << P[i] << "K process -> " << MP[ptr] << "K partition" << endl;
        }
    }
    
    cout << endl;
    return S;
}

struct Fit WorstFit(int mp, int p, vector<int> MP, vector<int> P)
{
    sort(MP.begin(), MP.end(), greater<int>()); // sort memory partitions
    struct Fit S = create("Worst-Fit", mp, p, MP, P); // new structure
    cout << "Worst Fit Allocation :-" << endl;

    for (int i = 0; i < p; i++)
    {
        // Allocate to process i
        
        int ptr = 0; // pointer
        while (ptr < mp)
        {
            if ((S.empty[ptr] == MP[ptr]) && (MP[ptr] >= P[i])) break; // sizable non-allocated partition
            else ptr++; // move forward
        }

        if (ptr == mp) // run out of memory partitions
        {
            S.done = false;
            cout << P[i] << "K process -> not allocated" << endl;
        }
        
        else // allocate process 'i' to partition 'ptr'
        {
            S.empty[ptr] -= P[i]; // reduce empty space left
            S.emp -= P[i];
            S.allocated[i] = MP[ptr]; // process allocated
            cout << P[i] << "K process -> " << MP[ptr] << "K partition" << endl;
        }
    }
    
    cout << endl;
    return S;
}

void compare(struct Fit FF, struct Fit BF, struct Fit WF)
{
    vector<struct Fit> V; // vector

    if (FF.done && BF.done && WF.done) // all algorithms have allocated completely
        V = {FF, BF, WF};
    
    else if (FF.done && BF.done) V = {FF, BF};
    else if (FF.done && WF.done) V = {FF, WF};
    else if (BF.done && WF.done) V = {BF, WF}; // 2 are completed

    else if (FF.done) V = {FF};
    else if (BF.done) V = {BF};
    else if (WF.done) V = {WF}; // 1 is completed

    else V = {FF, BF, WF}; // none are completed

    int s = V.size();
    if (s == 1) // only one is completed
    {
        cout << V[0].name << " is the best algorithm as it is the only algorithm wherein all processes are allocated.";
        return;
    }

    int m = INT_MAX; // algorithm with least empty space
    string alg = "";
    for (int i = 0; i < s; i++)
    {
        if (V[i].emp < m)
        {
            m = V[i].emp;
            alg = V[i].name; // update minimum record
        }
    }

    cout << alg << " is the best algorithm as it leaves the least empty space.";
}

int main()
{
    cout << "Welcome to C++ Partition Memory Management !" << endl << endl;

    int mp; // number of memory partitions
    cout << "Enter the number of memory partitions : ";
    cin >> mp;

    vector<int> MP;
    cout << "Enter the memory partitions : ";
    for (int i = 0; i < mp; i++)
    {
        int tmp; cin >> tmp;
        MP.push_back(tmp); // memory partition
    }

    int p; // number of processes
    cout << "Enter the number of processes : ";
    cin >> p;

    vector<int> P;
    cout << "Enter the processes : ";
    for (int i = 0; i < p; i++)
    {
        int tmp; cin >> tmp;
        P.push_back(tmp); // process
    }
    cout << endl;

    struct Fit FF = FirstFit(mp, p, MP, P); // first fit
    struct Fit BF = BestFit(mp, p, MP, P); // best fit
    struct Fit WF = WorstFit(mp, p, MP, P); // worst fit

    compare(FF, BF, WF); // compare algorithms
    cout << endl << endl << "Thank you for using C++ Partition Memory Management. Bye Bye !";
}