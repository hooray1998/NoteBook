#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define SIZE 10000  //the size of all numbers

void *another(void *arg){
    double *sum = (double*)malloc(sizeof(double));
    *sum = 0;
    short sign = ((SIZE/2)%2==0)?1:-1;
    int i=0;
    while(i<SIZE/2){
        *sum += sign*(double)1/(2*i+1+SIZE);
        sign = - sign;
        i++;
    }

    return (void *)sum;
}

int main(){

    pthread_t pid;
    pthread_create(&pid, NULL, &another, NULL);

    double sum1=0;
    short sign = 1;
    int i=0;
    while(i<SIZE/2){
        sum1 += sign*(double)1/(2*i+1);
        sign = - sign;
        i++;
    }
    double *sum2 = (double *)malloc(sizeof(double));
    pthread_join(pid, (void **)&sum2);

    printf("sum is %f.\n", sum1+*sum2);

    return 0;
}
