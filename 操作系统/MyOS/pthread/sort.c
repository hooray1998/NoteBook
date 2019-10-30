//>>> 两个线程实现排序，在主线程中完成合并
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define MAX_NUMBER_SIZE 20 //the size limit of all numbers

void *another(void *arg){
    int *arr = (int *)arg;
    int len;
    len = MAX_NUMBER_SIZE - MAX_NUMBER_SIZE/2;

    int min, temp;
    int i=0, j;
    while(i<len){
        min = i;
        j = i+1;
        while(j<len){
            if(arr[j]<arr[min])
                min = j;
            j++;
        }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;

        i++;
    }
}

int main(){
    srand(time(NULL));
    int arr[MAX_NUMBER_SIZE];
    int i=0;
    while(i<MAX_NUMBER_SIZE)
        arr[i++] = rand()%100;

    void *arg = (void *)malloc(sizeof(int*));
    arg = (void*)(arr + MAX_NUMBER_SIZE/2);
    pthread_t pid;
    pthread_create(&pid, NULL, &another, arg);


    int min, temp;
    int j;
    i = 0;
    while(i<MAX_NUMBER_SIZE/2){
        min = i;
        j = i+1;
        while(j<MAX_NUMBER_SIZE/2){
            if(arr[j]<arr[min])
                min = j;
            j++;
        }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;

        i++;
    }

    pthread_join(pid,NULL);

    i=0;
    j=MAX_NUMBER_SIZE/2;
    while(i<MAX_NUMBER_SIZE/2&&j<MAX_NUMBER_SIZE){
        if(arr[i]<arr[j]){
            printf("%d ", arr[i]);
            i++;
        }
        else{
            printf("%d ", arr[j]);
            j++;
        }
    }

    while(i<MAX_NUMBER_SIZE/2)
        printf("%d ", arr[i++]);

    while(j<MAX_NUMBER_SIZE)
        printf("%d ", arr[j++]);

    putchar(10);
    return 0;
}




