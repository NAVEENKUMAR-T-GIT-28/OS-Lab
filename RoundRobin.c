#include <stdio.h>
struct proc{int pn,bt,wt,tat;} p[10];
int main(){
    int tq,n,b[10],ttat=0,j=0;
    float awt=0,atat=0;
    printf("No of processes: "); 
    scanf("%d",&n);
    
    for(int i=1;i<=n;i++){
        printf("PID & Burst: ");
        scanf("%d %d",&p[i].pn,&p[i].bt);
        b[i]=p[i].bt; 
        ttat+=p[i].bt;
    }
    printf("Time quantum: "); 
    scanf("%d",&tq);

    while(j<ttat)
    for(int i=1;i<=n;i++){
        if(p[i].bt>0){
            if(p[i].bt>tq){p[i].bt-=tq;j+=tq;}
            else{
                j+=p[i].bt;
                p[i].tat=j;
                p[i].wt=p[i].tat-b[i];
                atat+=p[i].tat;
                awt+=p[i].wt;
                p[i].bt=0;
            }
        }
    }
    printf("\nP  BT  WT  TAT\n");
    for(int i=1;i<=n;i++) 
        printf("%d  %d  %d  %d\n",p[i].pn,b[i],p[i].wt,p[i].tat);
    printf("Avg WT=%.2f  Avg TAT=%.2f\n",awt/n,atat/n);
    return 0;
}