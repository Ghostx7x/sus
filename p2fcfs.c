#include <stdio.h>
#include <stdlib.h>

void FCFS();

int main() {
    FCFS();
    return 0;
}

void FCFS() {
    int n, *bt, *wt, *tat;
    float avgwt = 0, avgtat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    bt = (int*)malloc(n * sizeof(int));
    wt = (int*)malloc(n * sizeof(int));
    tat = (int*)malloc(n * sizeof(int));

    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Burst time for P%d: ", i);
        scanf("%d", &bt[i]);
    }

    // Calculate waiting time and turnaround time
    wt[0] = 0;
    tat[0] = bt[0];
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = wt[i] + bt[i];
    }

    // Calculate average waiting time and average turnaround time
    for (int i = 0; i < n; i++) {
        avgwt += wt[i];
        avgtat += tat[i];
    }
    avgwt /= n;
    avgtat /= n;

    // Print the table
    printf("\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i, bt[i], wt[i], tat[i]);
    }

    // Print averages
    printf("\nAverage Waiting Time = %.2f\n", avgwt);
    printf("Average Turnaround Time = %.2f\n", avgtat);

    // Free allocated memory
    free(bt);
    free(wt);
    free(tat);
}