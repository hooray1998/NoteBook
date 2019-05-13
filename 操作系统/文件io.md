# 文件IO

### 打开文件

原型
```c
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags);
```

功能
打开已有的文件
如果打开失败，返回-1
如果打开成功，返回值>=0，作为被打开文件的标识符，该整数被称为 **文件描述符**

参数
pathname，指定文件路径
flags, 指定打开参数，可选的取值如下
O_RDONLY	以只读方式打开
O_WRONLY	以只写方式打开
O_RDWR	以读写方式打开
O_APPEND	以追加模式打开，写文件时将内容追加文件末尾
O_TRUNC	如果文件存在，将文件的长度截断为0
O_CREAT	如果文件不存在，创建一个新文件
flags的取值可以用**位或**的方式进行组合
open("log.txt", O_RDWR | O_TRUNC);


### 创建文件

原型
```c
#include <sys/stat.h>
#include <fcntl.h>

int creat(const char *pathname, mode_t mode);
int open(const char *pathname, int flags, mode_t mode);
```

功能
如果文件存在，则打开文件；如果文件不存在，则创建文件
creat(path, mode)和open(path, O_CREAT|O_WRONLY|O_TRUNC, mode)等价

返回值
如果创建失败，返回-1
如果创建成功，返回值>=0，作为被创建文件的标识符，该整数被称为 **文件描述符**

参数
pathname，指定文件路径
flags, 指定打开参数，可选的取值与open相同
mode, 新建文件的访问模式

### 关闭文件

原型
```c
#include <unistd.h>

int close(int fd);
```

功能
将打开的文件关闭
操作系统需要为打开的文件分配资源，需要及时关闭不再使用的文件，从而释放相应资源

参数
fd，使用open或者creat打开的文件描述符


### 读取文件

原型
```c
#include <unistd.h>

int read(int fd, void *buf, size_t count);
```

功能
从打开的文件中读取数据到内存缓冲区
如果读取失败，返回-1
如果读取成功，返回实际读取的字节个数；返回0则代表读取到了文件末尾

参数
fd, 使用open或者creat打开的文件描述符
buf, 内存缓冲区的起始位置
count, 内存缓冲区的长度，read的返回值小于等于count


### 写入文件

原型
```c
#include <unistd.h>

int write(int fd, void *buf, size_t count);
```

功能
把内存缓冲区的数据写入到打开的文件
如果写入失败，返回-1
如果写入成功，返回实际写入的字节个数

参数
fd, 使用open或者creat打开的文件描述符
buf, 内存缓冲区的起始位置
count, 内存缓冲区的长度，write的返回值小于等于count


### 定位文件

原型
```c
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);
```

功能
调整文件的访问位置
read和write从文件的访问位置读写文件

参数
fd, 使用open或者creat打开的文件描述符
offset, 相对于whence的位置偏移量
whence, 根据offset和whence设置文件访问位置，取值如下
SEEK_SET	文件访问位置 = offset
SEEK_CUR	文件访问位置 = 文件访问位置 + offset
SEEK_END	文件访问位置 = 文件尾部位置 + offset

### Demo：简单数据库实现

[miniDB](db.c)
