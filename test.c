#include <stdio.h>
#include "fcfs.h"
#include "pp.h"    // has input_pp()
#include "pnp.h"   // has input_npp()


int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n+1], bt[n+1], priority[n+1], index[n+1];
    for (int i = 1; i <= n; i++) index[i] = i;

    int choice;
    printf("\n1) Priority Non-Preemptive\n2) Priority Preemptive\n3) FCFS\nChoose: ");
    scanf("%d", &choice);

    if (choice == 1) {
        input_preemptive(at, bt, priority, n);
        pp(at, bt, priority, index, n);
        ppgantt(at, bt, priority, index, n);
    } else if (choice == 2) {
        input_non_preemptive(at, bt, priority, n);
        pnp(at, bt, priority, index, n);
        pnpgantt(at, bt, priority, index, n);
    } else if (choice == 3) {
        // FCFS input (1-based arrays)
        printf("Enter Arrival Time and Burst Time for each process:\n");
        for (int i = 1; i <= n; i++) {
            printf("P%d (AT BT): ", i);
            scanf("%d %d", &at[i], &bt[i]);
        }

        // Call FCFS functions
        fcfs(at, bt, index, n);
        fcfsgantt(at, bt, index, n);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
