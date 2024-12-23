/*
    CSLR41 Algorithms Laboratory
    Prajwal Sundar - Roll Number 106121092
    Program-1
    Print BFS and DFS orders of a given graph
*/

#include "bits/stdc++.h"
using namespace std;

class Graph
{
    public :

    int v; // number of vertices
    char * L; // labels of graphs
    int ** M; // adjacency matrix

    Graph() // constructor
    {
        cout << "Enter the number of vertices : ";
        cin >> v; // get vertices

        L = (char *) malloc(v * sizeof(char));
        cout << "Enter the labelling of your vertices : ";
        for (int i = 0; i < v; i++) cin >> L[i]; // get labelling

        M = (int **) malloc(v * sizeof(int *));
        for (int i = 0; i < v; i++)
        {
            M[i] = (int *) malloc(v * sizeof(int));
            for (int j = 0; j < v; j++) M[i][j] = 0;
        }
    }

    int getPos(char ch)
    {
        for (int i = 0; i < v; i++)
            if (L[i] == ch) return i; // position found
        return -1; // position not found
    }

    void addEdge()
    {
        char a, b;
        cin >> a >> b;

        int v1 = getPos(a), v2 = getPos(b); // endpoints of vertices
        M[v1][v2] = M[v2][v1] = 1; // set edge between vertices
    }

    // Print BFS order of the graph
    void BFS(char ch)
    {
        int visited[v]; // array of visited vertices
        memset(visited, 0, sizeof(visited));

        queue<int> Q; // queue
        int p = getPos(ch); // starting position
        
        Q.push(p); // enqueue current position
        visited[p] = 1; // current vertex is visited

        while (!Q.empty())
        {
            int x = Q.front(); // frontmost position
            Q.pop(); // dequeue
            cout << L[x] << " "; // print label

            for (int i = 0; i < v; i++)
            {
                if (!visited[i] && M[i][x])
                {
                    Q.push(i); // enqueue position
                    visited[i] = 1; // now position is visited
                }
            }
        }
    }

    // Print DFS order of the graph
    void DFS(char ch)
    {
        int visited[v]; // array of visited vertices
        memset(visited, 0, sizeof(visited));

        stack<int> S; // stack
        int p = getPos(ch); // starting position
        
        S.push(p); // push current position
        visited[p] = 1; // current vertex is visited

        while (!S.empty())
        {
            int x = S.top(); // topmost position
            S.pop(); // pop
            cout << L[x] << " "; // print label

            for (int i = v-1; i >= 0; i--)
            {
                if (!visited[i] && M[i][x])
                {
                    S.push(i); // push position
                    visited[i] = 1; // now position is visited
                }
            }
        }
    }
};

int main()
{
    cout << "Welcome to C++ BFS-DFS Displayer !" << endl << endl;

    Graph G; // graph object
    cout << endl;

    int e; // number of edges
    cout << "Enter the number of edges in your graph : ";
    cin >> e;

    cout << "In the next " << e << " pairs, enter end-vertices of each edge :-" << endl;
    for (int i = 0; i < e; i++) G.addEdge(); // add edge

    char ch;
    cout << endl << "Enter the start vertex : ";
    cin >> ch;

    cout << "BFS Order : ";
    G.BFS(ch);

    cout << endl << "DFS Order : ";
    G.DFS(ch);

    cout << endl << endl << "Thank you for using C++ BFS-DFS Displayer. Bye Bye !";
}