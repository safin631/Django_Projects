#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id, arrival, burst, priority, completion, turnaround, waiting;
};

int main() {
    cout << "Enter number of processes: ";
    int n; cin >> n;

    vector<Process> processes(n);

    cout << "Enter arrival times:\n";
    for (int i = 0; i < n; ++i) {
        cin >> processes[i].arrival;
        processes[i].id = i + 1;
    }

    cout << "Enter burst times:\n";
    for (int i = 0; i < n; ++i) {
        cin >> processes[i].burst;
    }

    cout << "Enter priorities (lower number = higher priority):\n";
    for (int i = 0; i < n; ++i) {
        cin >> processes[i].priority;
    }
    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrival < b.arrival;
    });

    int current_time = 0;
    vector<Process> completed;

    while (!processes.empty()) {
        // Find all processes that have arrived
        vector<Process> ready;
        for (const auto &p : processes) {
            if (p.arrival <= current_time) {
                ready.push_back(p);
            }
        }

        if (ready.empty()) {
            // CPU idle: jump to next process arrival
            current_time = processes[0].arrival;
            continue;
        }

        // Select process with highest priority
        auto next_proc = min_element(ready.begin(), ready.end(), [](const Process &a, const Process &b) {
            if (a.priority == b.priority)
                return a.arrival < b.arrival; // Tiebreaker: arrival time
            return a.priority < b.priority; 
        });

        current_time += next_proc->burst;
        next_proc->completion = current_time;
        next_proc->turnaround = next_proc->completion - next_proc->arrival;
        next_proc->waiting = next_proc->turnaround - next_proc->burst;

        completed.push_back(*next_proc);

        // Remove the executed process from the list
        processes.erase(remove_if(processes.begin(), processes.end(),
            [&](const Process &p) { return p.id == next_proc->id; }),
                processes.end());
    }

    // Sort by process ID for final display
    sort(completed.begin(), completed.end(), [](const Process &a, const Process &b) {
        return a.id < b.id;
    });

    // Display process table
    double total_TAT = 0, total_WT = 0;
    cout << "\nPID\tAT\tBT\tP\tCT\tTAT\tWT\n";
    for (const auto &p : completed) {
        cout << p.id << "\t" << p.arrival << "\t" << p.burst << "\t" << p.priority << "\t"
             << p.completion << "\t" << p.turnaround << "\t" << p.waiting << "\n";
        total_TAT += p.turnaround;
        total_WT += p.waiting;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << total_TAT / n;
    cout << "\nAverage Waiting Time: " << total_WT / n << endl;

    return 0;
}
