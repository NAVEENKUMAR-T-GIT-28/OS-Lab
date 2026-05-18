#include <stdio.h>
int main(){
    int pn,rn,alloc[10][10],max[10][10],need[10][10],avail[10];
    int finish[10]={0},safe[10],count=0;
    printf("Processes: ");scanf("%d",&pn);
    printf("Resources: ");scanf("%d",&rn);
    printf("Allocation matrix:\n");
    for(int i=0;i<pn;i++) for(int j=0;j<rn;j++) scanf("%d",&alloc[i][j]);
    printf("Max matrix:\n");
    for(int i=0;i<pn;i++) for(int j=0;j<rn;j++){
        scanf("%d",&max[i][j]);
        need[i][j]=max[i][j]-alloc[i][j];
    }
    printf("Available: ");
    for(int i=0;i<rn;i++) scanf("%d",&avail[i]);
    int s=0;
    while(count<pn){
        int found=0;
        for(int i=0;i<pn;i++){
            if(!finish[i]){
                int ok=1;
                for(int j=0;j<rn;j++) if(need[i][j]>avail[j]){ok=0;break;}
                if(ok){
                    for(int j=0;j<rn;j++) avail[j]+=alloc[i][j];
                    finish[i]=1; safe[s++]=i; count++; found=1;
                }
            }
        }
        if(!found){printf("UNSAFE STATE - Deadlock possible!\n");return 0;}
    }
    printf("SAFE STATE. Safe sequence: ");
    for(int i=0;i<pn;i++) printf("P%d ",safe[i]);
    printf("\n");
    return 0;
}