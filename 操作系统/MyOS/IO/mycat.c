//>>> 文件读
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

int fd;
void readfile(char *filepath)
{
    char context[101];
    int count;
    do{
        memset(context,0,101);//clean array
        count = read(fd, &context,  100);
        printf("%s",context);
    }while(count>0);
}

void openfile(char *filepath)
{
    mode_t mode = 0777;
    fd = open(filepath, O_RDWR, mode);
    if(fd<0)
        puts("error in open file");
}

int main(int argc, char **argv)
{
    while(*++argv!=NULL)
    {
        openfile(*argv);
        readfile(*argv);
        close(fd);
    }

    return 0;
}
