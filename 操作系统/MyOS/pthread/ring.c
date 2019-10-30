//>>> 信号量实现轮着踢球
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define SIZE 4
#define PRODUCE_COUNT 3

int ball=0;

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
    sema->value++;
    pthread_cond_signal(&sema->cond);
    pthread_mutex_unlock(&sema->mutex);
}

sema_t mutex_sema;
sema_t flag[SIZE];

void *Consume(void *arg){
    int cur = *(int *)arg;
    int i=0;
    while(i<PRODUCE_COUNT){
        sema_wait(&flag[cur]);
        sema_wait(&mutex_sema);

        printf("\t\tcur[%d] => %d\n",cur, ball++);

        sema_signal(&mutex_sema);
        sema_signal(&flag[(cur+1)%SIZE]);

        i++;
    }
    return NULL;
}

int main(){
    pthread_t tid[SIZE];

    sema_init(&mutex_sema, 1);

    sema_init(&flag[0], 1);
    int i=1;
    while(i<SIZE)
        sema_init(&flag[i++], 0);

    int id[SIZE];
    i = 0;
    while(i<SIZE){
        id[i] = i;
        pthread_create(&tid[i], NULL, &Consume, &id[i]);
        i++;
    }

    i = 0;
    while(i<SIZE)
        pthread_join(tid[i++], NULL);

    return 0;
}
