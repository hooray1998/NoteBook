/*=========================================================
> File Name: ./pipe3.c
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月27日 星期六 17时26分25秒
> =======================================================*/

#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
        dup2(fd[1], 1); 
        close(fd[0]);
        close(fd[1]);

        execlp("cat", "cat", "/etc/passwd", NULL);
        exit(0);
    }
    // parent
    dup2(fd[0], 0); 
    close(fd[0]);
    close(fd[1]);

	wait(NULL);
    /*read(0, buf, sizeof(buf)); */
	execlp("wc", "wc", "-l", NULL);
    /*printf("Receive:%s\n", buf); */
    return 0;
}
