/*=========================================================
> File Name: src/pthread_demo1.c
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年05月05日 星期日 17时56分13秒
> =======================================================*/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *foo(void *arg){
	for(char i='a';i<'e';i++){
		putchar(i);
		sleep(1);
	}
}

void *bar(void *arg){
	char *s = arg;
	puts(s);
	/*
	int* a = (int*)arg;
	for(int i=0;i<3;i++)
	{
		printf("bar:%d\n", a[i]);
		sleep(1);
	}
	*/

}

int main(){

	int integer = 9;
	int arr[3] = {1,2,3};
	char *string = "hello";
	void *arg = (void *)&integer;
	void *arr_arg = (void *)arr;
	void *s_arg = (void *)string;
	pthread_t tid;
	/*pthread_create(&tid,NULL, &bar, arr_arg);*/
	pthread_create(&tid,NULL, &bar, s_arg);

	for(int i=0;i<3;i++){
		printf("main:%d\n", i);
		sleep(1);
	}
	return 0;
}
