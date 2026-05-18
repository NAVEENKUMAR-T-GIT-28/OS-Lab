#include <stdio.h>
#include <stdlib.h>
int f[50];
int main(){
    int p,a,st,len,c;
    for(int i=0;i<50;i++) f[i]=0;
    printf("Already allocated blocks count: ");scanf("%d",&p);
    printf("Enter those block numbers: ");
    for(int i=0;i<p;i++){scanf("%d",&a);f[a]=1;}
    again:
    printf("Starting block & length: ");scanf("%d %d",&st,&len);
    int k=len;
    for(int j=st;j<k+st;j++){
        if(f[j]==0){f[j]=1;printf("%d->%d\n",j,f[j]);}
        else{printf("%d->already allocated\n",j);k++;}
    }
    printf("More files? (1=yes 0=no): ");scanf("%d",&c);
    if(c==1) goto again;
    return 0;
}