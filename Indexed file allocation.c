#include <stdio.h>
#include <stdlib.h>
int f[50],inde[50];
int main(){
    int p,n,c;
    for(int i=0;i<50;i++) f[i]=0;
    again:
    printf("Index block: ");scanf("%d",&p);
    if(f[p]){printf("Block already allocated\n");goto again;}
    f[p]=1;
    printf("No of files on index: ");scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&inde[i]);
    for(int i=0;i<n;i++) if(f[inde[i]]){printf("Block %d already allocated\n",inde[i]);goto again;}
    for(int j=0;j<n;j++) f[inde[j]]=1;
    printf("Allocated. File indexed:\n");
    for(int k=0;k<n;k++) printf("%d->%d:%d\n",p,inde[k],f[inde[k]]);
    printf("More? (1=yes 0=no): ");scanf("%d",&c);
    if(c==1) goto again;
    return 0;
}