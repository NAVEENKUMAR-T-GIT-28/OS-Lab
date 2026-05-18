#include <stdio.h>
#include <stdlib.h>

int mutex=1, full=0, empty=3, x=0;

void producer(){
    --mutex;
    ++full;
    --empty;
    x++;
    printf("Producer produces item %d\n",x);
    ++mutex;
}

void consumer(){
    --mutex;
    --full;
    ++empty;
    printf("Consumer consumes item %d\n",x);
    x--; 
    ++mutex;
}
int main(){
    int n;
    printf("1=Producer  2=Consumer  3=Exit\n");
    for(;;){
        printf("Choice: "); 
        scanf("%d",&n);
        if(n==1){
            if(mutex==1 && empty!=0)
                producer();
            else 
                printf("Buffer full!\n");
        }
        else if(n==2){
            if(mutex==1 && full!=0)
                consumer();
            else 
                printf("Buffer empty!\n");
        }
        else 
            break;
    }
    return 0;
}