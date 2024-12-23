/*
    Program-14
    Implement TSP problem using Dynamic Programming approach.
    @ Prajwal Sundar
*/

#include "bits/stdc++.h"
using namespace std;

// Graph Class
class Graph
{
    public:

    int v, e; // number of vertices and edges
    int ** M; // adjacency matrix

    Graph(int n) // constructor
    {
        v = n; // set number of vertices
        e = 0; // no edges initially

        M = new int * [v];
        for (int i = 0; i < v; i++)
        {
            M[i] = new int [v];
            for (int j = 0; j < v; j++) M[i][j] = 0;
        }
    }

    void addEdge(int x, int y, int w)
    {
        if (!M[x][y]) e++; // increment number of edges
        M[x][y] = w; // set edge with given weight
    }

    int getWeight(int x, int y)
    {
        return M[x][y];
    }
};

// Travelling Salesman Problem using Dynamic Programming
// Graph G and Starting Vertex s
void TSP(Graph G, int s)
{
    int r = G.v; // number of rows of matrix
    int c = pow(2, G.v); // number of columns of matrix

    int ** C = new int * [r]; // cost matrix
    int ** N = new int * [r]; // next matrix
    for (int i = 0; i < r; i++)
    {
        C[i] = new int [c]; N[i] = new int [c];
        for (int j = 0; j < c; j++)
        {
            C[i][j] = 0; // 0 cost
            N[i][j] = -1; // no where to go next
        }
    }

    vector<int> * V = new vector<int> [r+1]; // vector
    int * ones = new int [c]; // number of one's
    ones[0] = 0; V[0].push_back(0);
    for (int i = 1; i < c; i++)
    {
        ones[i] = ones[i/2] + (i%2);
        V[ones[i]].push_back(i);
    }

    // Base Cases
    for (int i = 0; i < G.v; i++)
    {
        C[i][c-1] = G.getWeight(i, s);
        N[i][c-1] = s;
    }
    
    // Recursive Cases
    for (int n = 1; n < r; n++)
    {
        // n - number of vertices remaining (number of zeros)
        for (int ptr = 0; ptr < V[r-n].size(); ptr++)
        {
            int j = V[r-n][ptr]; // column number
            for (int i = 0; i < r; i++)
            {
                int mincost = INT_MAX, next = -1; // minimum cost and next vertex visited
                for (int x = 0; x < r; x++)
                {
                    if (!(j & (1 << x))) // xth vertex is unvisited
                    {
                        int cost = G.getWeight(i, x) + C[x][j+int(pow(2,x))]; // find cost
                        if (cost < mincost)
                        {
                            mincost = cost;
                            next = x; // update minimum cost and next vertex
                        }
                    }
                }

                C[i][j] = mincost;
                N[i][j] = next; // record results
            }
        }
    }

    int ptrR = s, ptrC = (int) pow(2, s);
    cout << endl << "Minimum Cost : " << C[ptrR][ptrC] << endl;
    cout << "Path : ";
    
    do
    {
        cout << ptrR << " -> ";
        int next = N[ptrR][ptrC];
        
        ptrR = next;
        ptrC += (int) pow(2, next);

    } while (ptrR != s);
    
    cout << s;
}

// Main Function
int main()
{
    cout << "Welcome to C++ Travelling Salesman Problem !" << endl << endl;

    int v; // number of vertices
    cout << "Enter the number of vertices in your graph : ";
    cin >> v;

    int e; // number of edges
    cout << "Enter the number of edges in your graph : ";
    cin >> e;

    Graph G(v); // graph object
    cout << "Enter each edge as (source destination weight) :-" << endl;
    for (int i = 0; i < e; i++)
    {
        int x, y, w; cin >> x >> y >> w;
        G.addEdge(x, y, w);
    }

    int s; // start vertex
    cout << "Enter the start vertex : ";
    cin >> s;

    TSP(G, s);
    cout << endl << endl << "Thank you for using C++ Travelling Salesman Problem. Bye Bye !";
}