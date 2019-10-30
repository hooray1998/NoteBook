//>>> 不断地运行命令
#include<stdio.h>
#include<unistd.h>

void mysys(char *command)
{
    if(NULL!=command)
    {
        pid_t pid;
        pid = fork();

        if(pid==0)
            execl("/bin/sh","sh","-c",command,NULL);
        wait();

    }
}

int main()
{
    char str[100];
    printf("> ");
    while(1)
    {
        fgets(str,99,stdin);
        mysys(str);
        printf("> ");
    }

    return 0;
}
