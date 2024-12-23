#include "bits/stdc++.h"
using namespace std;

// Structure of a file
struct File
{
    string name; // name of file
    int id; // file id
    int start; // start memory address of file
    int length; // length of file
};

// Minimum of two input integers
int min(int x, int y)
{
    return (x < y) ? x : y;
}

// Allocate memory to a file
void allocFile(vector<int> &M, struct File F)
{
    bool free = true; // initial positive assumption
    int s = min(F.start+F.length, M.size());

    for (int i = F.start; i < s; i++)
    {
        if (M[i] != -1) // occupied slot obtained
        {
            free = false; // cannot be allocated
            break;
        }
    }

    if (!free)
        cout << "This file cannot be allocated memory at present.";
    else
    {
        for (int i = F.start; i < F.start+F.length; i++) M[i] = F.id;
        cout << "File was allocated into the memory successfully.";
    }
}

// Delete Function
void delFile(vector<int> &M, vector<struct File> &V, string name)
{
    int id = -1; // search for id
    int nf = V.size(); // number of files

    for (int i = 0; i < nf; i++)
    {
        if (V[i].name == name)
        {
            id = i;
            break;
        }
    }

    if (id == -1) // file name not found
        cout << "File with the given name was not found.";
    else // perform deletion
    {
        struct File F = V[id];
        for (int i = F.start; i < F.start+F.length; i++) M[i] = -1;
        cout << "File was deleted from memory successfully.";
    }
}

// Display Function
void display(vector<int> &M, vector<struct File> &V)
{
    int ms = M.size(); // size of memory
    for (int i = 0; i < ms; i++)
    {
        if (M[i] == -1) continue; // free slot
        struct File F = V[M[i]]; // get file
        cout << "File " << F.name << " : " << F.start << "-" << (F.start+F.length-1) << endl;
        i += F.length-1;
    }
    cout << "(Other slots are empty)";
}

// Main Function
int main()
{
    cout << "Welcome to C++ Contiguous File Allocation !" << endl << endl;

    int s; // total disk space
    cout << "Enter the total disk space available : ";
    cin >> s;

    vector<int> M; // memory
    for (int i = 0; i < s; i++) M.push_back(-1);
    cout << endl;

    int id = 0; // file id
    vector<struct File> V; // vector of files

    cout << "The following options are available :-" << endl;
    cout << "'a' for File Allocation" << endl;
    cout << "'d' for File Deletion" << endl;
    cout << "'D' to Display File Allocation Table" << endl;
    cout << "'e' to Exit" << endl << endl;

    bool flag = true;
    while (flag)
    {
        char ch; // choice
        cout << "Enter your choice : ";
        cin >> ch;

        struct File F; // new file variable
        string name; // file to delete

        switch(ch)
        {
            case 'a': // file allocation                
                cout << "Enter file name : ";
                cin >> F.name;
                cout << "Enter start location : ";
                cin >> F.start;
                cout << "Enter file length : ";
                cin >> F.length;

                F.id = id++;
                allocFile(M, F); // allocate memory
                V.push_back(F);
                break;
            
            case 'd': // file deletion
                cout << "Enter the name of the file you wish to delete : ";
                cin >> name;

                delFile(M, V, name); // delete from memory
                break;
            
            case 'D': // display allocated memory
                display(M, V);
                break;
            
            case 'e':
                flag = false;
                cout << "Program Terminated.";
                break;
            
            default:
                cout << "Invalid Choice.";
        }

        cout << endl << endl;
    }

    cout << "Thank you for using C++ Contiguous File Allocation. Bye Bye !";
}