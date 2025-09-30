#include <stdio.h>
#ifndef FCFS_H
#define FCFS_H

/* sort by arrival time (1-based) without relying on external swap() */
void sortfcfs(int *a, int *b, int *index, int n) {
    int i, j, tmp;
    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            if (a[i] > a[j]) {
                /* swap arrival times */
                tmp = a[i]; a[i] = a[j]; a[j] = tmp;
                /* swap burst times */
                tmp = b[i]; b[i] = b[j]; b[j] = tmp;
                /* swap indices */
                tmp = index[i]; index[i] = index[j]; index[j] = tmp;
            }
        }
    }
}

/* FCFS using 1-based arrays a[1..n], b[1..n], index[1..n] */
void fcfs(int *a, int *b, int *index, int n) {
    int c[n+1], w[n+1], r[n+1], tat[n+1];
    int i;

    sortfcfs(a, b, index, n);

    printf("\n\nFCFS - First Come First Serve\n=============================\n");
    printf("PID\tAT\tBT\tCT\tWT\tRT\tTAT\n");

    for (i = 1; i <= n; i++) {
        if (i == 1) {
            if (a[i] > 0)
                c[i] = a[i] + b[i];
            else
                c[i] = b[i];
        } else {
            if (c[i-1] < a[i])
                c[i] = a[i] + b[i];   /* CPU idle until arrival */
            else
                c[i] = c[i-1] + b[i];
        }

        w[i]   = c[i] - b[i] - a[i];
        r[i]   = w[i];
        tat[i] = c[i] - a[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               index[i], a[i], b[i], c[i], w[i], r[i], tat[i]);
    }
}

/* Simple Gantt chart matching 1-based arrays */
void fcfsgantt(int *a, int *b, int *index, int n) {
    /* Make a local copy and sort so we don't disturb original arrays */
    int at[n+1], bt[n+1], idx[n+1], tmp;
    for (int i = 1; i <= n; i++) {
        at[i] = a[i];
        bt[i] = b[i];
        idx[i] = index[i];
    }

    /* reuse the same sort routine */
    sortfcfs(at, bt, idx, n);

    printf("\n\nGantt Chart\n===========\n|");
    int time = 0;
    for (int i = 1; i <= n; i++) {
        if (time < at[i]) {
            int idle_len = at[i] - time;
            printf("Idle");
            for (int j = 0; j < idle_len; j++) printf(" ");
            printf("|");
            time = at[i];
        }
        printf("P%d", idx[i]);
        for (int j = 0; j < bt[i]; j++) printf(" ");
        printf("|");
        time += bt[i];
    }

    /* time markers */
    printf("\n0");
    time = 0;
    for (int i = 1; i <= n; i++) {
        if (time < at[i]) time = at[i];
        time += bt[i];
        printf(" %d", time);
    }
    printf("\n");
}

#endif
