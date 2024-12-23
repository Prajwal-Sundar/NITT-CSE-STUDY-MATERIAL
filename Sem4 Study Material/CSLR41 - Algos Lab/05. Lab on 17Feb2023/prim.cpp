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

void Prim(Graph G)
{
    vector<int> V = {0}; // vertices in MST
    vector<int> VD; // vertices not in MST
    for (int i = 1; i < G.v; i++)
        VD.push_back(i);
    
    int W = 0; // weight of MST
    Graph MST(G.v); // minimum spanning tree graph
    
    for (int e = 0; e < G.v-1; e++)
    {
        int min = INT_MAX; // minimum weighted edge
        int s = -1, d = -1; // source and destination of minimum weighted edge

        int Vl = V.size(), VDl = VD.size(); // lengths of vector arrays
        for (int i = 0; i < Vl; i++)
        {
            for (int j = 0; j < VDl; j++)
            {
                int w = G.getWeight(V[i], VD[j]); // get weight of edge
                if (w && w < min) // new record
                {
                    min = w;
                    s = i; d = j; // update record
                }
            }
        }

        MST.addEdge(V[s], VD[d], min); // add edge to graph
        W += min; // update weight

        V.push_back(VD[d]); // push destination into MST vector
        VD.erase(VD.begin()+d); // remove destination from MST' vector
    }

    sort(MST.E.begin(), MST.E.end(), comp); // sort edges of MST
    MST.printEdges();
    cout << "Weight of MST : " << W << endl;
}

// Main Function
int main()
{
    cout << "Welcome to C++ Prim's Algorithm !" << endl << endl;

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
    Prim(G); // implement Prim's Algorithm
    cout << endl << "Thank you for using C++ Prim's Algorithm. Bye Bye !";
}