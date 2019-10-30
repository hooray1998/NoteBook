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

typedef struct{
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}sema_t;

void sema_init(sema_t *sema, int value){
    sema->value = value;
    pthread_mutex_init(&sema->mutex, NULL);
    pthread_cond_init(&sema->cond, NULL);
}

void sema_wait(sema_t *sema){
    pthread_mutex_lock(&sema->mutex);
    while(sema->value <= 0)
        pthread_cond_wait(&sema->cond, &sema->mutex);

    sema->value--;
    pthread_mutex_unlock(&sema->mutex);
}

void sema_signal(sema_t *sema){
    pthread_mutex_lock(&sema->mutex);
    ++sema->value;
    pthread_cond_signal(&sema->cond);
    pthread_mutex_unlock(&sema->mutex);
}

sema_t mutex_sema;
sema_t emptyOfPro_sema;
sema_t fullOfCal_sema;
sema_t emptyOfCal_sema;
sema_t fullOfCon_sema;

void *Produce(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        sema_wait(&emptyOfPro_sema);
        sema_wait(&mutex_sema);

        put(i+'a');
        printf("produce=>%c\n", i+'a');

        sema_signal(&mutex_sema);
        sema_signal(&fullOfCal_sema);
        i++;
    }
}

void *Calculate(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        sema_wait(&fullOfCal_sema);
        sema_wait(&emptyOfCal_sema);
        sema_wait(&mutex_sema);

        calculate();
        printf("\tcalculate<=\n");

        sema_signal(&mutex_sema);
        sema_signal(&emptyOfPro_sema);
        sema_signal(&fullOfCon_sema);
        i++;
    }
}

void *Consume(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        sema_wait(&fullOfCon_sema);
        sema_wait(&mutex_sema);

        printf("\t\tconsume=>%c\n", get());

        sema_signal(&mutex_sema);
        sema_signal(&emptyOfCal_sema);
        i++;
    }
}

int main(){

    pthread_t consumePid;
    pthread_t calculatePid;

    sema_init(&mutex_sema, 1);
    sema_init(&emptyOfPro_sema,SIZE-1);
    sema_init(&fullOfCal_sema,0);
    sema_init(&emptyOfCal_sema,SIZE-1);
    sema_init(&fullOfCon_sema,0);

    pthread_create(&consumePid, NULL, &Consume, NULL);
    pthread_create(&calculatePid, NULL, &Calculate, NULL);

    Produce(NULL);

    pthread_join(consumePid, NULL);
    pthread_join(calculatePid, NULL);

    return 0;
}
