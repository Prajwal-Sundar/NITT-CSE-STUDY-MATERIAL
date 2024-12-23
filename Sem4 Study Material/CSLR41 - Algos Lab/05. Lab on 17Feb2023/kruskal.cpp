#include "bits/stdc++.h"
using namespace std;

struct Edge
{
    int x; // source
    int y; // destination
    int w; // weight

    Edge(int a, int b, int c)
    {
        x = a; y = b; // initialize source and destination
        w = c; // initialize weight
    }
};

class Graph
{
    public :

    int v; // number of vertices
    int e; // number of edges
    int ** M; // adjacency matrix
    vector<Edge*> E; // vector of edges

    Graph(int x)
    {
        v = x; // Initialize number of vertices
        e = 0; // Initialize number of edges

        // Initialize adjacency matrix
        M = (int **) malloc(v * sizeof(int *));
        for (int i = 0; i < v; i++)
        {
            M[i] = (int *) malloc(v * sizeof(int));
            for (int j = 0; j < v; j++)
                M[i][j] = 0;
        } 
    }

    // Function to add an edge to the graph
    void addEdge(int x, int y, int w)
    {
        if (!M[x][y]) e++; // increment number of edges
        M[x][y] = M[y][x] = w;
        E.push_back(new Edge(x, y, w)); // add new edge to graph
    }

    // Function to return the weight of an edge
    int getWeight(int x, int y)
    {
        return M[x][y];
    }
    
    // Function to print all edges in a graph
    void printEdges()
    {
        for (auto ptr = E.begin(); ptr != E.end(); ++ptr)
            cout << "Edge of weight " << (*ptr)->w << " between vertices (" << (*ptr)->x << "," << (*ptr)->y << ")" << endl;
    }
};

// Compare function to sort edges in increasing order of weight
bool comp(Edge * E1, Edge * E2)
{
    return (E1->w <= E2->w);
}

// Get parent of a vertex
int getParent(vector<int> &parents, int v)
{
    if (parents[v] < 0) return v; // no parent
    else return getParent(parents, parents[v]);
}

// Kruskal's Algorithm Implementation
void Kruskal(Graph G)
{
    sort(G.E.begin(), G.E.end(), comp); // sort
    
    vector<int> parents; // list of parents of nodes
    for (int i = 0; i < G.v; i++)
        parents.push_back(-1); // initialize to -1
    
    Graph MST(G.v); // minimal spanning tree graph
    int W = 0; // weight of minimal spanning tree formed
    
    for (int i = 0; (i < G.e) && (MST.e < (G.v-1)); i++)
    {
        int xp = getParent(parents, G.E[i]->x); // parent of x
        int yp = getParent(parents, G.E[i]->y); // parent of y

        if ((xp > 0) && (yp > 0) && (xp == yp)) // cycle formation
            continue; // reject edge and continue
        
        // Edge accepted, first add it to the MST
        MST.addEdge(G.E[i]->x, G.E[i]->y, G.E[i]->w); // add edge
        W += G.E[i]->w; // increment

        // Union of 2 disjoint sets
        if (parents[xp] >= parents[yp]) // make x point to y
        {
            parents[yp] += parents[xp]; // increase number of nodes
            parents[xp] = yp; // change parent of x to y
        }
        else // make y point to x
        {
            parents[xp] += parents[yp]; // increase number of nodes
            parents[yp] = xp; // change parent of y to x
        }
    }

    MST.printEdges();
    cout << "Weight of MST : " << W << endl;
}

// Main Function
int main()
{
    cout << "Welcome to C++ Kruskal's Algorithm !" << endl << endl;

    int v; // number of vertices
    cout << "Enter the number of vertices : ";
    cin >> v;

    Graph G(v); // graph object

    int e; // number of edges
    cout << "Enter the number of edges : ";
    cin >> e;

    cout << "In the next " << e << " lines, enter edge as (start end weight) :-" << endl;
    for (int i = 0; i < e; i++)
    {
        int s, d, w; // source, destination and weight
        cin >> s >> d >> w;
        G.addEdge(s, d, w);
    }

    cout << endl << "The Minimal Spanning Tree consists of the following edges :-" << endl;
    Kruskal(G); // implement Kruskal's Algorithm
    cout << endl << "Thank you for using C++ Kruskal's Algorithm. Bye Bye !";
}