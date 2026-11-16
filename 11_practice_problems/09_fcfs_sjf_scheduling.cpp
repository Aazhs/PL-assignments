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
    Queue() {
        front = -1;
        rear = -1;
    }

    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return rear == MAX - 1;
    }

    // True when process a should run before process b.
    bool comesFirst(int a, int b, Process p[], bool sjf) {
        if (sjf && p[a].burst != p[b].burst) return p[a].burst < p[b].burst;
        if (p[a].arrival != p[b].arrival) return p[a].arrival < p[b].arrival;
        return p[a].id < p[b].id;
    }

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

    int dequeue() {
        if (isEmpty()) return -1;
        int value = arr[front];
        if (front == rear) {
            front = rear = -1;
        } else {
            front++;
        }
        return value;
    }
};

void schedule(Process p[], int n, bool sjf)
{
    Queue queue;
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
                queue.enqueue(i, p, sjf);
                added[i] = true;
            }
        }

        if (queue.isEmpty())
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
                    queue.enqueue(i, p, sjf);
                    added[i] = true;
                }
            }
        }

        Process current = p[queue.dequeue()];

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
