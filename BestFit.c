#include <stdio.h>
#define MAX 25
int main(){
    int b[MAX],f[MAX],bf[MAX]={0},ff[MAX]={0},frag[MAX];
    int nb,nf,lowest;

    printf("No of blocks: "); 
    scanf("%d",&nb);

    for(int i=1;i<=nb;i++){
        printf("Block %d: ",i);
        scanf("%d",&b[i]);
    }

    printf("No of files: "); 
    scanf("%d",&nf);

    for(int i=1;i<=nf;i++){
        printf("File %d: ",i);
        scanf("%d",&f[i]);
    }

    for(int i=1;i<=nf;i++){
        lowest=10000;
        for(int j=1;j<=nb;j++){
            if(!bf[j]){
                int temp=b[j]-f[i];
                if(temp>=0 && temp<lowest){
                    ff[i]=j;
                    lowest=temp;
                }
            }
        }
        frag[i]=lowest;
        bf[ff[i]]=1;
    }

    printf("\nFile  FSize  Block  BSize  Frag\n");
    for(int i=1;i<=nf && ff[i];i++)
        printf("%d     %d      %d      %d      %d\n",i,f[i],ff[i],b[ff[i]],frag[i]);
    return 0;
}