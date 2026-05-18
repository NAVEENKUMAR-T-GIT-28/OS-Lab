#include <stdio.h>
int main() {
    int n,p[20],bt[20],wt[20],tat[20],temp;
    float wtavg=0,tatavg=0;
    printf("Number of processes: "); scanf("%d",&n);
    for(int i=0;i<n;i++){p[i]=i; printf("Burst P%d: ",i); scanf("%d",&bt[i]);}
    for(int i=0;i<n;i++)
        for(int k=i+1;k<n;k++)
            if(bt[i]>bt[k]){
                temp=bt[i];bt[i]=bt[k];bt[k]=temp;
                temp=p[i];p[i]=p[k];p[k]=temp;
            }
    wt[0]=0; tat[0]=bt[0]; tatavg=tat[0];
    for(int i=1;i<n;i++){
        wt[i]=wt[i-1]+bt[i-1];
        tat[i]=tat[i-1]+bt[i];
        wtavg+=wt[i]; tatavg+=tat[i];
    }
    printf("\nP  BT  WT  TAT\n");
    for(int i=0;i<n;i++)
        printf("P%d %d  %d  %d\n",p[i],bt[i],wt[i],tat[i]);
    printf("Avg WT=%.2f  Avg TAT=%.2f\n",wtavg/n,tatavg/n);
    return 0;
}