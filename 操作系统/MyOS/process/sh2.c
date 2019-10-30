//>>> 支持输出重定向
#include<stdio.h>//printf
#include<unistd.h>//fork
#include<string.h>//strlen
#include<fcntl.h>
#include<sys/wait.h>//wait
#include<stdlib.h>//exit

void mysys(char *command)
{
    if(NULL!=command)
    {
        pid_t pid;
        pid = fork();

        if(pid==0)
        {
            //judge if command have >
            int len = strlen(command);
            int gt=0;
            while(gt<len&&command[gt++]!='>');
            if(gt!=len){//have >, so change output
                command[gt-1] = 0;//split from >
                command[len-1] = 0;
                int fd_out = open(&command[gt], O_CREAT|O_WRONLY, 0666);//-rw-rw-rw-
                dup2(fd_out, 1);
                pid = fork();
                if(pid==0){
                    mysys(command);
                    //execl("/bin/sh", "sh", "-c", command, NULL);
                    exit(0);
                }
                wait(NULL);
            }
            else
                execl("/bin/sh","sh","-c",command,NULL);
            exit(0);
        }
        wait(NULL);

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
