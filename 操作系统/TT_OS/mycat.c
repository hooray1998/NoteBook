#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
    int i=1;
    while(i<argc)
    {
        int fd;
        fd = open(argv[i],O_RDWR);
        if(fd==-1)
            printf("%s Not Find\n",argv[i]);
        else//opening is ok.
        {
            char buf[257];
            int count = read(fd, buf, 256);
            while(count>0)
            {
                printf("%s",buf);
                int j=0;
                while(j<257) buf[j++] = '\0';
                count = read(fd, buf, 256);
            }
            close(fd);

        }

        i++;

    }
    return 0;
}

