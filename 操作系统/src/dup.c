/*=========================================================
> File Name: src/dup.c
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月27日 星期六 16时59分38秒
> =======================================================*/

#include<unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
  
int main(){
	int fd;
	fd = open("log.txt", O_CREAT|O_RDWR, 0666); 
	int newfd = dup(fd); 
	close(fd); 
	write(0, "hello\n", 6);
	return 0;
}
