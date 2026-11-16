#include <iostream>
#include <iomanip>
using namespace std;

struct Process
{
    int id, arrival, burst;
};

void schedule(Process p[], int n, bool sjf)
{
    int ready[100], count = 0;
    bool added[100] = {}; // True once a process has entered the ready queue.
    long long time = 0, totalWait = 0, totalTurn = 0;
    cout << "PID\tArrival\tBurst\tStart\tFinish\tWait\tTurnaround\n";

    for (int completed = 0; completed < n; completed++)
    {
        // Add processes that arrived while the previous process was running.
        for (int i = 0; i < n; i++)
        {
            if (!added[i] && p[i].arrival <= time)
            {
                ready[count] = i;
                count++;
                added[i] = true;
            }
        }

        if (count == 0)
        {
            // CPU is idle: find the earliest arrival still to come.
            int next = -1;
            for (int i = 0; i < n; i++)
            {
                if (!added[i])
                {
                    if (next == -1 || p[i].arrival < p[next].arrival) next = i;
                }
            }
            time = p[next].arrival;
            for (int i = 0; i < n; i++)
            {
                if (!added[i] && p[i].arrival <= time)
                {
                    ready[count] = i;
                    count++;
                    added[i] = true;
                }
            }
        }

        // Find the next process in the array-based ready queue.
        int best = 0;
        for (int i = 1; i < count; i++)
        {
            int a = ready[i];
            int b = ready[best];
            bool choose;
            if (sjf && p[a].burst != p[b].burst)
                choose = p[a].burst < p[b].burst; // SJF: smaller burst wins.
            else if (p[a].arrival != p[b].arrival)
                choose = p[a].arrival < p[b].arrival; // FCFS, or SJF tie.
            else
                choose = p[a].id < p[b].id; // Same arrival: input order.
            if (choose) best = i;
        }

        Process current = p[ready[best]];
        // Remove the chosen process from the ready queue.
        for (int i = best; i < count - 1; i++) ready[i] = ready[i + 1];
        count--;

        long long start = time;
        time += current.burst; // Non-preemptive: run this process to completion.
        long long wait = start - current.arrival;
        long long turn = time - current.arrival;
        totalWait += wait;
        totalTurn += turn;
        cout << current.id << "\t" << current.arrival << "\t" << current.burst << "\t"
             << start << "\t" << time << "\t" << wait << "\t" << turn << endl;
    }
    cout << fixed << setprecision(2);
    cout << "Average waiting time: " << double(totalWait) / n << endl;
    cout << "Average turnaround time: " << double(totalTurn) / n << endl;
}

int main()
{
    Process p[100];
    int n;
    cout << "Enter process count (1 to 100): ";
    if (!(cin >> n) || n < 1 || n > 100) return 0;
    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        if (!(cin >> p[i].arrival >> p[i].burst) || p[i].arrival < 0 || p[i].burst <= 0) return 0;
    }
    // Each call builds a fresh queue from the same original processes.
    cout << "\nFCFS:\n";
    schedule(p, n, false);
    cout << "\nSJF:\n";
    schedule(p, n, true);
    return 0;
}
