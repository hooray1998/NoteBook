//>>> 运行命令
#include<stdio.h>
#include<unistd.h>

void mysys(char *command)
{
    pid_t pid;
    pid = fork();

    if(pid==0)
        execl("/bin/sh","sh","-c",command,NULL);
    wait();

}

int main(int argc, char **argv)
{

    printf("-------------------------------------\n");
    mysys("echo hello world");
    printf("-------------------------------------\n");
    mysys("ls /");
    printf("-------------------------------------\n");

    return 0;
}
