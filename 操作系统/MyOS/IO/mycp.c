//>>> 文件读写
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

int fd_src;
int fd_target;
void readAndWriteFile()
{
    char context[128];
    int count;
    count = read(fd_src, context,  127);
    while(count){
        write(fd_target, context, 127);
        int i=-1;
        while(++i<128) context[i] = '\0';
        count = read(fd_src, context,  127);
    }
}

void openfile(char *src_path, char *target_path)
{
    mode_t mode = 0777;
    fd_src = open(src_path, O_RDONLY, mode);
    if(fd_src<0)
        printf("error in open %s",src_path);
    else
        printf("ok in open %s\n",src_path);

    fd_target = open(target_path, O_WRONLY | O_CREAT, 0600);
    if(fd_target<0)
        printf("error in open %s",target_path);
    else
        printf("ok in open %s\n",target_path);
}

int main(int argc, char **argv)
{
    if(argc>2)
    {
        openfile(argv[1],argv[2]);
        readAndWriteFile();
        close(fd_src);
        close(fd_target);
    }
    else
    {
        puts("please in put two file");
    }

    return 0;
}
