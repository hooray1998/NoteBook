#include<stdio.h>
#include<unistd.h>

void mysys(char *cmd)
{
    if(cmd != NULL)
    {
        pid_t pid;
        pid = fork();
        if(pid==0)
            execl("/bin/sh","sh", "-c", cmd, NULL);
        wait();
    }
}
int main(int argc, char* argv[])
{
    char cmd[100];
    do{
        printf("> ");
        fgets(cmd, 99, stdin);
        mysys(cmd);
    }while(1);

    return 0;
}
