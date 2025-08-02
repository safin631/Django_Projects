#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id, arrival, burst, remaining, completion, turnaround, waiting;
};

// Comparator for priority queue (shortest remaining time first)
struct CompareRemaining {
    bool operator()(const Process &a, const Process &b) {
        if (a.remaining == b.remaining)
            return a.arrival > b.arrival; // Tie-breaker: earlier arrival
        return a.remaining > b.remaining; // Min-heap
    }
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
        processes[i].remaining = processes[i].burst;
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrival < b.arrival;
    });

    int current_time = 0, completed_count = 0, index = 0;
    priority_queue<Process, vector<Process>, CompareRemaining> ready_queue;
    vector<Process> result;

    while (completed_count < n) {
        // Add newly arrived processes to ready queue
        while (index < n && processes[index].arrival <= current_time) {
            ready_queue.push(processes[index]);
            index++;
        }

        if (ready_queue.empty()) {
            // CPU idle: move to next arrival time
            current_time = processes[index].arrival;
            continue;
        }

        // Get process with shortest remaining time
        Process current = ready_queue.top();
        ready_queue.pop();

        // Execute for 1 time unit
        current.remaining--;
        current_time++;

        // Add newly arrived processes during this time
        while (index < n && processes[index].arrival <= current_time) {
            ready_queue.push(processes[index]);
            index++;
        }

        // If process still has time left, put back in queue
        if (current.remaining > 0) {
            ready_queue.push(current);
        } else {
            // Process finished
            current.completion = current_time;
            current.turnaround = current.completion - current.arrival;
            current.waiting = current.turnaround - current.burst;
            result.push_back(current);
            completed_count++;
        }
    }

    // Sort results by process ID
    sort(result.begin(), result.end(), [](const Process &a, const Process &b) {
        return a.id < b.id;
    });

    // Display process table
    double total_TAT = 0, total_WT = 0;
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (const auto &p : result) {
        cout << p.id << "\t" << p.arrival << "\t" << p.burst << "\t"
             << p.completion << "\t" << p.turnaround << "\t" << p.waiting << "\n";
        total_TAT += p.turnaround;
        total_WT += p.waiting;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << total_TAT / n;
    cout << "\nAverage Waiting Time: " << total_WT / n << endl;

    return 0;
}
