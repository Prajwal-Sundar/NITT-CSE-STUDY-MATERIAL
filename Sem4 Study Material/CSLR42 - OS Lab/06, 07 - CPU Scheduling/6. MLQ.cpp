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
    int q; // queue number
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

// Print MLQ Gantt Chart and Table
void MLQ(vector<struct Process> V, int q)
{
    cout << endl << "Gantt Chart :-" << endl << 0;
    sort(V.begin(), V.end(), comp); // sort based on arrival time

    int t = 0; // current timesnap
    int AP = -1; // arrival pointer

    int s = V.size(); // number of processes
    int c = s; // processes left to schedule

    int BT[s]; // array of burst times
    for (int i = 0; i < s; i++)
        BT[i]=  V[i].b; // copy burst times
    
    double s_tt = 0, s_wt = 0, s_rt = 0, s_it = 0; // sum of times variable
    
    queue<int> Q1; // first queue - for RR
    queue<int> Q2; // second queue - for FCFS
    int preempted = -1; // preempted process

    while (c)
    {
        int prev_AP = AP; // previous position of AP
        // Set position of arrival pointer
        for (int i = AP+1; i < s; i++)
        {
            if (V[i].a > t) break;
            else AP++;
        }
        // Processes till AP's position have now arrived

        // Push newly arrived processes into their respective queues
        for (int i = prev_AP+1; i <= AP; i++)
        {
            if (BT[i]) // process is not over
            {
                if (V[i].q == 1) Q1.push(i); // push into RR queue
                else if (V[i].q == 2) Q2.push(i); // push into FCFS queue
            }
        }

        if (preempted != -1)
            Q1.push(preempted); // push the previously preempted process into the RR queue
        preempted = -1;

        if (Q1.empty() && Q2.empty()) // both queues are empty, some idle time has to be spent
        {
            s_it += V[AP+1].a-t; // add idle time
            t = V[AP+1].a; // increment time

            cout << " [-] " << t;
            continue; // continue to next iteration
        }

        int p = -1; // scheduling process
        int b = 0; // burst time
        int flag = 0; // fully completed or not

        // Now at least one of the queues is non-empty
        if (!Q1.empty()) // schedule process in RR queue with higher priority
        {
            p = Q1.front(); // schedule frontmost process of RR queue
            Q1.pop();

            if (BT[p] == V[p].b) // first time schedule
                V[p].ir = t; // record initial response moment

            if (BT[p] <= q) // schedule fully
            {
                b = BT[p]; // burst time of p
                BT[p] = 0; // process over
                flag = 1; // fully scheduled
            }

            else // schedule partially
            {
                b = q; // only one time quantum
                BT[p] -= q;
                flag = 0; // not fully scheduled
            }
        }

        else // RR queue is empty, schedule process in FCFS queue with lower priority
        {
            p = Q2.front(); // schedule frontmost process of FCFS queue
            Q2.pop();

            if (BT[p] == V[p].b) // first time schedule
                V[p].ir = t; // record initial response moment

            b = BT[p]; // burst time of p
            BT[p] = 0; // process over
            flag = 1; // fully scheduled
        }

        t += b; // increment burst time
        cout << " [P" << V[p].n << "] " << t;

        if (flag) // fully scheduled
        {
            c--;

            V[p].c = t; // completing time
            V[p].t = V[p].c - V[p].a; // turnaround time
            V[p].w = V[p].t - V[p].b; // waiting time
            V[p].r = V[p].ir - V[p].a; // response time

            s_tt += V[p].t;
            s_wt += V[p].w;
            s_rt += V[p].r; // add times
        }

        else // not fully scheduled
            preempted = p;
    }

    sort(V.begin(), V.end(), compP); // sort back based on position
    cout << endl << endl << "\t" << "AT" << "\t" << "BT" << "\t" << "CT" << "\t" << "TT" << "\t" << "WT" << "\t" << "RT" << endl;
    for (int i = 0; i < s; i++)
        cout << "P" << V[i].n << "\t" << V[i].a << "\t" << V[i].b << "\t" << V[i].c << "\t" << V[i].t << "\t" << V[i].w << "\t" << V[i].r << endl;
    
    cout << endl << "Average Turnaround Time = " << (s_tt / s);
    cout << endl << "Average Waiting Time = " << (s_wt / s);
    cout << endl << "Average Response Time = " << (s_rt / s);
    cout << endl << "Total Idle Time = " << s_it;
}

int main()
{
    cout << "Welcome to C++ Multi Level Queue (MLQ) CPU Scheduler !" << endl;

    // Describe given multi-level queue
    cout << "Queue 1 follows RR Scheduling while Queue 2 follows FCFS Scheduling." << endl << endl;

    int num; // number of processes
    cout << "Enter the number of processes : ";
    cin >> num;

    vector<struct Process> V; // vector of processes
    cout << "For each process, enter (pid arrival_time burst_time queue_number) :-" << endl;
    for (int i = 0; i < num; i++)
    {
        struct Process P; // process
        cout << "Process " << i << " : ";
        cin >> P.n >> P.a >> P.b >> P.q; // get times as user input

        P.c = P.t = P.w = P.r = P.ir = 0; // other times
        V.push_back(P);
    }

    int q; // time quantum
    cout << "Enter time quantum for the first queue : ";
    cin >> q;

    MLQ(V, q); // print Gantt chart
    cout << endl << endl << "Thank you for using C++ MLQ CPU Scheduler. Bye Bye !";
}