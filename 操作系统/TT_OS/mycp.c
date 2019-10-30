#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
    if(3 == argc)
    {
        int fd1, fd2;
        mode_t mode = 0777;
        fd1 = open(argv[1],O_RDWR, mode);
        fd2 = open(argv[2],O_RDWR | O_CREAT, mode);
        
        if(fd1==-1)
            printf("%s Not Find\n",argv[1]);
        else if(fd2==-1)
            printf("Error in create %s\n",argv[2]);
        else//opening is ok.
        {
            char buf[257];
            int count = read(fd1, buf, 256);
            while(count>0)
            {
                write(fd2, buf, 256);
                int j=0;
                while(j<257) buf[j++] = '\0';
                count = read(fd1, buf, 256);
            }
            close(fd1);
            close(fd2);
        }
    }
    else
        printf("please input two filename\n");

    return 0;
}

