#include<bits/stdc++.h>
using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int remainingTime;
};

void calculateTimes(Process proc[], int n) {
    int currentTime = 0;
    int completedProcesses = 0;
    
    while (completedProcesses < n) {
        int idx = -1;
        int minRemainingTime = INT_MAX;

        // Find the process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0 && proc[i].remainingTime < minRemainingTime) {
                minRemainingTime = proc[i].remainingTime;
                idx = i;
            }
        }

        if (idx != -1) {
            // Process the selected process for one unit of time
            proc[idx].remainingTime--;
            currentTime++;

            // Check if the process is completed
            if (proc[idx].remainingTime == 0) {
                proc[idx].completionTime = currentTime;
                completedProcesses++;
            }
        } else {
            // If no process is available, just increment the time
            currentTime++;
        }
    }
}

void calculateTurnaroundTime(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaroundTime = proc[i].completionTime - proc[i].arrivalTime;
    }
}

void calculateWaitingTime(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
    }
}

void displayProcessDetails(Process proc[], int n) {
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << proc[i].pid << "\t\t" 
             << proc[i].arrivalTime << "\t\t" 
             << proc[i].burstTime << "\t\t" 
             << proc[i].completionTime << "\t\t" 
             << proc[i].turnaroundTime << "\t\t" 
             << proc[i].waitingTime << endl;
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    Process proc[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter Process " << i + 1 << " (ID, Arrival Time, Burst Time): ";
        cin >> proc[i].pid >> proc[i].arrivalTime >> proc[i].burstTime;
        proc[i].remainingTime = proc[i].burstTime; // Initialize remaining time
    }

    calculateTimes(proc, n);
    calculateTurnaroundTime(proc, n);
    calculateWaitingTime(proc, n);

    cout << "\nShortest Remaining Time First (SRTF) Scheduling Results:\n";
    displayProcessDetails(proc, n);

    return 0;
}
