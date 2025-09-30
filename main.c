#include <stdio.h>
#include <string.h>
#include "fcfs.h"
#include "pp.h"    // non-preemptive priority
#include "pnp.h"   // preemptive priority
#include "sjf.h"
#include "srt.h"
// #include "rr.h"   // uncomment if you add Round Robin later

int main() {
    char cmd[50], alg[50];
    int n, quantum = 2; // default RR quantum
    int arrival[20], burst[20], priority[20], index[20];

    while (1) {
        printf("\nSCHEDULER> ");
        scanf("%s", cmd);

        if (!strcmp(cmd, "quit")) break;

        else if (!strcmp(cmd, "scheduling")) {
            printf("Enter number of processes: ");
            scanf("%d", &n);
            for (int i = 1; i <= n; i++) index[i] = i;

            printf("Enter algorithm (fcfs, sjf, srt, pp, pnp, all): ");
            scanf("%s", alg);

            if (!strcmp(alg, "fcfs") || !strcmp(alg, "all")) {
                printf("Enter AT and BT for each process:\n");
                for (int i = 1; i <= n; i++) {
                    printf("P%d (AT BT): ", i);
                    scanf("%d %d", &arrival[i], &burst[i]);
                }
            }

            if (!strcmp(alg, "sjf") || !strcmp(alg, "all")) {
                printf("Enter AT and BT for each process (for SJF):\n");
                for (int i = 1; i <= n; i++) {
                    printf("P%d (AT BT): ", i);
                    scanf("%d %d", &arrival[i], &burst[i]);
                }
            }

            if (!strcmp(alg, "srt") || !strcmp(alg, "all")) {
                printf("Enter AT and BT for each process (for SRT):\n");
                for (int i = 1; i <= n; i++) {
                    printf("P%d (AT BT): ", i);
                    scanf("%d %d", &arrival[i], &burst[i]);
                }
            }

            if (!strcmp(alg, "pp") || !strcmp(alg, "all")) {
                // Non-preemptive Priority
                input_pp(arrival, burst, priority, n);
            }

            if (!strcmp(alg, "pnp") || !strcmp(alg, "all")) {
                // Preemptive Priority
                input_npp(arrival, burst, priority, n);
            }

            // Round Robin would go here if rr.h is added
        }

        else if (!strcmp(cmd, "gantt")) {
            scanf("%s", alg);

            if (!strcmp(alg, "fcfs") || !strcmp(alg, "all"))
                fcfsgantt(arrival, burst, index, n);

            if (!strcmp(alg, "sjf") || !strcmp(alg, "all"))
                sjfgantt(arrival, burst, index, n);

            if (!strcmp(alg, "srt") || !strcmp(alg, "all"))
                srtgantt(arrival, burst, index, n);

            if (!strcmp(alg, "pp") || !strcmp(alg, "all"))
                ppgantt(arrival, burst, priority, index, n);

            if (!strcmp(alg, "pnp") || !strcmp(alg, "all"))
                pnpgantt(arrival, burst, priority, index, n);
        }

        else if (!strcmp(cmd, "table")) {
            scanf("%s", alg);

            if (!strcmp(alg, "fcfs") || !strcmp(alg, "all"))
                fcfs(arrival, burst, index, n);

            if (!strcmp(alg, "sjf") || !strcmp(alg, "all"))
                sjf(arrival, burst, index, n);

            if (!strcmp(alg, "srt") || !strcmp(alg, "all"))
                srt(arrival, burst, index, n);

            if (!strcmp(alg, "pp") || !strcmp(alg, "all"))
                pp(arrival, burst, priority, index, n);

            if (!strcmp(alg, "pnp") || !strcmp(alg, "all"))
                pnp(arrival, burst, priority, index, n);
        }

        else if (!strcmp(cmd, "quantum")) {
            scanf("%d", &quantum);
            printf("Round Robin quantum set to %d\n", quantum);
        }

        else {
            printf("Unknown command: %s\n", cmd);
        }
    }

    return 0;
}
