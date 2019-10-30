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
    printf("------------------------------------------------------------\n");
    mysys("echo HELLO WORLD");
    printf("------------------------------------------------------------\n");
    mysys("ls /");
    printf("------------------------------------------------------------\n");
    return 0;
}
