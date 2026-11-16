#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;

struct Process{
    int id, arrival, burst;
};
// FCFS orders by arrival; SJF orders by burst, then arrival, then input ID.
struct Earlier{
    bool operator()(Process a, Process b) const{
        if(a.arrival != b.arrival) return a.arrival > b.arrival;
        return a.id > b.id;
    }
};
struct Shorter{
    bool operator()(Process a, Process b) const{
        if(a.burst != b.burst) return a.burst > b.burst;
        return Earlier()(a, b);
    }
};
void schedule(Process p[], int n, bool sjf){
    priority_queue<Process, vector<Process>, Earlier> arrivals;
    priority_queue<Process, vector<Process>, Shorter> shortest;
    queue<Process> ready;
    for(int i = 0; i < n; i++) arrivals.push(p[i]);
    long long time = 0, totalWait = 0, totalTurn = 0;
    cout << "\nPID\tArrival\tBurst\tStart\tFinish\tWait\tTurnaround\n";
    for(int completed = 0; completed < n; completed++){
        if(ready.empty() && shortest.empty() && !arrivals.empty() && time < arrivals.top().arrival)
            time = arrivals.top().arrival; // CPU is idle until the next arrival.
        while(!arrivals.empty() && arrivals.top().arrival <= time){
            Process next = arrivals.top(); arrivals.pop();
            if(sjf) shortest.push(next);
            else ready.push(next);
        }
        Process current;
        if(sjf){ current = shortest.top(); shortest.pop(); }
        else{ current = ready.front(); ready.pop(); }
        long long start = time;
        time += current.burst; // Run to completion: no preemption.
        long long wait = start - current.arrival, turn = time - current.arrival;
        totalWait += wait; totalTurn += turn;
        cout << current.id << "\t" << current.arrival << "\t" << current.burst << "\t"
             << start << "\t" << time << "\t" << wait << "\t" << turn << "\n";
    }
    cout << fixed << setprecision(2) << "Average waiting time: " << double(totalWait) / n
         << "\nAverage turnaround time: " << double(totalTurn) / n << "\n";
}
int main(){
    Process p[100]; int n, choice;
    cout << "Enter process count (1 to 100): ";
    if(!(cin >> n) || n < 1 || n > 100) return 0;
    cout << "Enter arrival time and burst time for each process:\n";
    for(int i = 0; i < n; i++){
        p[i].id = i + 1;
        if(!(cin >> p[i].arrival >> p[i].burst) || p[i].arrival < 0 || p[i].burst <= 0) return 0;
    }
    while(true){
        cout << "\n===== Scheduling Menu =====\n1. FCFS\n2. SJF\n3. Exit\nEnter choice: ";
        if(!(cin >> choice) || choice == 3) break;
        if(choice == 1 || choice == 2) schedule(p, n, choice == 2);
        else cout << "Invalid choice.\n";
    }
}
