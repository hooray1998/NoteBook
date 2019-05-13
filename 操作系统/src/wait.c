/*=========================================================
> File Name: wait.c
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月27日 星期六 16时01分28秒
> =======================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void child()
{
    puts("Child process");
    exit(123);
}

int main()
{
    int pid;
    pid = fork();
    if (pid == 0)
        child(); 
    wait(NULL);
    puts("Parent process");
    return 0;
}
