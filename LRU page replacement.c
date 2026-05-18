#include <stdio.h>
int main(){
    int n,f,q[20],p[20],pgf=0,st=0,t,cnt,j;
    printf("No of ref strings: ");
    scanf("%d",&n);
    printf("No of frames: ");
    scanf("%d",&f);
    printf("Strings: ");
    for(int i=0;i<n;i++)
    scanf("%d",&q[i]);

    for(int i=0;i<f;i++)
    p[i]=999;
    
    for(int i=0;i<n;i++){
        st=0;
        for(j=0;j<f;j++) 
            if(p[j]==q[i]){
                st=1;
                t=p[j];
                cnt=j;
            }
        if(!st){
            printf("Fault  ");
            pgf++;
            for(j=f;j>0;j--) p[j]=p[j-1];
            p[0]=q[i];
        } else {
            for(j=cnt;j>0;j--) p[j]=p[j-1];
            p[0]=t;
        }
        for(j=0;j<f;j++) printf("%d ",p[j]);
        printf("\n");
    }
    printf("Total page faults: %d\n",pgf);
    return 0;
}