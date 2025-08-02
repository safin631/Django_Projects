/*
    * Code for first fit, best fit, and worst fit memory allocation algorithms in C++
*/
#include<bits/stdc++.h>
using namespace std;
int main(){
    cout << "Enter number of memory blocks: ";
    int n; cin >> n;
    vector<int> space(n);
    cout << "Enter sizes of memory blocks:\n";
    for(int i = 0; i < n; i++) {
        cin >> space[i];
    }

    cout << "Enter number of processes: ";
    int pn; cin >> pn;
    vector<int> process(pn), allocate(pn, -1);
    cout << "Enter sizes of processes:\n";
    for(int i = 0; i < pn; i++) {
        cin >> process[i];
    }

    // First Fit
    cout << "First Fit Allocation:\n";
    for(int i = 0; i < pn; i++) {
        for(int j = 0; j < n; j++) {
            if(space[j] >= process[i] && allocate[i] == -1) {
                allocate[i] = j;
                space[j] -= process[i];
                cout << "Process " << i << " allocated to block " << j << endl;
                break;
            }
        }
    }

    // Best Fit
    cout << "Best Fit Allocation:\n";
    fill(allocate.begin(), allocate.end(), -1);
    vector<int> temp_space = space;
    for(int i = 0; i < pn; i++) {
        int best_idx = -1;
        for(int j = 0; j < n; j++) {
            if(temp_space[j] >= process[i] && (best_idx == -1 || temp_space[j] < temp_space[best_idx])) {
                best_idx = j;
            }
        }
        if(best_idx != -1) {
            allocate[i] = best_idx;
            temp_space[best_idx] -= process[i];
            cout << "Process " << i << " allocated to block " << best_idx << endl;
        }
    }

    // Worst Fit
    cout << "Worst Fit Allocation:\n";
    fill(allocate.begin(), allocate.end(), -1);
    temp_space = space;
    for(int i = 0; i < pn; i++) {
        int worst_idx = -1;
        for(int j = 0; j < n; j++) {
            if(temp_space[j] >= process[i] && (worst_idx == -1 || temp_space[j] > temp_space[worst_idx])) {
                worst_idx = j;
            }
        }
        if(worst_idx != -1) {
            allocate[i] = worst_idx;
            temp_space[worst_idx] -= process[i];
            cout << "Process " << i << " allocated to block " << worst_idx << endl;
        }
    }

    return 0;
}