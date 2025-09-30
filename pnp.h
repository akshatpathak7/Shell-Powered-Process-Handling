#ifndef PNP_H
#define PNP_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


/*---------------------------------------
  Input: asks user for arrival, burst, priority
----------------------------------------*/
void input_non_preemptive(int *at, int *bt, int *priority, int n) {
    for (int i = 1; i <= n; i++) {
        printf("Enter Arrival Time, Burst Time, Priority for Process %d: ", i);
        if (scanf("%d %d %d", &at[i], &bt[i], &priority[i]) != 3) {
            printf("Invalid input.\n");
            return;
        }
    }
}

/*---------------------------------------
  Sort by priority (higher first).
  If equal priority, sort by arrival time.
----------------------------------------*/
void ppsort(int *at, int *bt, int *priority, int *index, int n) {
    for (int i = 1; i <= n; i++) {
        int maxIdx = i;
        for (int j = i + 1; j <= n; j++) {
            if (priority[j] > priority[maxIdx] ||
               (priority[j] == priority[maxIdx] && at[j] < at[maxIdx])) {
                maxIdx = j;
            }
        }
        swap(&priority[i], &priority[maxIdx]);
        swap(&bt[i], &bt[maxIdx]);
        swap(&at[i], &at[maxIdx]);
        swap(&index[i], &index[maxIdx]);
    }
}

/*---------------------------------------
  Priority (Non-Preemptive) Scheduling
----------------------------------------*/
void pp(int *at, int *bt, int *priority, int *index, int n) {
    int ct[n + 1], wt[n + 1], tat[n + 1];
    int time = 0;

    ppsort(at, bt, priority, index, n);

    printf("\n\nPriority Scheduling (Non-Preemptive)\n====================================\n");
    printf("PID\tAT\tBT\tPriority\tCT\tWT\tTAT\n");

    for (int i = 1; i <= n; i++) {
        if (time < at[i]) {  // CPU idle until process arrives
            time = at[i];
        }
        ct[i]  = time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i]  = tat[i] - bt[i];
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               index[i], at[i], bt[i], priority[i], ct[i], wt[i], tat[i]);
        time += bt[i];
    }
}

/*---------------------------------------
  Gantt Chart
----------------------------------------*/
void ppgantt(int *at, int *bt, int *priority, int *index, int n) {
    ppsort(at, bt, priority, index, n);

    printf("\n\nGantt Chart\n===========\n|");
    int time = 0;
    for (int i = 1; i <= n; i++) {
        if (time < at[i]) {
            // idle time slot
            printf("Idle");
            for (int j = 0; j < (at[i] - time); j++) printf(" ");
            printf("|");
            time = at[i];
        }
        printf("P%d", index[i]);
        for (int j = 0; j < bt[i]; j++) printf(" ");
        printf("|");
        time += bt[i];
    }

    // Time markers
    printf("\n0");
    time = 0;
    for (int i = 1; i <= n; i++) {
        if (time < at[i]) {
            time = at[i];
            printf("%*d", 5, time); // idle gap
        }
        time += bt[i];
        printf("%*d", bt[i] + 2, time);
    }
    printf("\n");
}

#endif


