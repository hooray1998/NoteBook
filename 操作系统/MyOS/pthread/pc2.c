//>>> 信号量实现 生产者，计算者，消费者
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define SIZE 4
#define PRODUCE_COUNT (SIZE*2)

char buffer1[SIZE];
char buffer2[SIZE];
int in=0;
int cal=0;
int out=0;

int next(int num){
    return (num+1)%SIZE;
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
sema_t have_site_to_produce_sema;
sema_t have_value_to_calculate_sema;
sema_t have_site_to_calculate_sema;
sema_t have_value_to_consume_sema;

void *Produce(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        sema_wait(&have_site_to_produce_sema);
        sema_wait(&mutex_sema);

        put(i+'a');
        printf("produce:%c\n", i+'a');

        sema_signal(&mutex_sema);
        sema_signal(&have_value_to_calculate_sema);

        i++;
    }
}


void *Calculate(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        sema_wait(&have_value_to_calculate_sema);
        sema_wait(&have_site_to_calculate_sema);
        sema_wait(&mutex_sema);

        calculate();
        printf("\tcalculate\n");

        sema_signal(&mutex_sema);
        sema_signal(&have_site_to_produce_sema);
        sema_signal(&have_value_to_consume_sema);

        i++;
    }
}

void *Consume(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        sema_wait(&have_value_to_consume_sema);
        sema_wait(&mutex_sema);

        printf("\t\tconsume:%c\n", get());

        sema_signal(&mutex_sema);
        sema_signal(&have_site_to_calculate_sema);

        i++;
    }
}

int main(){
    pthread_t consume_pid;
    pthread_t calculate_pid;

    sema_init(&mutex_sema, 1);
    sema_init(&have_site_to_produce_sema, SIZE-1);
    sema_init(&have_value_to_calculate_sema, 0);
    sema_init(&have_site_to_calculate_sema, SIZE-1);
    sema_init(&have_value_to_consume_sema, 0);

    pthread_create(&consume_pid, NULL, &Consume, NULL);
    pthread_create(&calculate_pid, NULL, &Calculate, NULL);

    Produce(NULL);

    pthread_join(consume_pid, NULL);
    pthread_join(calculate_pid, NULL);

    return 0;
}
