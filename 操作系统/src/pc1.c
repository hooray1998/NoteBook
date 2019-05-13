/*=========================================================
> File Name: pc1.c
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年05月06日 星期一 15时44分16秒
> =======================================================*/

#include<stdio.h>
#include<pthread.h>

#define SIZE 4
#define PRODUCE_COUNT 10

int buffer[SIZE];
int in=0;
int out=0;

int isEmpty(){
	return in==out;
}
int isFull(){
	return (in+1)%SIZE==out;
}
int get(){
	int n = buffer[out];
	out = (out+1)%SIZE;
	return n;
}
void put(int n){
	buffer[in] = n;
	in = (in+1)%SIZE;
}
pthread_mutex_t mutex;
pthread_cond_t wait_empty_buffer;
pthread_cond_t wait_full_buffer;

void *consume(){

	for(int i=0;i<PRODUCE_COUNT;i++)
	{
		pthread_mutex_lock(&mutex);
		while(isEmpty())
			pthread_cond_wait(&wait_full_buffer, &mutex);
		printf("\tconsume:%d\n", get());
		pthread_cond_signal(&wait_empty_buffer);
		pthread_mutex_unlock(&mutex);
	}
}

void produce(){
	for(int i=0;i<PRODUCE_COUNT;i++){
		pthread_mutex_lock(&mutex);
		while(isFull())
			pthread_cond_wait(&wait_empty_buffer, &mutex);
		put(i+1000);
		printf("produce:%d\n",i+1000);
		pthread_cond_signal(&wait_full_buffer);
		pthread_mutex_unlock(&mutex);
	}
}

int main(){

	pthread_t consume_pid;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&wait_empty_buffer, NULL);
	pthread_cond_init(&wait_full_buffer, NULL);
	/*pthread_t produce_pid;*/

	pthread_create(&consume_pid, NULL, &consume, NULL);
	//pthread_create(&produce_pid, NULL, &produce, NULL);

	produce();

	pthread_join(consume_pid, NULL);

	pthread_mutex_destroy(&mutex);

	return 0;
}
