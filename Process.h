#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    char pxx[3]; // process num
    int arrivalTime;
    int burstTime;
    int vPriority;
    int queue;
    int quantum;
    int exitTime;
    int waitingTime;
    int responseTime;
    int turnAroundTime;
    int cpu;
    int remainingBurstTime;
} process;

int calculateTT(int exitTime, int arrivalTime);
int otherColumnTT(int burstTime, int waitingTime);
int calculateWaitingTime(int tt, int bt);

int calculateTT(int exitTime, int arrivalTime) {
    return exitTime - arrivalTime;
}

int otherColumnTT(int burstTime, int waitingTime) {
    return burstTime - waitingTime;
}

int calculateWaitingTime(int tt, int bt) {
    return tt - bt;
}


#endif

