#include <stdio.h>
int main(){
    int m,n,cl[10][10],al[10][10],av[10],ne[10][10];

    printf("Processes Rows, Resource Cols: ");
    scanf("%d %d",&m,&n);

    printf("Claim matrix:\n");
    for(int i=0;i<m;i++) 
        for(int j=0;j<n;j++) 
            scanf("%d",&cl[i][j]);

    printf("Allocated matrix:\n");
    for(int i=0;i<m;i++) 
        for(int j=0;j<n;j++) 
            scanf("%d",&al[i][j]);

    printf("Need matrix:\n");
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            ne[i][j]=cl[i][j]-al[i][j];
            printf("%d ",ne[i][j]);}
        printf("\n");
    }

    printf("Available: ");
    for(int i=0;i<n;i++) 
        scanf("%d",&av[i]);

    int flag=1;

    for(int i=0;i<m && flag;i++){

        for(int j=0;j<n;j++){
            
            if(av[j]<ne[i][j]){
                flag=0;
                break;
            }
        }   
    }

    printf(flag?"Safe State\n":"Unsafe State\n");
    
    return 0;
}