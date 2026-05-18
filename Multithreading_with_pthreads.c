#include <stdio.h>
#include <pthread.h>
void* thread_func(void* arg){
    int id=*(int*)arg;
    printf("Thread %d is running\n",id);
    return NULL;
}
int main(){
    pthread_t t1,t2;
    int id1=1,id2=2;
    pthread_create(&t1,NULL,thread_func,&id1);
    pthread_create(&t2,NULL,thread_func,&id2);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    printf("Both threads finished.\n");
    return 0;
}
/* Compile: gcc thread.c -lpthread -o thread */