#include "bits/stdc++.h"
using namespace std;

struct Process
{
    int n; // process number
    int b; // burst time
    int a; // arrival time
    
    int c; // completion time
    int t; // turnaround time
    int w; // waiting time
    int r; // response time
};

// Sort processes based on arrival time
bool comp(Process P1, Process P2)
{
    return (P1.a < P2.a); // required condition
}

// Sort processes based on position
bool compP(Process P1, Process P2)
{
    return (P1.n < P2.n); // required condition
}

// Print FCFS Gantt Chart and Table
void FCFS(vector<struct Process> V)
{
    cout << endl << "Gantt Chart :-" << endl << 0;
    sort(V.begin(), V.end(), comp); // sort based on arrival times

    int t = 0; // current timesnap
    int s = V.size(); // number of processes
    double s_tt = 0, s_wt = 0, s_rt = 0, s_it = 0; // sum of times

    for (int i = 0; i < s; i++)
    {
        if (t < V[i].a) // idle condition
        {
            s_it += V[i].a-t; // add idle time
            cout << " [-] " << V[i].a;
            t = V[i].a; // update time
        }
        
        t += V[i].b; // add burst time
        V[i].t = V[i].b; // turnaround time
        cout << " [P" << V[i].n << "] " << t;

        V[i].c = t; // completion time
        V[i].t = V[i].c - V[i].a; // turnaround time
        V[i].w = V[i].t - V[i].b; // waiting time
        V[i].r = V[i].w; // response times

        s_tt += V[i].t;
        s_wt += V[i].w;
        s_rt += V[i].r; // add times
    }

    sort(V.begin(), V.end(), compP); // sort based on position
    cout << endl << endl << "\t" << "AT" << "\t" << "BT" << "\t" "CT" << "\t" << "TT" << "\t" << "WT" << "\t" << "RT" << endl;
    for (int i = 0; i < s; i++)
        cout << "P" << V[i].n << "\t" << V[i].a << "\t" << V[i].b << "\t" << V[i].c << "\t" << V[i].t << "\t" << V[i].w << "\t" << V[i].r << endl;
    
    cout << endl << "Average Turnaround Time = " << (s_tt / s);
    cout << endl << "Average Waiting Time = " << (s_wt / s);
    cout << endl << "Average Response Time = " << (s_rt / s);
    cout << endl << "Total Idle Time = " << s_it;
}

int main()
{
    cout << "Welcome to C++ First Come First Serve (FCFS) CPU Scheduler !" << endl << endl;

    int num; // number of processes
    cout << "Enter the number of processes : ";
    cin >> num;

    vector<struct Process> V; // vector of processes
    cout << "For each process, enter (pid arrival_time burst_time) :-" << endl;
    for (int i = 0; i < num; i++)
    {
        struct Process P; // process
        cout << "Process " << i << " : ";
        cin >> P.n >> P.a >> P.b; // get times as user input

        P.c = P.t = P.w = P.r = 0; // other times
        V.push_back(P);
    }

    FCFS(V);
    cout << endl << endl << "Thank you for using C++ FCFS CPU Scheduler. Bye Bye !";
}