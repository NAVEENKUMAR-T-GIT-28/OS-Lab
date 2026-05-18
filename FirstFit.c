#include <stdio.h>
int main(){
    int bsize[10],psize[10],bno,pno,flags[10],alloc[10];
    for(int i=0;i<10;i++){flags[i]=0;alloc[i]=-1;}
    printf("No of blocks: "); scanf("%d",&bno);
    for(int i=0;i<bno;i++){printf("Block %d size: ",i+1);scanf("%d",&bsize[i]);}
    printf("No of processes: "); scanf("%d",&pno);
    for(int i=0;i<pno;i++){printf("Process %d size: ",i+1);scanf("%d",&psize[i]);}
    for(int i=0;i<pno;i++)
        for(int j=0;j<bno;j++)
            if(!flags[j]&&bsize[j]>=psize[i]){alloc[j]=i;flags[j]=1;break;}
    printf("\nBlock  Size  Process  PSize\n");
    for(int i=0;i<bno;i++){
        printf("%d      %d",i+1,bsize[i]);
        if(flags[i]) printf("     P%d       %d",alloc[i]+1,psize[alloc[i]]);
        else printf("     Not allocated");
        printf("\n");
    }
    return 0;
}