#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define SIZE 10000  //the size of all numbers
#define PTHREAD_SIZE 100  //the size of all pthreads

void *another(void *arg){
    double *sum = (double*)malloc(sizeof(double));
    int start = *(int *)arg;
    *sum = 0;
    short sign = ((start/2)%2==0)?1:-1;
    int i=start;
    while(i<(start + SIZE/PTHREAD_SIZE)){
        *sum += sign*(double)1/(2*i+1);
        sign = - sign;
        i++;
    }

    return (void *)sum;
}

int main(){

    pthread_t pidArr[PTHREAD_SIZE];
    int start[PTHREAD_SIZE];

    int cur_start = 0;
    int i=0;
    while(i<PTHREAD_SIZE){

        start[i] = cur_start;
        void *arg = (void *)(start + i);
        pthread_create(&pidArr[i], NULL, &another, arg);
        cur_start += SIZE/PTHREAD_SIZE;
        i++;
    }

    double allSum = 0;
    i=0;

    while(i<PTHREAD_SIZE){
        double *sum;
        pthread_join(pidArr[i], (void **)&sum);
        allSum += *sum;
        free(sum);
        i++;
    }

    printf("sum is %f.\n", allSum);

    return 0;
}
