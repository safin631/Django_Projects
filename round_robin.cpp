#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id, arrival, burst, remaining, completion, turnaround, waiting;
};

int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;

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

    cout << "Enter time quantum: ";
    cin >> quantum;

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrival < b.arrival;
    });

    queue<Process> ready_queue;
    int current_time = 0, index = 0;
    vector<Process> completed;

    // Add the first arriving process to the queue
    ready_queue.push(processes[index++]);

    while (!ready_queue.empty()) {
        Process current = ready_queue.front();
        ready_queue.pop();

        // Execute for min(time quantum, remaining burst time)
        int exec_time = min(quantum, current.remaining);
        current.remaining -= exec_time;
        current_time = max(current_time, current.arrival) + exec_time;

        // Add newly arrived processes to the queue
        while (index < n && processes[index].arrival <= current_time) {
            ready_queue.push(processes[index++]);
        }

        if (current.remaining > 0) {
            // Not finished: put back into the queue
            current.arrival = current_time; // update arrival to avoid starvation
            ready_queue.push(current);
        } else {
            // Finished
            current.completion = current_time;
            current.turnaround = current.completion - current.arrival + (current.burst - current.remaining);
            current.waiting = current.turnaround - current.burst;
            completed.push_back(current);
        }

        // If queue is empty but there are still processes left, add next arriving process
        if (ready_queue.empty() && index < n) {
            ready_queue.push(processes[index++]);
        }
    }

    // Sort results by process ID
    sort(completed.begin(), completed.end(), [](const Process &a, const Process &b) {
        return a.id < b.id;
    });

    // Display process table
    double total_TAT = 0, total_WT = 0;
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (const auto &p : completed) {
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
