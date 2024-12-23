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

    int ir; // initial response time
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

// Print SRTF Gantt Chart and Table
void SRTF(vector<struct Process> V)
{
    cout << endl << "Gantt Chart :-" << endl << 0;
    sort(V.begin(), V.end(), comp); // sort based on arrival time

    int t = 0; // current timesnap
    int AP = -1; // arrival pointer

    int s = V.size(); // number of processes
    int c = s; // processes left to schedule

    int BT[s]; // array of burst times
    for (int i = 0; i < s; i++)
        BT[i] = V[i].b; // copy burst times
    
    double s_tt = 0, s_wt = 0, s_rt = 0, s_it = 0; // sum of times variable
    while (c)
    {
        // Set position of arrival pointer
        for (int i = AP+1; i < s; i++)
        {
            if (V[i].a > t) break;
            else AP++;
        }
        // Processes till AP's position have now arrived

        int minJ = INT_MAX, p = -1; // store minimum job burst time
        for (int i = 0; i <= AP; i++)
        {
            if (!BT[i]) continue; // process has been scheduled earlier

            bool c1 = (V[i].b < minJ);
            bool c2 = (p != -1) && (V[i].b == minJ) && (V[i].a < V[p].a);
            bool c3 = (p != -1) && (V[i].b == minJ) && (V[i].a == V[p].a) && (V[i].n < V[p].n);

            if (c1 || c2 || c3) // swap conditions
            {
                minJ = V[i].b;
                p = i; // update position
            }
        }

        if (p == -1) // idle time needs to be spent
        {
            s_it += V[AP+1].a-t; // add idle time
            t = V[AP+1].a; // increment time
            
            cout << " [-] " << t;
        }

        // In these 2 cases, process 'p' is to be scheduled

        else if ((AP == s-1) || (V[AP+1].a-t >= BT[p])) // process can be fully scheduled
        {
            if (BT[p] == V[p].b) // process is being scheduled for the first time
                V[p].ir = t; // record initial response time

            c--;
            t += BT[p]; // increment time by burst time
            BT[p] = 0; // current process is over

            V[p].c = t; // completing time
            V[p].t = V[p].c - V[p].a; // turnaround time
            V[p].w = V[p].t - V[p].b; // waiting time
            V[p].r = V[p].ir - V[p].a; // response time

            s_tt += V[p].t;
            s_wt += V[p].w;
            s_rt += V[p].r; // add times

            cout << " [P" << V[p].n << "] " << t;
        }

        else // process is partially scheduled
        {
            if (BT[p] == V[p].b) // process is being scheduled for the first time
                V[p].ir = t; // record initial response time

            BT[p] -= (V[AP+1].a-t); // decrement burst time
            t = V[AP+1].a; // update time
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
    cout << "Welcome to C++ Shortest Remaining Time First (SRTF) CPU Scheduler !" << endl << endl;

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

        P.c = P.t = P.w = P.r = P.ir = 0; // other times
        V.push_back(P);
    }

    SRTF(V);
    cout << endl << endl << "Thank you for using C++ SRTF CPU Scheduler. Bye Bye !";
}