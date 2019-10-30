//>>> 两个线程并行求和
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define MAX_NUMBER_SIZE 10000 //the size limit of all numbers

void *another(void *arg){
    double *result = (double *)malloc(sizeof(double));
    *result = 0;
    short sign = ((MAX_NUMBER_SIZE/2)%2==0)?1:-1;
    int i=0;
    while(i<MAX_NUMBER_SIZE/2){
        *result += sign*(double)1/(2*i + 1 + MAX_NUMBER_SIZE);
        sign = -sign;
        i++;
    }

    return (void *)result;
}

int main(){
    pthread_t pid;
    pthread_create(&pid, NULL, &another, NULL);

    double main_result = 0;
    short sign = 1;
    int i=0;
    while(i<MAX_NUMBER_SIZE/2){
        main_result += sign*(double)1/(2*i+1);
        sign =- sign;
        i++;
    }
    double *another_result = (double*) malloc(sizeof(double));
    pthread_join(pid, (void **)&another_result);

    printf("result is %f. (main_result is %f, anther_pthread_result is %f)", main_result+*another_result, main_result, *another_result);
    printf("\nso PI is closed to %f\n", (main_result + *another_result)*4);

    return 0;
}




