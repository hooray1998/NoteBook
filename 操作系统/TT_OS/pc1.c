#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define SIZE 4
#define PRODUCE_COUNT 8

char buffer1[SIZE];
char buffer2[SIZE];
int in=0;
int cal=0;
int out=0;

int emptyOfCon(){
    return cal==out;
}

int emptyOfCal(){
    return cal==in;
}

int fullOfCal(){
    return (cal+1)%SIZE==out;
}

int fullOfPro(){
    return (in+1)%SIZE==cal;
}

char get(){
    char n = buffer2[out];
    out = (out+1)%SIZE;
    return n;
}

void put(char n){
    buffer1[in] = n;
    in = (in+1)%SIZE;
}

void calculate(){
    buffer2[cal] = buffer1[cal] + 'A' - 'a';
    cal = (cal+1)%SIZE;
}

pthread_mutex_t mutex;
pthread_cond_t wait_emptyOfPro;
pthread_cond_t wait_fullOfCal;
pthread_cond_t wait_emptyOfCal;
pthread_cond_t wait_fullOfCon;

void *Produce(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        pthread_mutex_lock(&mutex);
        while(fullOfPro())
            pthread_cond_wait(&wait_emptyOfPro, &mutex);

        put(i+'a');
        printf("produce=>%c\n", i+'a');

        pthread_cond_signal(&wait_fullOfCal);
        pthread_mutex_unlock(&mutex);
        i++;
    }
}

void *Calculate(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        pthread_mutex_lock(&mutex);
        while(emptyOfCal())
            pthread_cond_wait(&wait_fullOfCal, &mutex);
        while(fullOfCal())
            pthread_cond_wait(&wait_emptyOfCal, &mutex);

        calculate();
        printf("\tcalculate<=\n");

        pthread_cond_signal(&wait_fullOfCon);
        pthread_cond_signal(&wait_emptyOfPro);
        pthread_mutex_unlock(&mutex);
        i++;
    }
}

void *Consume(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        pthread_mutex_lock(&mutex);
        while(emptyOfCon())
            pthread_cond_wait(&wait_fullOfCon, &mutex);

        printf("\t\tconsume=>%c\n", get());

        pthread_cond_signal(&wait_emptyOfCal);
        pthread_mutex_unlock(&mutex);
        i++;
    }
}

int main(){

    pthread_t consumePid;
    pthread_t calculatePid;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&wait_emptyOfPro, NULL);
    pthread_cond_init(&wait_emptyOfCal, NULL);
    pthread_cond_init(&wait_fullOfCal, NULL);
    pthread_cond_init(&wait_fullOfCon, NULL);

    pthread_create(&consumePid, NULL, &Consume, NULL);
    pthread_create(&calculatePid, NULL, &Calculate, NULL);

    Produce(NULL);

    pthread_join(consumePid, NULL);
    pthread_join(calculatePid, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
