//>>> 多个线程并行求和
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define MAX_NUMBER_SIZE 10000 //the size limit of all numbers
#define MAX_PTHREAD_SIZE 100 //the number of pthread

void *another(void *arg){
    double *result = (double *)malloc(sizeof(double));
    int start = *(int *)arg;
    *result = 0;
    short sign = ((start)%2==0)?1:-1;
    int i=start;
    while(i<(start + MAX_NUMBER_SIZE/MAX_PTHREAD_SIZE)){
        *result += sign*(double)1/(2*i + 1);
        sign = -sign;
        i++;
    }

    return (void *)result;
}

int main(){
    pthread_t pidArr[MAX_PTHREAD_SIZE];
    int start[MAX_PTHREAD_SIZE];

    int curStart = 0;
    int i=0;
    while(i<MAX_PTHREAD_SIZE){
        start[i] = curStart;
        void *arg = (void *)(start + i);
        pthread_create(&pidArr[i], NULL, &another, arg);
        curStart += MAX_NUMBER_SIZE/MAX_PTHREAD_SIZE;
        i++;
    }

    double all_result = 0;

    i=0;
    while(i<MAX_PTHREAD_SIZE){
        double *another_result;
        pthread_join(pidArr[i], (void **)&another_result);
        all_result += *another_result;
        free(another_result);
        i++;
    }

    printf("result is %f. ", all_result);
    printf("\nso PI is closed to %f\n", all_result*4);

    return 0;
}




