#include <stdio.h>
#include <stdlib.h>
int f[50];
int main(){
    int st,len,c;

    for(int i=0;i<50;i++) 
        f[i]=0;
    
    again:
    printf("Starting block & length: ");
    scanf("%d %d",&st,&len);
    
    int j;
    for(j=st;j<st+len;j++){
        if(f[j]==0){
            f[j]=1;
            printf("%d->%d\n",j,f[j]);
        }
        else{
            printf("Block %d already allocated\n",j);
            break;
        }
    }
    if(j==st+len) 
        printf("File allocated to disk\n");
    printf("More files? (1=yes 0=no): ");
    scanf("%d",&c);
    if(c==1) 
        goto again;
    return 0;
}