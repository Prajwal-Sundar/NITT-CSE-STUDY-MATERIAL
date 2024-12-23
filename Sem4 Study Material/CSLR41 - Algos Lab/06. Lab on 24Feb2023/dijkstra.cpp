#include "bits/stdc++.h"
using namespace std;

struct Vertex
{
    int p; // position of current vertex
    int d; // minimum distance till now
    int prev; // lastly visited vertex

    Vertex(int x)
    {
        p = x; // position
        d = INT_MAX; // infinity by default
        prev = -1; // no parent by default
    }
};

class Graph
{
    public:

    int v, e; // number of vertices and edges
    int ** M; // adjacency matrix

    Graph(int x)
    {
        v = x; // set number of vertices
        e = 0; // set number of edges (initially no edge)

        // Adjacency Matrix
        M = (int **) malloc(v * sizeof(int *));
        for (int i = 0; i < v; i++)
        {
            M[i] = (int *) malloc(v * sizeof(int));
            for (int j = 0; j < v; j++)
                M[i][j] = 0;
        }
    }

    void addEdge(int x, int y, int w)
    {
        M[x][y] = M[y][x] = w; // add edge with given weight
        e++;
    }

    void remEdge(int x, int y)
    {
        if (M[x][y]) e--;
        M[x][y] = M[y][x] = 0; // remove edge
    }

    int getWeight(int x, int y)
    {
        return M[x][y]; // return weight of corresponding edge
    }
};

// Path generator function
string path(vector<Vertex*> V, int v)
{
    if (V[v]->prev == -1) // no previous
        return to_string(v);
    else
        return path(V, V[v]->prev) + " -> " + to_string(v);
}

// Function to implement Dijkstra's Algorithm for vertex v
void Dijkstra(Graph G, int start)
{
    vector<Vertex*> V; // vector

    // Initialization
    for (int i = 0; i < G.v; i++)
        V.push_back(new Vertex(i)); // initialize new vertex
    V[start]->d = 0; // make start to start distance 0

    // Visited array
    bool visited[G.v];
    memset(visited, false, sizeof(visited)); // no visited node

    // Current vertex to visit
    int vx = start;
    // Looping
    while (vx != -1)
    {
        visited[vx] = true; // current vertex is visited
        int minD = INT_MAX;
        int next = -1;

        for (int i = 0; i < G.v; i++)
        {
            if (!G.getWeight(i, vx) || visited[i]) continue;
            int dis = V[vx]->d + G.getWeight(i, vx);
            if (dis < V[i]->d) // new record
            {
                V[i]->d = dis; // update record
                V[i]->prev = vx; // update previous vertex
            }
            if (V[i]->d <= minD)
            {
                minD = V[i]->d;
                next = i; // update next vertex
            }
        }

        vx = next; // update next
    }

    cout << "Minimum distances and paths from vertex " << start << " :-" << endl;
    for (int i = 0; i < G.v; i++)
        cout << "Vertex " << V[i]->p << " : " << V[i]->d << " units with path : " << path(V, i) << endl;
}

// Main Function
int main()
{
    cout << "Welcome to C++ Dijsktra Algorithm !" << endl << endl;

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
        G.addEdge(s, d, w); // add edge to graph
    }

    int start; // source vertex
    cout << endl << "Enter your source vertex : ";
    cin >> start;

    cout << endl << "Dijkstra Algorithm :-" << endl;
    Dijkstra(G, start);
    cout << endl << "Thank you for using C++ Dijkstra Algorithm. Bye Bye !";
}