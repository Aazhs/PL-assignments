#include <iostream>
#include <string>
using namespace std;

struct Patient
{
    string name;
    int priority;
};

void insert(Patient queue[], int& count, Patient patient)
{
    int i = count - 1;
    // Smaller number = higher priority. Shift less urgent patients right.
    // Equal priorities are not shifted, so they keep their arrival order.
    while (i >= 0 && queue[i].priority > patient.priority)
    {
        queue[i + 1] = queue[i];
        i--;
    }
    queue[i + 1] = patient;
    count++;
}

void serve(Patient queue[], int& count)
{
    if (count == 0)
    {
        cout << "Queue empty.\n";
        return;
    }
    cout << "Serving: " << queue[0].name << endl;
    // Remove the front patient by moving every other patient one place left.
    for (int i = 1; i < count; i++) queue[i - 1] = queue[i];
    count--;
}

void display(Patient queue[], int count)
{
    for (int i = 0; i < count; i++)
        cout << queue[i].name << "\tPriority: " << queue[i].priority << endl;
}

int main()
{
    Patient queue[100], patient;
    int n, count = 0;
    cout << "Enter number of patients (0 to 100): ";
    if (!(cin >> n) || n < 0 || n > 100) return 0;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter patient name: ";
        if (!getline(cin >> ws, patient.name)) return 0;
        cout << "Priority (1 emergency, 2 urgent, 3 routine): ";
        if (!(cin >> patient.priority) || patient.priority < 1 || patient.priority > 3) return 0;
        insert(queue, count, patient);
    }
    cout << "Appointments in priority order:\n";
    display(queue, count);
    // Demonstrate deletion by serving the next appointment.
    serve(queue, count);
    cout << "Remaining appointments:\n";
    display(queue, count);
    return 0;
}
