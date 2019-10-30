//>>> 条件变量实现 生产者，计算者，消费者
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

int next(int num){
    return (num+1)%SIZE;
}

int noValue2Cosume(){
    return cal==out;
}

int noValue2Calculate(){
    return cal==in;
}

int noSite2Calculate(){
    return next(cal)==out;
}

int noSite2Produce(){
    return next(in)==cal;
}

char get(){
    char n = buffer2[out];
    out = next(out);
    return n;
}
void put(char n){
    buffer1[in] = n;
    in = next(in);
}
void calculate(){
    buffer2[cal] = buffer1[cal] + 'A' - 'a';
    cal = next(cal);
}

pthread_mutex_t mutex;
pthread_cond_t wait_site_to_produce;
pthread_cond_t wait_value_to_calculate;
pthread_cond_t wait_site_to_calculate;
pthread_cond_t wait_value_to_consume;

void *Produce(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        pthread_mutex_lock(&mutex);
        while(noSite2Produce())
            pthread_cond_wait(&wait_site_to_produce, &mutex);

        put(i+'a');
        printf("produce:%c\n", i+'a');

        pthread_cond_signal(&wait_value_to_calculate);
        pthread_mutex_unlock(&mutex);

        i++;
    }
}

void *Calculate(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        pthread_mutex_lock(&mutex);
        while(noValue2Calculate())
            pthread_cond_wait(&wait_value_to_calculate, &mutex);
        while(noSite2Calculate())
            pthread_cond_wait(&wait_site_to_calculate, &mutex);

        calculate();
        printf("\tcalculate\n");

        pthread_cond_signal(&wait_value_to_consume);
        pthread_cond_signal(&wait_site_to_produce);
        pthread_mutex_unlock(&mutex);

        i++;
    }
}

void *Consume(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        pthread_mutex_lock(&mutex);
        while(noValue2Cosume())
            pthread_cond_wait(&wait_value_to_consume, &mutex);

        printf("\t\tconsume:%c\n", get());

        pthread_cond_signal(&wait_site_to_calculate);
        pthread_mutex_unlock(&mutex);

        i++;
    }
}


int main(){
    pthread_t consume_pid;
    pthread_t calculate_pid;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&wait_value_to_consume, NULL);
    pthread_cond_init(&wait_value_to_calculate, NULL);
    pthread_cond_init(&wait_site_to_calculate, NULL);
    pthread_cond_init(&wait_site_to_produce, NULL);

    pthread_create(&consume_pid, NULL, &Consume, NULL);
    pthread_create(&calculate_pid, NULL, &Calculate, NULL);

    Produce(NULL);

    pthread_join(consume_pid, NULL);
    pthread_join(calculate_pid, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
