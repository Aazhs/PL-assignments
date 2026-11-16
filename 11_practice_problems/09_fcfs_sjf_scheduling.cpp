/*
PRACTICE PROBLEM 9: NON-PREEMPTIVE FCFS AND SJF SCHEDULING

PROBLEM:
Given processes with arrival and CPU burst times, simulate FCFS and SJF.
FCFS = First Come First Served. SJF = Shortest Job First.
Non-preemptive means a running process finishes before another can start.

EXAMPLE:
All arrive at 0: P1 burst 5, P2 burst 2, P3 burst 1.
FCFS order: P1, P2, P3. SJF order: P3, P2, P1.

HOW TO SOLVE:
1. Read arrival and burst times; assign IDs in input order.
2. Put processes that have arrived into a ready queue storing their indices.
3. Order that queue by arrival for FCFS, or by burst for SJF.
4. If no process is ready, jump the clock to the earliest remaining arrival.
5. Dequeue a process, record its start, and add its full burst to the clock.
6. Compute waiting = start - arrival and turnaround = finish - arrival.
7. Repeat until all finish, print averages, then run the other algorithm afresh.

VARIABLES / IMPORTANT POINTS:
added[i] prevents adding the same process twice; time is the simulated clock.
Only arrived processes can compete for the CPU, including under SJF.
SJF burst ties use arrival, then ID. FCFS arrival ties use ID.
Each run builds a fresh queue, so FCFS cannot change the SJF input.
*/

#include <iostream>
#include <iomanip>
using namespace std;

class Process
{
public:
    int id, arrival, burst;
};

// Adapted from PL/queue.cpp. Store process indices instead of plain values.
// Insertion orders the ready processes; dequeue still removes from front.
const int MAX = 100;

class Queue {
    int arr[MAX];
    int front;
    int rear;

public:
    // Start with an empty ready queue; each scheduling run constructs its own object.
    Queue() {
        front = -1;
        rear = -1;
    }

    // Tell the scheduler whether it must wait for another process arrival.
    bool isEmpty() {
        return front == -1;
    }

    // Guard against placing a process index outside the fixed-size array.
    bool isFull() {
        return rear == MAX - 1;
    }

    // True when process a should run before process b.
    // Compare two process indices by SJF burst or FCFS arrival, then break ties consistently.
    bool comesFirst(int a, int b, Process p[], bool sjf) {
        // Only SJF prefers shorter bursts. FCFS skips this rule and compares arrival times.
        if (sjf && p[a].burst != p[b].burst) return p[a].burst < p[b].burst;
        if (p[a].arrival != p[b].arrival) return p[a].arrival < p[b].arrival;
        return p[a].id < p[b].id;
    }

    // Insert an arrived process index into the correct scheduling position.
    void enqueue(int value, Process p[], bool sjf) {
        if (isFull()) return;
        if (isEmpty()) front = 0;
        // Insert in FCFS or SJF order, shifting later processes right.
        int i = rear;
        while (i >= front && comesFirst(value, arr[i], p, sjf)) {
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = value;
        rear++;
    }

    // Return the front process index and remove it; -1 indicates an empty queue.
    int dequeue() {
        if (isEmpty()) return -1;
        // The array stores an index, not a Process copy; p[value] is the chosen process.
        int value = arr[front];
        if (front == rear) {
            front = rear = -1;
        } else {
            front++;
        }
        return value;
    }
};

// Simulate the clock and ready queue, run each job fully, and calculate times and averages.
void schedule(Process p[], int n, bool sjf)
{
    Queue queue;
    bool added[100] = {}; // True once a process has entered the ready queue.
    long long time = 0, totalWait = 0, totalTurn = 0;
    cout << "PID\tArrival\tBurst\tStart\tFinish\tWait\tTurnaround\n";

    for (int completed = 0; completed < n; completed++)
    {
        // Add processes that arrived while the previous process was running.
        // Scan the original inputs so processes arriving during the last burst can now join.
        for (int i = 0; i < n; i++)
        {
            if (!added[i] && p[i].arrival <= time)
            {
                queue.enqueue(i, p, sjf);
                added[i] = true;
            }
        }

        if (queue.isEmpty())
        {
            // CPU is idle: find the earliest arrival still to come.
            // No next process has been selected yet; the first unadded entry becomes the candidate.
            int next = -1;
            for (int i = 0; i < n; i++)
            {
                if (!added[i])
                {
                    if (next == -1 || p[i].arrival < p[next].arrival) next = i;
                }
            }
            // Jump directly to that arrival instead of advancing an idle clock one unit at a time.
            time = p[next].arrival;
            for (int i = 0; i < n; i++)
            {
                if (!added[i] && p[i].arrival <= time)
                {
                    queue.enqueue(i, p, sjf);
                    added[i] = true;
                }
            }
        }

        Process current = p[queue.dequeue()];

        // This process starts now. Its finish is the clock value after adding its entire burst.
        long long start = time;
        time += current.burst; // Non-preemptive: run this process to completion.
        // Waiting counts only time before CPU service, while turnaround includes the service time.
        long long wait = start - current.arrival;
        long long turn = time - current.arrival;
        // Accumulate each completed process once so dividing by n gives the mean.
        totalWait += wait;
        totalTurn += turn;
        cout << current.id << "\t" << current.arrival << "\t" << current.burst << "\t"
             << start << "\t" << time << "\t" << wait << "\t" << turn << endl;
    }
    cout << fixed << setprecision(2);
    cout << "Average waiting time: " << double(totalWait) / n << endl;
    cout << "Average turnaround time: " << double(totalTurn) / n << endl;
}

// Read the processes once, then simulate FCFS and SJF independently on the same data.
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
