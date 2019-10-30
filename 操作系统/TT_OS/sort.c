#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define SIZE 20  //the size of all numbers

void *another(void *arg){
    int *arr = (int *)arg;
    int len = SIZE - SIZE/2;

    int min, temp;
    int i=0,j;
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

    return NULL;
}

int main(){

    int arr[SIZE];
    int i=0,j;
    while(i<SIZE){
        arr[i++] = rand()%100;
    }

    void *arg = (void *)(arr + SIZE/2);

    pthread_t pid;
    pthread_create(&pid, NULL, &another, arg);

    int min, temp;
    i=0;
    while(i<SIZE/2){
        min = i;
        j = i+1;
        while(j<SIZE/2){
            if(arr[j]<arr[min])
                min = j;
            j++;
        }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
        i++;
    }

    pthread_join(pid, NULL);
    
    i=0,j=SIZE/2;
    while(i<SIZE/2&&j<SIZE){
        if(arr[i]<arr[j]){
            printf("%d ", arr[i]);
            i++;
        }
        else{
            printf("%d ", arr[j]);
            j++;
        }
    }

    while(i<SIZE/2){
        printf("%d ", arr[i++]);
    }
    while(j<SIZE){
        printf("%d ", arr[j++]);
    }
    printf("\n");


    return 0;
}
