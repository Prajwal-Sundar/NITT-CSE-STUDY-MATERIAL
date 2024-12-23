#include "bits/stdc++.h"
using namespace std;

struct Job
{
    int D; // deadline
    int P; // penalty
    int pos; // position of job
    int B; // burst time
    
    Job(int position)
    {
        D = 0; P = 0; pos = position; B = 0;
    }
};

// Compare function for sorting
bool comp(struct Job * job1, struct Job * job2)
{
    return (job1->P >= job2->P); // retain if penalty is already in descending order
}

// Function to schedule jobs and print maximum profit
void schedule(vector<struct Job*> jobs)
{
    sort(jobs.begin(), jobs.end(), comp); // sort
    int n = jobs.size();
    
    int maxD = INT_MIN; // calculation of maximum deadline
    for (int i = 0; i < n; i++) maxD = max(maxD, jobs[i]->D);

    int J[maxD]; // array to store job sequence
    memset(J, -1, sizeof(J));
    
    int penalty = 0; // storage of profit
    for (int i = 0; i < n; i++) penalty += jobs[i]->P;
    cout << endl;

    for (int i = 0; i < n; i++) // loop through jobs
    {
        int c = 0; // count of free slots
        int first, last = -1; // pointers to first and last free slots

        for (int j = jobs[i]->D-1; j >= 0 && c < jobs[i]->B; j--)
        {
            if (J[j] == -1) // free slot located
            {
                if (last == -1) // first free slot
                    last = j;
                c++; // increment number of free slots
                first = j; // shift pointer position
            }
        }

        if (c < jobs[i]->B) // enough slots are not available
            continue; // proceed to next iteration
        
        while (1) // loop to form continuous slots
        {
            if (J[first] != -1) // current slot is full
            {
                first++;
                continue; // go to next iteration
            }
            
            // Now current slot is empty, try to move it as right as possible

            int next; // position of next filled slot
            for (next = first+1; next <= last; next++)
            {
                if (J[next] != -1) // filled slot located
                {
                    swap(J[first], J[next]); // swap filled and empty slots
                    break; // break out of for loop
                }
            }

            if (next > last) // no more filled slots, while loop can be terminated
                break; // break out of while loop
            else
                first++;
        }

        penalty -= jobs[i]->P; // remove penalty of currently scheduled job
        for (int j = last; j > last-jobs[i]->B; j--)
            J[j] = i; // schedule job at current slot
    }

    cout << endl << "The job schedule is : 0";
    for (int i = 0; i < maxD;)
    {
        if (J[i] == -1) // empty slot
            cout << " [-] " << (++i);
        else // non-empty slot
        {
            cout << " [J" << jobs[J[i]]->pos << "] " << (i+jobs[J[i]]->B);
            i += jobs[J[i]]->B; // next slot
        }
    }

    cout << endl << "The optimised minimum penalty to be paid is : " << penalty << endl;
}

// Main Function
int main()
{
    cout << "Welcome to C++ Job Penalty Deadline Sequencing !" << endl << endl;

    int n; // number of jobs
    cout << "Enter the number of jobs to be performed : ";
    cin >> n;

    vector<struct Job*> jobs; // array of jobs
    for (int i = 0; i < n; i++) jobs.push_back(new Job(i+1));
    cout << "Enter the deadlines of your jobs : ";
    for (int i = 0; i < n; i++) cin >> jobs[i]->D;
    cout << "Enter the penalties of your jobs : ";
    for (int i = 0; i < n; i++) cin >> jobs[i]->P;
    cout << "Enter the burst times of your jobs : ";
    for (int i = 0; i < n; i++) cin >> jobs[i]->B;

    schedule(jobs); // show results
    cout << endl << "Thank you for using C++ Job Penalty Deadline Sequencing. Bye Bye !";
}