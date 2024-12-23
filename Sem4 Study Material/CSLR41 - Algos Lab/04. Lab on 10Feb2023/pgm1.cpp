#include "bits/stdc++.h"
using namespace std;

struct Job
{
    int D; // deadline
    int P; // profit
    int pos; // position of job

    Job(int position)
    {
        D = 0; P = 0; pos = position;
    }
};

// Compare function for sorting
bool comp(struct Job * job1, struct Job * job2)
{
    return (job1->P >= job2->P); // retain if profit is already in descending order
}

// Function to schedule jobs and print maximum profit
void schedule(vector<struct Job*> jobs, int n)
{
    sort(jobs.begin(), jobs.end(), comp); // sort
    
    int maxD = INT_MIN; // calculation of maximum deadline
    for (int i = 0; i < n; i++) maxD = max(maxD, jobs[i]->D);

    int J[maxD]; // array to store job sequence
    memset(J, 0, sizeof(J));
    int profit = 0; // storage of profit
    cout << endl;

    for (int i = 0; i < n; i++) // loop through profits
    {
        int flag = 0;
        for (int j = jobs[i]->D-1; j >= 0; j--)
        {
            if (!J[j]) // empty slot located
            {
                flag = 1; // job successfully scheduled
                J[j] = jobs[i]->pos; // schedule job
                profit += jobs[i]->P; // add profit
                cout << "Job J" << jobs[i]->pos << " scheduled at slot [" << j << "-" << j+1 << "], profit = " << jobs[i]->P << endl;
                break;
            }
        }
        if (!flag) cout << "Sorry, job J" << jobs[i]->pos << " could not be scheduled" << endl;
    }

    cout << endl << "The job schedule is : ";
    for (int i = 0; i < maxD; i++) cout << "J" << J[i] << " ";

    cout << endl << "The optimised maximum profit attained is : " << profit << endl;
}

// Main Function
int main()
{
    cout << "Welcome to C++ Job Deadline Sequencing !" << endl << endl;

    int n; // number of jobs
    cout << "Enter the number of jobs to be performed : ";
    cin >> n;

    vector<struct Job*> jobs; // array of jobs
    for (int i = 0; i < n; i++) jobs.push_back(new Job(i));
    cout << "Enter the deadlines of your jobs : ";
    for (int i = 0; i < n; i++) cin >> jobs[i]->D;
    cout << "Enter the profits of your jobs : ";
    for (int i = 0; i < n; i++) cin >> jobs[i]->P;

    schedule(jobs, n); // show results
    cout << endl << "Thank you for using C++ Job Deadline Sequencing. Bye Bye !";
}