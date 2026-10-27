#include <iostream>
using namespace std;

const int MAX = 5;

// Circular queue storing indices of processes waiting for the CPU
class CircularQueue {
    int arr[MAX];
    int front;
    int rear;
    int count;

public:
    CircularQueue() {
        front = 0;
        // rear starts at -1 so the first enqueue puts the value at index 0
        rear = -1;
        count = 0;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == MAX;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is full. Cannot insert.\n";
            return;
        }
        // Move rear forward; % MAX wraps it back to 0 after the last index
        rear = (rear + 1) % MAX;
        arr[rear] = value;
        count++;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot delete.\n";
            return -1;
        }
        int value = arr[front];
        // Move front forward, wrapping around the same way
        front = (front + 1) % MAX;
        count--;
        return value;
    }

    void display() {
        cout << "Ready queue (front -> rear): ";
        // Visit 'count' items starting at front, wrapping around with % MAX
        for (int i = 0, idx = front; i < count; i++, idx = (idx + 1) % MAX) {
            cout << "P" << arr[idx] + 1 << " ";
        }
        cout << "\n";
    }
};

class RoundRobin {
    int n;
    int quantum;
    int arrival[MAX];
    int burst[MAX];
    int remaining[MAX];
    int completion[MAX];
    int turnaround[MAX];
    int waiting[MAX];

public:
    RoundRobin(int q) {
        n = MAX;
        quantum = q;
        int at[MAX] = {0, 1, 2, 3, 4};
        int bt[MAX] = {5, 3, 1, 2, 3};
        for (int i = 0; i < n; i++) {
            arrival[i] = at[i];
            burst[i] = bt[i];
            remaining[i] = bt[i];
        }
    }

    void schedule() {
        CircularQueue q;
        bool added[MAX] = {false};
        int time = 0, done = 0;

        cout << "\nGantt chart:\n";
        while (done < n) {
            // Add all processes that have arrived by the current time
            for (int i = 0; i < n; i++) {
                if (!added[i] && arrival[i] <= time) {
                    q.enqueue(i);
                    added[i] = true;
                }
            }

            // CPU idle: jump to the next arrival
            if (q.isEmpty()) {
                time++;
                continue;
            }

            int p = q.dequeue();
            // Run for one time quantum, or less if the process finishes sooner
            int run = remaining[p] < quantum ? remaining[p] : quantum;

            cout << "| P" << p + 1 << " (" << time << "-" << time + run << ") ";
            time += run;
            remaining[p] -= run;

            // Processes arriving during this slice go before the preempted one
            for (int i = 0; i < n; i++) {
                if (!added[i] && arrival[i] <= time) {
                    q.enqueue(i);
                    added[i] = true;
                }
            }

            // Not finished: back to the end of the queue. Finished: record when it completed.
            if (remaining[p] > 0) {
                q.enqueue(p);
            } else {
                completion[p] = time;
                done++;
            }
        }
        cout << "|\n";
    }

    void display() {
        float totalTAT = 0, totalWT = 0;

        cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
        cout << "-------------------------------------------\n";
        for (int i = 0; i < n; i++) {
            // Turnaround = completion - arrival, Waiting = turnaround - burst
            turnaround[i] = completion[i] - arrival[i];
            waiting[i] = turnaround[i] - burst[i];
            totalTAT += turnaround[i];
            totalWT += waiting[i];
            cout << "P" << i + 1 << "\t" << arrival[i] << "\t" << burst[i] << "\t"
                 << completion[i] << "\t" << turnaround[i] << "\t" << waiting[i] << "\n";
        }
        cout << "\nAverage Turnaround Time: " << totalTAT / n << "\n";
        cout << "Average Waiting Time: " << totalWT / n << "\n";
    }
};

int main() {
    int quantum;

    cout << "===== ROUND ROBIN CPU SCHEDULING =====\n";
    cout << "Enter time quantum: ";
    cin >> quantum;

    if (cin.fail() || quantum <= 0) {
        cout << "Invalid time quantum.\n";
        return 1;
    }

    RoundRobin rr(quantum);
    rr.schedule();
    rr.display();

    return 0;
}
