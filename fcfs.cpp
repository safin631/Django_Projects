#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid, arrival, burst, completion, turnaround, waiting;
};

int main() {
    cout << "Enter the number of processes: ";
    int n; cin >> n;

    vector<Process> p(n);

    cout << "Enter arrival times: ";
    for (int i = 0; i < n; ++i) {
        p[i].pid = i + 1;
        cin >> p[i].arrival;
    }

    cout << "Enter burst times: ";
    for (int i = 0; i < n; ++i) {
        cin >> p[i].burst;
    }

    sort(p.begin(), p.end(), [](const Process &a, const Process &b){
        return a.arrival < b.arrival;
    });

    int currentTime = 0;
    double totalTAT = 0, totalWT = 0;

    for (int i = 0; i < n; ++i) {
        if (currentTime < p[i].arrival) {
            currentTime = p[i].arrival; // CPU idle
        }
        p[i].completion = currentTime + p[i].burst;
        currentTime = p[i].completion;

        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;

        totalTAT += p[i].turnaround;
        totalWT += p[i].waiting;
    }

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &p : p) {
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t"
             << p.completion << "\t" << p.turnaround << "\t" << p.waiting << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;
    cout << "Average Waiting Time: " << totalWT / n << endl;

    return 0;
}