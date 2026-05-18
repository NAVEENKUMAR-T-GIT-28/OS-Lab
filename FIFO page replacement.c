#include <stdio.h>
#include <stdlib.h>
int main(){
    int n,no,a[20],frame[20],count=0,j=0,avail,k;
    
    printf("No of pages: ");
    scanf("%d",&n);

    printf("Page reference string: ");
    for(int i=1;i<=n;i++) 
        scanf("%d",&a[i]);
    
    printf("No of frames: ");
    scanf("%d",&no);

    for(int i=0;i<no;i++) frame[i]=-1;
    printf("\nRef\tFrames\n");
    
    for(int i=1;i<=n;i++){
        printf("%d\t",a[i]);
        avail=0;
        for(k=0;k<no;k++) if(frame[k]==a[i]) avail=1;
        if(!avail){
            frame[j]=a[i];
            j=(j+1)%no;
            count++;
            for(k=0;k<no;k++) 
                printf("%d ",frame[k]);
        }
        printf("\n");
    }
    printf("Page faults: %d\n",count);
    return 0;
}