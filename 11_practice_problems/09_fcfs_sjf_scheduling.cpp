#include <iostream>
#include <iomanip>
using namespace std;

// How this program works:
// FCFS picks the earliest arrival among ready processes.
// SJF picks the smallest burst among ready processes.
// A future arrival must wait until its arrival time before it can be chosen.

// arrival = when a process becomes ready; burst = time it needs on the CPU.
struct Process{
    int id, arrival, burst;
};

// Use an ordinary array as the ready queue, avoiding STL comparators.
// The queue stores process indices, so ready[0] refers to p[ready[0]].
void schedule(Process p[], int n, bool sjf){
    int ready[100];
    int count = 0;
    bool added[100] = {}; // True once a process has entered the ready queue.
    long long time = 0;
    long long totalWait = 0;
    long long totalTurn = 0;

    cout << "\nPID\tArrival\tBurst\tStart\tFinish\tWait\tTurnaround\n";
    for(int completed = 0; completed < n; completed++){
        // Add every process that has arrived since the previous completion.
        for(int i = 0; i < n; i++){
            if(!added[i] && p[i].arrival <= time){
                ready[count] = i;
                count++;
                added[i] = true;
            }
        }

        if(count == 0){
            // No process is ready. Jump to the earliest remaining arrival.
            int next = -1;
            for(int i = 0; i < n; i++){
                if(!added[i]){
                    if(next == -1 || p[i].arrival < p[next].arrival) next = i;
                }
            }
            time = p[next].arrival;
            for(int i = 0; i < n; i++){
                if(!added[i] && p[i].arrival <= time){
                    ready[count] = i;
                    count++;
                    added[i] = true;
                }
            }
        }

        // Find which ready-queue entry should run next.
        int best = 0;
        for(int i = 1; i < count; i++){
            int a = ready[i];
            int b = ready[best];
            bool choose = false;
            if(sjf && p[a].burst != p[b].burst){
                choose = p[a].burst < p[b].burst; // SJF: shortest job first.
            }
            else if(p[a].arrival != p[b].arrival){
                choose = p[a].arrival < p[b].arrival; // FCFS or SJF tie.
            }
            else{
                choose = p[a].id < p[b].id; // Same arrival: input order.
            }
            if(choose) best = i;
        }

        Process current = p[ready[best]];
        // Remove that entry by shifting the remaining queue entries left.
        for(int i = best; i < count - 1; i++) ready[i] = ready[i + 1];
        count--;

        long long start = time;
        time += current.burst; // Non-preemptive: finish this job before choosing again.
        long long wait = start - current.arrival;
        long long turn = time - current.arrival;
        totalWait += wait;
        totalTurn += turn;
        cout << current.id << "\t" << current.arrival << "\t" << current.burst << "\t"
             << start << "\t" << time << "\t" << wait << "\t" << turn << "\n";
    }
    // Waiting = start - arrival; turnaround = finish - arrival.
    cout << fixed << setprecision(2) << "Average waiting time: " << double(totalWait) / n
         << "\nAverage turnaround time: " << double(totalTurn) / n << "\n";
}
// Program starts here: read inputs, then perform the requested operations.
int main(){
    Process p[100]; int n, choice;
    cout << "Enter process count (1 to 100): ";
    if(!(cin >> n) || n < 1 || n > 100) return 0;
    cout << "Enter arrival time and burst time for each process:\n";
    for(int i = 0; i < n; i++){
        p[i].id = i + 1;
        if(!(cin >> p[i].arrival >> p[i].burst) || p[i].arrival < 0 || p[i].burst <= 0) return 0;
    }
    // Repeat the menu until Exit is chosen or the input ends.
    while(true){
        cout << "\n===== Scheduling Menu =====\n1. FCFS\n2. SJF\n3. Exit\nEnter choice: ";
        if(!(cin >> choice) || choice == 3) break;
        if(choice == 1 || choice == 2) schedule(p, n, choice == 2);
        else cout << "Invalid choice.\n";
    }
}
