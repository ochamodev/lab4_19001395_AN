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
int sortByAT(const void *a, const void *b);
int sortByPriority(const void *a, const void *b);


int calculateTT(int exitTime, int arrivalTime) {
    return exitTime - arrivalTime;
}

int otherColumnTT(int burstTime, int waitingTime) {
    return burstTime - waitingTime;
}

int calculateWaitingTime(int tt, int bt) {
    return tt - bt;
}

int sortByAT(const void *a, const void *b) {
	process *f = (process*) a;
	process *s = (process*) b;

	if (f->arrivalTime > s->arrivalTime) {
		return 1;
	} else if (f->arrivalTime < s->arrivalTime) {
		return -1;
	}
	return 0;
}

int sortByPriority(const void *a, const void *b) {
	process *f = (process*) a;
	process *s = (process*) b;

	if (f->vPriority > s->vPriority) {
		return 1;
	} else if (f->vPriority < s->vPriority) {
		return -1;
	}
	return 0;
}

#endif

