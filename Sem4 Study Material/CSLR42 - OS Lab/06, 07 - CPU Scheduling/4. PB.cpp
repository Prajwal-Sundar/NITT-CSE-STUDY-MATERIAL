#include "bits/stdc++.h"
using namespace std;

struct Process
{
    int n; // process number
    int b; // burst time
    int a; // arrival time
    int p; // priority
    
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

// Print PB Gantt Chart and Table
void PB(vector<struct Process> V)
{
    cout << endl << "Gantt Chart :-" << endl << 0;
    sort(V.begin(), V.end(), comp); // sort based on arrival time

    int t = 0; // current timesnap
    int AP = -1; // arrival pointer

    int s = V.size(); // number of processes
    int c = s; // processes left to schedule

    bool over[s]; // schedule array
    memset(over, false, sizeof(over));

    double s_tt = 0, s_wt = 0, s_rt = 0, s_it = 0; // sum of times variable
    while (c)
    {
        // Set position of arrival pointer
        for (int i = AP+1; i < s; i++)
        {
            if (V[i].a > t) break;
            else AP++;
        }

        int minP = INT_MAX, p = -1; // store minimum priority
        for (int i = 0; i <= AP; i++)
        {
            if (over[i]) continue; // process has been scheduled earlier

            bool c1 = (V[i].p < minP);
            bool c2 = (p != -1) && (V[i].p == minP) && (V[i].a < V[p].a);
            bool c3 = (p != -1) && (V[i].p == minP) && (V[i].a == V[p].a) && (V[i].n < V[p].n);

            if (c1 || c2 || c3) // swap conditions
            {
                minP = V[i].p;
                p = i; // update position
            }
        }

        if (p == -1) // idle time needs to be spent
        {
            s_it += V[AP+1].a-t; // add idle time
            t = V[AP+1].a; // increment time
            
            cout << " [-] " << t;
        }

        else // Process 'p' is to be scheduled
        {
            c--;
            t += V[p].b; // increment time by burst time
            over[p] = true; // current process is over

            V[p].c = t; // completing time
            V[p].t = V[p].c - V[p].a; // turnaround time
            V[p].w = V[p].t - V[p].b; // waiting time
            V[p].r = V[p].w; // response time

            s_tt += V[p].t;
            s_wt += V[p].w;
            s_rt += V[p].r; // add times

            cout << " [P" << V[p].n << "] " << t;
        }
    }

    sort(V.begin(), V.end(), compP); // sort back based on position
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
    cout << "Welcome to C++ Priority Based (PB) CPU Scheduler !" << endl << endl;

    int num; // number of processes
    cout << "Enter the number of processes : ";
    cin >> num;

    vector<struct Process> V; // vector of processes
    cout << "For each process, enter (pid arrival_time burst_time priority_level) :-" << endl;
    for (int i = 0; i < num; i++)
    {
        struct Process P; // process
        cout << "Process " << i << " : ";
        cin >> P.n >> P.a >> P.b >> P.p; // get times as user input

        P.c = P.t = P.w = P.r = 0; // other times
        V.push_back(P);
    }

    PB(V);
    cout << endl << endl << "Thank you for using C++ PB CPU Scheduler. Bye Bye !";
}