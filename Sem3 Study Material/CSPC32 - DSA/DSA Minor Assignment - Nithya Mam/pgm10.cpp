/*
    Program-10
    Write a program to return the reverse of the directed graph (each edge from v to w 
is replaced by an edge from w to v).
    @ Prajwal Sundar
*/

#include "bits/stdc++.h"
using namespace std;

class Graph
{
    public:

    int v; // number of vertices
    int e; // number of edges
    int ** M; // adjacency matrix

    Graph(int n) // constructor
    {
        v = n; // initialize number of vertices
        e = 0; // initialize number of edges
        M = new int * [v];
        for (int i = 0; i < v; i++)
        {
            M[i] = new int [v];
            for (int j = 0; j < v; j++) M[i][j] = 0; // no edge present initially
        }
    }

    void addEdge(int x, int y)
    {
        M[x][y] = 1; // add edge to graph
    }

    void printEdges() // print all edges present in graph
    {
        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                if (M[i][j]) cout << "(" << i << "," << j << ") ";
    }

    void transpose() // reverse the graph
    {
        for (int i = 0; i < v; i++)
            for (int j = 0; j < i; j++)
                swap(M[i][j], M[j][i]);
    }
};

// Main Function
int main()
{
    cout << "Welcome to C++ Graph Reverser !" << endl << endl;

    int v; // vertices
    cout << "Enter the number of vertices : ";
    cin >> v;

    int e; // edges
    cout << "Enter the number of edges : ";
    cin >> e;

    Graph G(v); // graph
    cout << "Enter each edge as (source destination) :-" << endl;
    for (int i = 0; i < e; i++)
    {
        int x, y;
        cin >> x >> y;
        G.addEdge(x, y);
    }

    G.transpose(); // reverse direction of all edges
    cout << endl << "Reversed Graph :" << endl;
    G.printEdges();

    cout << endl << endl << "Thank you for using C++ Graph Reverser. Bye Bye !";

}