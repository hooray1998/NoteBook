#include<stdio.h>
#include<unistd.h>

void mysys(char *cmd)
{
    if(cmd != NULL)
    {
        pid_t pid;
        pid = fork();
        if(pid==0){
            int len = strlen(cmd);
            int xiaoyu=0, shuxian=0;
            while(xiaoyu<len)
                if(cmd[xiaoyu++]=='>')
                    break;

            if(xiaoyu!=len){
                cmd[xiaoyu-1] = 0;
                cmd[len-1] = 0;
                int  fd = open(&cmd[xiaoyu], O_CREAT|O_WRONLY, 0666);
                dup2(fd, 1);
                pid = fork();
                if(pid==0){
                    mysys(cmd);
                    exit(0);
                }
                wait(NULL);
            }
            else{
                execlp("sh", "sh", "-c", cmd, NULL);
            }
            exit(0);

        }
        wait(NULL);
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
