/*=========================================================
> File Name: ./pipe2.c
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月27日 星期六 17时10分11秒
> =======================================================*/

#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pid;    
    int fd[2];
    char buf[32];

    pipe(fd); 
    pid = fork(); 
    if (pid == 0) {
        // child
		close(fd[1]); 
		read(fd[0], buf, sizeof(buf)); 
		printf("Receive:%s\n", buf); 
        exit(0);
    }
    // parent
	close(fd[0]); 
	write(fd[1], "hello", 6); 
    return 0;
}
