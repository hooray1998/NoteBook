#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define SIZE 4
#define PRODUCE_COUNT 4
int Number = 0;

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
sema_t semaArr[SIZE];

void *Produce(void *arg){
    int curID = *(int *)arg;
    int i=0;

    while(i<PRODUCE_COUNT){
        sema_wait(&semaArr[curID]);
        sema_wait(&mutex_sema);

        printf("ring(%d) => %d\n", curID, Number++);

        sema_signal(&mutex_sema);
        sema_signal(&semaArr[(curID+1)%SIZE]);
        i++;
    }
}


int main(){

    pthread_t pid[SIZE];

    sema_init(&mutex_sema, 1);
    sema_init(&semaArr[0],1);
    int i=1;
    while(i<SIZE){
        sema_init(&semaArr[i], 0);
        i++;
    }

    int ID[SIZE];
    i=0;
    while(i<SIZE){
        ID[i] = i;
        pthread_create(&pid[i], NULL, &Produce, &ID[i]);
        i++;
    }

    i=0;
    while(i<SIZE){
        pthread_join(pid[i++], NULL);
    }

    return 0;
}
