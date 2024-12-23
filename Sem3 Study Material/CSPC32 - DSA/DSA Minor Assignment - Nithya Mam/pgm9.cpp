/*
    Program-9
    Write a program for finding the maximum-weight spanning tree in a graph.
    @ Prajwal Sundar
*/

#include "bits/stdc++.h"
using namespace std;

struct Edge
{
    int x, y, w;
};

bool comp(struct Edge A, struct Edge B)
{
    return (A.w > B.w);
}

class Graph
{
    public:

    int v; // number of vertices
    int e; // number of edges
    int W; // total weight of graph
    int ** M; // adjacency matrix
    vector<struct Edge> E; // vector of edges

    Graph(int n) // constructor
    {
        v = n; // initialize number of vertices
        e = 0; // initialize number of edges
        W = 0; // initialize total weight of graph

        M = new int * [v]; // initialize adjacency matrix
        for (int i = 0; i < v; i++)
        {
            M[i] = new int [v];
            for (int j = 0; j < v; j++) M[i][j] = 0;
        }
    }

    void addEdge(int x, int y, int w) // add edge with given weight
    {
        M[x][y] = M[y][x] = w; // set edge
        e++; // increment number of edges
        W += w; // add weight of new edge
        E.push_back({x, y, w});
    }

    void displayGraph() // display all graph edges
    {
        for (int i = 0; i < e; i++)
            cout << "Edge of weight " << E[i].w << " between (" << E[i].x << "," << E[i].y << ")" << endl;
    }
};

// Absolute Parents Function
int getAbsParent(int * parents, int v)
{
    if (parents[v] < 0) return v;
    else return getAbsParent(parents, parents[v]);
}

// Return MST of maximum weight
Graph Kruskal(Graph G)
{
    sort(G.E.begin(), G.E.end(), comp); // arrange edges in descending order of weight

    Graph MST(G.v); // maximum spanning tree
    int parents[G.v]; // array pointing to parents
    memset(parents, -1, sizeof(parents));

    for (int i = 0; (i < G.e && MST.e < G.v-1); i++)
    {
        int xp = getAbsParent(parents, G.E[i].x);
        int yp = getAbsParent(parents, G.E[i].y);

        if (xp == yp) continue; // cycle formation
        else if (parents[xp] < parents[yp]) // make x the parent of y
        {
            parents[xp] += parents[yp];
            parents[yp] = xp;
        }
        else // make y the parent of x
        {
            parents[yp] += parents[xp];
            parents[xp] = yp;
        }

        MST.addEdge(G.E[i].x, G.E[i].y, G.E[i].w); // add edge to graph
    }

    return MST;
}

// Main Function
int main()
{
    cout << "Welcome to C++ Maximum Spanning Trees !" << endl << endl;

    int v; // number of vertices
    cout << "Enter the number of vertices : ";
    cin >> v;

    int e; // number of edges
    cout << "Enter the number of edges : ";
    cin >> e;

    Graph G(v);
    cout << "Enter each edge as (vertex1 vertex2 weight) :-" << endl;
    for (int i = 0; i < e; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        G.addEdge(x, y, w); // add edge to graph object
    }

    Graph MST = Kruskal(G); // get maximum spanning tree using Kruskal's algorithm
    cout << endl << "The maximum Spanning Tree has the following edges :" << endl;
    MST.displayGraph();
    cout << "Weight of MST : " << MST.W;

    cout << endl << endl << "Thank you for using C++ Maximum Spanning Trees. Bye Bye !";
}