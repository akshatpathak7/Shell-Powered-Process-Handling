#include <stdio.h>
#include "swap.h"
#ifndef PP_H
#define PP_H


/*---------------------------------------
  Input: AT, BT, Priority
----------------------------------------*/
void input_preemptive(int *at, int *bt, int *priority, int n) {
    for (int i = 1; i <= n; i++) {
        printf("Enter AT, BT, Priority for Process %d: ", i);
        if (scanf("%d %d %d", &at[i], &bt[i], &priority[i]) != 3) {
            printf("Invalid input.\n");
            return;
        }
    }
}

/*---------------------------------------
  Priority Preemptive Scheduling
----------------------------------------*/
void pnp(int *at, int *bt, int *priority, int *index, int n) {
    int rt[n + 1], ct[n + 1], tat[n + 1], wt[n + 1];
    int completed = 0, time = 0;

    for (int i = 1; i <= n; i++) {
        rt[i] = bt[i]; // remaining time
    }

    printf("\nPriority Scheduling (Preemptive)\n=================================\n");

    // scheduling loop
    while (completed < n) {
        int highest = -1;

        // find ready process with highest priority
        for (int i = 1; i <= n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                if (highest == -1 || priority[i] > priority[highest]) {
                    highest = i;
                }
            }
        }

        if (highest == -1) {
            time++; // idle CPU
            continue;
        }

        rt[highest]--; // run chosen process for 1 unit
        time++;

        if (rt[highest] == 0) {
            completed++;
            ct[highest] = time;
            tat[highest] = ct[highest] - at[highest];
            wt[highest]  = tat[highest] - bt[highest];
        }
    }

    // Print results
    printf("PID\tAT\tBT\tPri\tCT\tWT\tTAT\n");
    for (int i = 1; i <= n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               index[i], at[i], bt[i], priority[i],
               ct[i], wt[i], tat[i]);
    }
}

/*---------------------------------------
  Gantt Chart for Preemptive Priority
----------------------------------------*/
void pnpgantt(int *at, int *bt, int *priority, int *index, int n) {
    int rt[n + 1];
    for (int i = 1; i <= n; i++) rt[i] = bt[i];

    int time = 0, completed = 0;

    printf("\n\nGantt Chart\n===========\n|");

    while (completed < n) {
        int highest = -1;
        for (int i = 1; i <= n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                if (highest == -1 || priority[i] > priority[highest]) {
                    highest = i;
                }
            }
        }

        if (highest == -1) {
            printf("Idle|");
            time++;
            continue;
        }

        printf("P%d|", index[highest]);
        rt[highest]--;
        time++;

        if (rt[highest] == 0) {
            completed++;
        }
    }

    // Time markers (simple linear)
    printf("\n0");
    for (int t = 1; t <= time; t++) {
        printf(" %d", t);
    }
    printf("\n");
}

#endif
