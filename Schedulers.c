#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "Process.h"
#include <sys/stat.h>
#include <string.h>

#define FILE_NAME "listProcess.cpu"
#define ARRAY_LENGTH 29

const char* read_format_file = "%s\t%d\t%d\t%d\n";

void output(void *vargp) {
	printf("|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n");
	printf("|PXX\t|QU\t|QM\t|AT\t|BT\t|ET\t|WT\t|RT\t|TT\t|\n");
	printf("|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n\n");
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

void FCFS(void *vargp) {
	printf(" --> FCFS\n");
	output(0);
	
	int totalExitTime = 0;

	process processes[ARRAY_LENGTH];

	FILE *inputFile = fopen(FILE_NAME, "r");

	int index = -1;

	char line[255];
	char *limiter = "\t";

	while (fgets(line, sizeof(line), inputFile) != NULL) {
		if (index < 0) {
			index++;
			continue;
		} else {
			process p = processes[index];
			sscanf(line, "%s\t%d\t%d\t%d\n", p.pxx, &p.arrivalTime, &p.burstTime, &p.vPriority);
			processes[index] = p;
			index++;
		}
	}

	fclose(inputFile);

	//ordenando la lista por medio de AT
	qsort(processes, ARRAY_LENGTH, sizeof(process), sortByAT);

	int exitTime = 0;
	for (int i = 0; i < index; i++) {
		process *p = &processes[i];
		exitTime += p->burstTime;
		p->exitTime = exitTime;
		p->turnAroundTime = calculateTT(p->exitTime, p->arrivalTime);
		p->waitingTime = calculateWaitingTime(p->turnAroundTime, p->burstTime);
		p->responseTime = i;

		if (p->responseTime == 0) {
			p->responseTime = 0;
		} else {
			p->responseTime = calculateTT(processes[i - 1].exitTime, processes[i].arrivalTime);
		}

		processes[i].queue	= processes[i].arrivalTime;
		printf("|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n");
		printf("|%s\t|%02d\t|%02d\t|%02d\t|%02d\t|%03d\t|%03d\t|%03d\t|%03d\t|\n",
			p->pxx,
			p->queue,
			0,
			p->arrivalTime,
			p->burstTime,
			p->exitTime,
			p->waitingTime,
			p->responseTime,
			p->turnAroundTime
		);
		printf("|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n\n");
	}

	// calculando promedios
	for (int i = 0; i < ARRAY_LENGTH; i++) {

	}
	printf("|%s\t|%02d\t|%02d\t|%02d\t|%02d\t|%03d\t|%03d\t|%03d\t|%03d\t|\n",
			"TH",
			0,
			0
		);

} 

void PS(void *vargp) {
	printf(" --> PS\n");
	output(0);
} 

void RR(void *vargp) {
	printf(" --> RR\n");
	output(0);
} 

void MLFQS(void *vargp) {
	printf(" --> MLFQS\n");
	output(0);
} 

int menu(){
	int tmp;
	printf("############\n1 - FCFS\n2 - PS\n3 - RR\n4 - MLFQS\n0 - EXIT\n\nSeleccione Opción: ");
	scanf("%d", &tmp);
	return tmp;
}

// C Concepts 
// https://gist.github.com/Integralist/6c35d4f26c0c7bf5bdce7b95cfa906b3
int main ( int argc , char * argv []) {
	int op = 9;
	pid_t pid;
	while (op > 0){
		op = menu();
		printf("Procesando opción: %d\n", op);
		if ( op >5 || op<=0 ){
			printf("### END ###\n");
			break;
		}
		printf("### BEGIN ###\n");
		switch(op){
			case 1:
			FCFS(0);
			break;
			case 2:
			PS(0);
			break;
			case 3:
			RR(0);
			break;
			default:
			case 4:
			MLFQS(0);
			break;
		}
	}
	return 0;
}