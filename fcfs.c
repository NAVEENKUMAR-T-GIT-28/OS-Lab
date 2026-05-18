#include <stdio.h>
int main() {
    int n, bt[20], wt[20], tat[20];
    float wtavg=0, tatavg=0;
    printf("Number of processes: "); scanf("%d",&n);
    for(int i=0;i<n;i++){
        printf("Burst time P%d: ",i); scanf("%d",&bt[i]);
    }
    wt[0]=0; tat[0]=bt[0];
    for(int i=1;i<n;i++){
        wt[i]  = wt[i-1]+bt[i-1];
        tat[i] = wt[i]+bt[i];
        wtavg += wt[i]; tatavg += tat[i];
    }
    tatavg += tat[0];
    printf("\nP  BT  WT  TAT\n");
    for(int i=0;i<n;i++)
        printf("P%d %d  %d  %d\n",i,bt[i],wt[i],tat[i]);
    printf("Avg WT=%.2f  Avg TAT=%.2f\n",wtavg/n,tatavg/n);
    return 0;
}