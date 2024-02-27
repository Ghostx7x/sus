#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
//#include<malloc.h>

void FCFS();
void SJF();
void roundrobin();
void priority();
int n, i, j, pos, temp, *bt, *wt, *tat, *p, *pt, tempn, count, terminaltime=0, initialtime, qt, flag=0,*tempbt;
float avgwt = 0, avgtat = 0;
int main(void)
{
    int choice;
    for(;;)
    {
        printf("\n Enter the number of processes : ");
        scanf("%d", &n);
        tempn=n;
        free(p);
        free(pt);
        free(bt);
        free(wt);
        free(tat);
        free(tempbt);
        tempbt = (int*)malloc(n*sizeof(int));
        p = (int*)malloc(n*sizeof(int));
        pt = (int*)malloc(n*sizeof(int));
        bt = (int*)malloc(n*sizeof(int));
        wt = (int*)malloc(n*sizeof(int));
        tat = (int*)malloc(n*sizeof(int));
        printf("\n Enter the burst time for each process \n");
        for(i=0; i<n; i++)
        {
            printf(" Burst time for P%d: ", i);
            scanf("%d", &bt[i]);
            p[i] = i;
            tempbt[i] = bt[i];
            terminaltime += bt[i];
        }
        printf("\n enter the choice");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:FCFS();
            break;
            case 2: SJF();
            break;
            case 3:roundrobin();
            break;
            case 4:priority();
            break;
            default: exit(0);
        }
    }
}

void FCFS()
{
    avgwt = 0, avgtat = 0;
    wt[0] = 0;
    tat[0] = bt[0];
    for(i=1; i<n; i++)
    {
        wt[i] = wt[i-1] + bt[i-1]; //waiting time[p] = waiting time[p-1] + Burst Time[p-1]
        tat[i] = wt[i] + bt[i]; //Turnaround Time = Waiting Time + Burst Time
    }
    for(i=0; i<n; i++)
    {
        avgwt += wt[i];
        avgtat += tat[i];
    }
    avgwt = avgwt/n;
    avgtat = avgtat/n;
    printf("\n PROCESS \t BURST TIME \t WAITING TIME \t TURNAROUND TIME \n");
    printf("--------------------------------------------------------------\n");
    for(i=0; i<n; i++)
    {
        printf(" P%d \t\t %d \t\t %d \t\t %d \n", i, bt[i], wt[i], tat[i]);
    }
    printf("\n Average Waiting Time = %f \n Average Turnaround Time = %f \n", avgwt, avgtat);
    printf("\n GANTT CHART \n");
    printf("---------------\n");
    for(i=0; i<n; i++)
    {
        printf(" %d\t|| P%d ||\t%d\n", wt[i], i, tat[i]);
    }
}

void SJF()
{
    avgwt = 0, avgtat = 0;
    for(i=0; i<n; i++)
    {
        pos = i;
        for(j=i+1; j<n; j++)
        {
            if(bt[j] < bt[pos])
            {
                pos = j;
            }
        }
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }
    wt[0] = 0;
    tat[0] = bt[0];
    for(i=1; i<n; i++)
    {
        wt[i] = wt[i-1] + bt[i-1]; //waiting time[p] = waiting time[p-1] + Burst Time[p-1]
        tat[i] = wt[i] + bt[i]; //Turnaround Time = Waiting Time + Burst Time
    }
    for(i=0; i<n; i++)
    {
        avgwt += wt[i];
        avgtat += tat[i];
    }
    avgwt = avgwt/n;
    avgtat = avgtat/n;
    printf("\n PROCESS \t BURST TIME \t WAITING TIME \t TURNAROUND TIME \n");
    printf("--------------------------------------------------------------\n");
    for(i=0; i<n; i++)
    {
        printf(" P%d \t\t %d \t\t %d \t\t %d \n", p[i], bt[i], wt[i], tat[i]);
    }
    printf("\n Average Waiting Time = %f \n Average Turnaround Time = %f \n", avgwt, avgtat);
    printf("\n GAANT CHART \n");
    printf("---------------\n");
    for(i=0; i<n; i++)
    {
        printf(" %d\t|| P%d ||\t%d\n", wt[i], p[i], tat[i]);
    }
}

void roundrobin()
{
    printf("\n Enter the Quantum Time : ");
    scanf("%d", &qt);
    avgwt = 0, avgtat = 0;
    wt[0] = 0;
    printf("\n GANTT CHART \n");
    printf("\n-------------\n");
    for(terminaltime=0, count=0; tempn!=0;) 
    {
        initialtime = terminaltime;
        if(tempbt[count] <= qt && tempbt[count] > 0) 
        {
            terminaltime += tempbt[count];
            tempbt[count] = 0;
            wt[count] = terminaltime - bt[count];
            tat[count] = wt[count] + bt[count];
            flag = 1;
        }
        else if(tempbt[count] > qt) 
        {
            tempbt[count] -= qt;
            terminaltime += qt;
        }
        if(tempbt[count] == 0 && flag == 1) 
        {
            tempn--;
            flag=0;
        }
        if(initialtime != terminaltime) 
        {
            printf(" %d\t|| P%d ||\t%d\n", initialtime, count, terminaltime);
        }
        if(count == n-1)
            count = 0;
        else
            ++count;
    }
    printf("\n PROCESS \t BURST TIME \t WAITING TIME \t TURNAROUND TIME \n");
    printf("--------------------------------------------------------------\n");
    for(i=0; i<n; i++)
    {
        printf(" P%d \t\t %d \t\t %d \t\t %d \n", i, bt[i], wt[i], tat[i]);
    }
    for(i=0; i<n; i++) {
        avgwt += wt[i];
        avgtat += tat[i];
    }
    avgwt = avgwt/n;
    avgtat = avgtat/n;
    printf("\n Average Waiting Time = %f \n Average Turnaround Time = %f \n", avgwt, avgtat);
}

void priority()
{
    avgwt = 0, avgtat = 0;
    for(i=0; i<n; i++)
    {
        printf(" Priority of P %d : ", i);
        scanf("%d", &pt[i]);
        p[i] = i;
    }
    for(i=0; i<n; i++)
    {
        pos = i;
        for(j=i+1; j<n; j++)
        {
            if(pt[j] < pt[pos])
            {
                pos = j;
            }
        }
        temp = pt[i];
        pt[i] = pt[pos];
        pt[pos] = temp;
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }
    wt[0] = 0;
    tat[0] = bt[0];
    for(i=1; i<n; i++)
    {
        wt[i] = wt[i-1] + bt[i-1]; //waiting time[p] = waiting time[p-1] + Burst Time[p-1]
        tat[i] = wt[i] + bt[i]; //Turnaround Time = Waiting Time + Burst Time
    }
    for(i=0; i<n; i++)
    {
        avgwt += wt[i];
        avgtat += tat[i];
    }
    avgwt = avgwt/n;
    avgtat = avgtat/n;
    printf("\n PROCESS \t PRIORITY \t BURST TIME \t WAITING TIME \t TURNAROUND TIME \n");
    printf("--------------------------------------------------------------\n");
    for(i=0; i<n; i++)
    {
        printf(" P%d \t\t %d \t\t %d \t\t %d \t\t %d \n", p[i], pt[i], bt[i], wt[i], tat[i]);
    }
    printf("\n Average Waiting Time = %f \n Average Turnaround Time = %f \n", avgwt, avgtat);
    printf("\n GANTT CHART \n");
    printf("---------------\n");
    for(i=0; i<n; i++)
    {
        printf(" %d\t|| P%d ||\t%d\n", wt[i], p[i], tat[i]);
    }
}