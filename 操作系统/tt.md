# tt的代码思想

## myecho.c

- 通过main函数的参数获取命令行参数。
- main函数参数为(int argc,char \*argv[]) ，其中：
	1. argc代表参数的个数。
	2. 所有的参数存储在argv字符指针数组中。
	3. 可以通过argv[i]访问第i个命令行参数。
	4. 由于第0个代表可执行程序本身，所以从第1个开始打印。
- 使用while循环逐个打印命令行参数。从而实现echo的效果。

```c
#include<unistd.h>
#include<stdio.h>
int main(int argc,char *argv[])
{
    int i=1;
    while(i<argc)
    {
        printf("%s ",argv[i]);
        i++;
    }
    printf("\n");
    return 0;
}
```

## mycat.c

1. 使用系统调用open/read/close实现
2. 使用main函数的参数依次获取文件名。
3. 对于每一个文件执行如下操作
	1. 定义文件描述符fd。
	2. 使用open系统调用打开文件。同时判断文件是否存在。
	3. 若文件存在，使用read系统调用读取文件内容。
	4. 同时考虑文件大小的不确定性，使用大小为256字节的数组存储读取的内容。然后循环读取文件内容。
	5. 直到文件结束。
	6. 此时使用close系统调用关闭文件描述符。

```c

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

```

## mycp.c


1. 使用系统调用open/read/write/close实现
2. 由于cp命令后跟的是源文件和目标文件，所以需要使用argc判断命令行参数的个数。只有数量是3时，才会继续执行。
3. 定义两个文件描述符，使用open使它们分别指向源文件和目标文件。 
	- 目标文件不存在需要创建。
4. 判断这两个文件是否打开成功。
5. 如果打开成功：
	1. 定义一个257字节大小的数组。
	2. 循环从源文件中使用read读取256个字节，然后使用write系统调用写入到目标文件中
	3. 直到源文件结束。
6. 使用close关闭上述文件



```c
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
```


# 多进程

## mysys.c


1. 使用fork/exec/wait系统调用实现mysys
2. 定义mysys函数。函数实现细节如下：
	1. 首先判断当前的命令是否为空，若非空则继续。
	2. 使用fork创建一个子进程。
	3. 在子进程中执行当前命令。
	4. 使用wait等待子进程结束。
3. 使用两个测试命令测试mysys的执行情况。

```c

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
```


## sh1.c

1. 使用while循环打印提示符>，并使用fgets接受用户输入的命令。
2. 使用mysys函数创建子进程执行命令。
3. mysys函数实现细节如下：
	1. 首先判断当前的命令是否为空，若非空则继续。
	2. 使用fork创建一个子进程。
	3. 在子进程中执行当前命令。
	4. 使用wait等待子进程结束。


```c

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
    char cmd[100];
    do{
        printf("> ");
        fgets(cmd, 99, stdin);
        mysys(cmd);
    }while(1);

    return 0;
}
```

## sh2.c


1. 使用while循环打印提示符>，并使用fgets接受用户输入的命令。
2. 使用mysys函数创建子进程执行命令。
3. mysys函数实现细节如下：
	1. 首先判断当前的命令是否为空，若非空则继续。
	2. 使用fork创建一个子进程。
	3. 使用while遍历命令，查看是否使用输出重定向符号&gt;
	4. 若存在文件重定向，则记录出现的位置。
	5. 因为重定向符号后是输出文件的文件名，所以定义一个文件描述符指向该输出文件。并使用dup2将该描述符重定向到标准输出。这样的效果就是如果有数据要显示到标准输出，那么它就会写入该文件。
	2. 使用fork创建一个子进程。
	3. 在子进程中执行重定向符号之前的命令。该命令产生的输出都会写入文件中。
	4. 主进程使用wait等待子进程结束。
	4. 若不存在文件重定向，则直接执行该指令。
	

```c

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
```

## sh3.c


1. 使用while循环打印提示符>，并使用fgets接受用户输入的命令。
2. 使用mysys函数创建子进程执行命令。
3. mysys函数实现细节如下：
	1. 首先判断当前的命令是否为空，若非空则继续。
	2. 使用fork创建一个子进程。
	3. 使用while遍历命令，查看是否使用输出重定向符号&gt或管道符号|。
	4. 若存在管道符号，则记录出现的位置。
	3. 定义一个pipe并初始化。
	2. 使用fork创建一个子进程。
	3. 在子进程中重定向管道的写端到标准输出。代表该命令产生的输出都会通过管道写出去。
	3. 子进程重定向标准输入到管道的读端。
	4. 主进程使用wait等待子进程结束。
	4. 若存在文件重定向，则记录出现的位置。
	5. 因为重定向符号后是输出文件的文件名，所以定义一个文件描述符指向该输出文件。并使用dup2将该描述符重定向到标准输出。这样的效果就是如果有数据要显示到标准输出，那么它就会写入该文件。
	2. 使用fork创建一个子进程。
	3. 在子进程中执行重定向符号之前的命令。该命令产生的输出都会写入文件中。
	4. 主进程使用wait等待子进程结束。
	4. 若不存在文件重定向和管道，则直接执行该指令。



```c

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<stdlib.h>


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
            while(shuxian<len)
                if(cmd[shuxian++]=='|')
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
            else if(shuxian!=len){
                cmd[shuxian-1] = 0;
                cmd[len-1] = 0;

                int fd[2];
                pipe(fd);

                pid = fork();
                if(pid==0){
                    dup2(fd[1],1);
                    close(fd[0]);
                    close(fd[1]);
                    execlp("sh", "sh", "-c", cmd, NULL);
                    exit(0);
                }
                dup2(fd[0], 0);
                close(fd[0]);
                close(fd[1]);
                execlp("sh", "sh", "-c", &cmd[shuxian], NULL);
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
```

# 多线程

## pi1.c


1. 在main函数主线程使用pthread_create创建1个辅助线程
2. 并传入该线程执行的函数。
3. 该函数通过循环计算级数的后半部分
4. 并通过return返回结果
5. 主线程计算级数的前半部分
6. 并使用pthread_join等待辅助线程运行結束,使用sum2获取线程的结果。
7. 最后在主线程中将前半部分和后半部分相加,输出结果

```c

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define SIZE 10000  //the size of all numbers

void *another(void *arg){
    double *sum = (double*)malloc(sizeof(double));
    *sum = 0;
    short sign = ((SIZE/2)%2==0)?1:-1;
    int i=0;
    while(i<SIZE/2){
        *sum += sign*(double)1/(2*i+1+SIZE);
        sign = - sign;
        i++;
    }

    return (void *)sum;
}

int main(){

    pthread_t pid;
    pthread_create(&pid, NULL, &another, NULL);

    double sum1=0;
    short sign = 1;
    int i=0;
    while(i<SIZE/2){
        sum1 += sign*(double)1/(2*i+1);
        sign = - sign;
        i++;
    }
    double *sum2 = (double *)malloc(sizeof(double));
    pthread_join(pid, (void **)&sum2);

    printf("sum is %f.\n", sum1+*sum2);

    return 0;
}
```

## pi2.c


子线程：

1. 通过类型转化，获取函数参数中所对应的索引信息。
2. 通过该信息得知从哪个数进行计算。
3. 然后循环计算累加值，最后返回。

主线程：

1. 创建多个线程，并通过参数传入各个进程执行的函数需要使用的位置索引。
2. 等待所有进程结束，并通过pthread_join获取各个线程的返回值。
3. 累加所有的返回值，完成计算。

```c

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define SIZE 10000  //the size of all numbers
#define PTHREAD_SIZE 100  //the size of all pthreads

void *another(void *arg){
    double *sum = (double*)malloc(sizeof(double));
    int start = *(int *)arg;
    *sum = 0;
    short sign = ((start/2)%2==0)?1:-1;
    int i=start;
    while(i<(start + SIZE/PTHREAD_SIZE)){
        *sum += sign*(double)1/(2*i+1);
        sign = - sign;
        i++;
    }

    return (void *)sum;
}

int main(){

    pthread_t pidArr[PTHREAD_SIZE];
    int start[PTHREAD_SIZE];

    int cur_start = 0;
    int i=0;
    while(i<PTHREAD_SIZE){

        start[i] = cur_start;
        void *arg = (void *)(start + i);
        pthread_create(&pidArr[i], NULL, &another, arg);
        cur_start += SIZE/PTHREAD_SIZE;
        i++;
    }

    double allSum = 0;
    i=0;

    while(i<PTHREAD_SIZE){
        double *sum;
        pthread_join(pidArr[i], (void **)&sum);
        allSum += *sum;
        free(sum);
        i++;
    }

    printf("sum is %f.\n", allSum);

    return 0;
}
```

## sort.c

子线程：

1. 通过函数参数得到数组的地址。
2. 然后计算数组的长度，从而确定自己需要排序的区间。
3. 使用排序算法进行排序。


主线程：

1. 随机产生一百个数
2. 创建一个子线程，并将数组的地址作为参数传过去。
3. 使用选择排序算法对数组的前半部分进行排序。
4. 使用pthread_join等待进程结束。
5. 然后使用归并算法对数组的全部元素进行归并。
6. 完成排序。

```c

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define SIZE 20  //the size of all numbers

void *another(void *arg){
    int *arr = (int *)arg;
    int len = SIZE - SIZE/2;

    int min, temp;
    int i=0,j;
    while(i<len){
        min = i;
        j = i+1;
        while(j<len){
            if(arr[j]<arr[min])
                min = j;
            j++;
        }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
        i++;
    }

    return NULL;
}

int main(){

    int arr[SIZE];
    int i=0,j;
    while(i<SIZE){
        arr[i++] = rand()%100;
    }

    void *arg = (void *)(arr + SIZE/2);

    pthread_t pid;
    pthread_create(&pid, NULL, &another, arg);

    int min, temp;
    i=0;
    while(i<SIZE/2){
        min = i;
        j = i+1;
        while(j<SIZE/2){
            if(arr[j]<arr[min])
                min = j;
            j++;
        }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
        i++;
    }

    pthread_join(pid, NULL);
    
    i=0,j=SIZE/2;
    while(i<SIZE/2&&j<SIZE){
        if(arr[i]<arr[j]){
            printf("%d ", arr[i]);
            i++;
        }
        else{
            printf("%d ", arr[j]);
            j++;
        }
    }

    while(i<SIZE/2){
        printf("%d ", arr[i++]);
    }
    while(j<SIZE){
        printf("%d ", arr[j++]);
    }
    printf("\n");


    return 0;
}
```

# 信号量和条件变量

## pc1.c


1. 主线程作为生产者，主线程创建两个子线程分别作为计算者和消费者。
2. 定义四个条件变量。意义分别是：是否有空位用来生产，是否有空位用来存储计算结果，是否有生产过的用来计算，是否有计算好的用来消费。

生产者：

1. 判断是否有空位用来生产。
2. 如果没有，则阻塞。
3. 如果有，产生结果，并存储到缓冲区1。
4. 同时signal条件变量wait_fullOfCal。

计算者：

1. 判断是否有需要计算的资源。若没有，则阻塞。
2. 判断是否有存储计算结果的位置。若没有，则阻塞。
3. 如果上述条件满足，则计算。
4. 结束时signal条件变量wait_fullOfCon和wait_emptyOfPro

消费者：

1. 判断是否有可以消费的资源。若没有，则阻塞。
2. 如果上述条件满足，则打印（消费）。
3. 结束时signal条件变量wait_emptyOfCal。


```c

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define SIZE 4
#define PRODUCE_COUNT 8

char buffer1[SIZE];
char buffer2[SIZE];
int in=0;
int cal=0;
int out=0;

int emptyOfCon(){
    return cal==out;
}

int emptyOfCal(){
    return cal==in;
}

int fullOfCal(){
    return (cal+1)%SIZE==out;
}

int fullOfPro(){
    return (in+1)%SIZE==cal;
}

char get(){
    char n = buffer2[out];
    out = (out+1)%SIZE;
    return n;
}

void put(char n){
    buffer1[in] = n;
    in = (in+1)%SIZE;
}

void calculate(){
    buffer2[cal] = buffer1[cal] + 'A' - 'a';
    cal = (cal+1)%SIZE;
}

pthread_mutex_t mutex;
pthread_cond_t wait_emptyOfPro;
pthread_cond_t wait_fullOfCal;
pthread_cond_t wait_emptyOfCal;
pthread_cond_t wait_fullOfCon;

void *Produce(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        pthread_mutex_lock(&mutex);
        while(fullOfPro())
            pthread_cond_wait(&wait_emptyOfPro, &mutex);

        put(i+'a');
        printf("produce=>%c\n", i+'a');

        pthread_cond_signal(&wait_fullOfCal);
        pthread_mutex_unlock(&mutex);
        i++;
    }
}

void *Calculate(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        pthread_mutex_lock(&mutex);
        while(emptyOfCal())
            pthread_cond_wait(&wait_fullOfCal, &mutex);
        while(fullOfCal())
            pthread_cond_wait(&wait_emptyOfCal, &mutex);

        calculate();
        printf("\tcalculate<=\n");

        pthread_cond_signal(&wait_fullOfCon);
        pthread_cond_signal(&wait_emptyOfPro);
        pthread_mutex_unlock(&mutex);
        i++;
    }
}

void *Consume(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        pthread_mutex_lock(&mutex);
        while(emptyOfCon())
            pthread_cond_wait(&wait_fullOfCon, &mutex);

        printf("\t\tconsume=>%c\n", get());

        pthread_cond_signal(&wait_emptyOfCal);
        pthread_mutex_unlock(&mutex);
        i++;
    }
}

int main(){

    pthread_t consumePid;
    pthread_t calculatePid;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&wait_emptyOfPro, NULL);
    pthread_cond_init(&wait_emptyOfCal, NULL);
    pthread_cond_init(&wait_fullOfCal, NULL);
    pthread_cond_init(&wait_fullOfCon, NULL);

    pthread_create(&consumePid, NULL, &Consume, NULL);
    pthread_create(&calculatePid, NULL, &Calculate, NULL);

    Produce(NULL);

    pthread_join(consumePid, NULL);
    pthread_join(calculatePid, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
```

## pc2.c


1. 定义五个信号量， mutex_sema emptyOfPro_sema fullOfCal_sema emptyOfCal_sema fullOfCon_sema
2. 后四个的含义非别是可以生产的空位的个数，可以计算的个数，可以存储计算结果的个数，可以消费的资源个数。
3. 主线程作为生产者，主线程创建两个子线程分别作为计算者和消费者。


生产者：

1. 判断是否有空位用来生产。
2. 如果没有，则阻塞。
3. 如果有，emptyOfPro_sema的值减一，产生结果，并存储到缓冲区1。
4. 同时释放信号量fullOfCal_sema

计算者：

1. 判断是否有需要计算的资源。若没有，则阻塞。
2. 判断是否有存储计算结果的位置。若没有，则阻塞。
3. 如果上述条件满足，fullOfCal_sema和emptyOfCal_sema的值减一，进行计算。
4. 结束时释放信号量emptyOfPro_sema和fullOfCon_sema

消费者：

1. 判断是否有可以消费的资源。若没有，则阻塞。
2. 如果上述条件满足，fullOfCon_sema的值减一，则打印（消费）。
3. 结束时释放信号量emptyOfCal_sema



```c

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define SIZE 4
#define PRODUCE_COUNT 8

char buffer1[SIZE];
char buffer2[SIZE];
int in=0;
int cal=0;
int out=0;


char get(){
    char n = buffer2[out];
    out = (out+1)%SIZE;
    return n;
}

void put(char n){
    buffer1[in] = n;
    in = (in+1)%SIZE;
}

void calculate(){
    buffer2[cal] = buffer1[cal] + 'A' - 'a';
    cal = (cal+1)%SIZE;
}

typedef struct{
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}sema_t;

void sema_init(sema_t *sema, int value){
    sema->value = value;
    pthread_mutex_init(&sema->mutex, NULL);
    pthread_cond_init(&sema->cond, NULL);
}

void sema_wait(sema_t *sema){
    pthread_mutex_lock(&sema->mutex);
    while(sema->value <= 0)
        pthread_cond_wait(&sema->cond, &sema->mutex);

    sema->value--;
    pthread_mutex_unlock(&sema->mutex);
}

void sema_signal(sema_t *sema){
    pthread_mutex_lock(&sema->mutex);
    ++sema->value;
    pthread_cond_signal(&sema->cond);
    pthread_mutex_unlock(&sema->mutex);
}

sema_t mutex_sema;
sema_t emptyOfPro_sema;
sema_t fullOfCal_sema;
sema_t emptyOfCal_sema;
sema_t fullOfCon_sema;

void *Produce(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        sema_wait(&emptyOfPro_sema);
        sema_wait(&mutex_sema);

        put(i+'a');
        printf("produce=>%c\n", i+'a');

        sema_signal(&mutex_sema);
        sema_signal(&fullOfCal_sema);
        i++;
    }
}

void *Calculate(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        sema_wait(&fullOfCal_sema);
        sema_wait(&emptyOfCal_sema);
        sema_wait(&mutex_sema);

        calculate();
        printf("\tcalculate<=\n");

        sema_signal(&mutex_sema);
        sema_signal(&emptyOfPro_sema);
        sema_signal(&fullOfCon_sema);
        i++;
    }
}

void *Consume(void *arg){
    int i=0;
    while(i<PRODUCE_COUNT){
        sema_wait(&fullOfCon_sema);
        sema_wait(&mutex_sema);

        printf("\t\tconsume=>%c\n", get());

        sema_signal(&mutex_sema);
        sema_signal(&emptyOfCal_sema);
        i++;
    }
}

int main(){

    pthread_t consumePid;
    pthread_t calculatePid;

    sema_init(&mutex_sema, 1);
    sema_init(&emptyOfPro_sema,SIZE-1);
    sema_init(&fullOfCal_sema,0);
    sema_init(&emptyOfCal_sema,SIZE-1);
    sema_init(&fullOfCon_sema,0);

    pthread_create(&consumePid, NULL, &Consume, NULL);
    pthread_create(&calculatePid, NULL, &Calculate, NULL);

    Produce(NULL);

    pthread_join(consumePid, NULL);
    pthread_join(calculatePid, NULL);

    return 0;
}
```

## ring.c

1. 主线程定义SIZE个信号量。
2. 初始第一个信号量为1，其余为0
3. 创建SIZE个线程，并通过函数参数告诉每个线程自己的身份ID


对于每个线程：

1. 通过函数参数获取自己的ID。
2. 执行时wait第ID个信号量，然后输出当前的值并累加。
3. 结束释放第ID个的后一个信号量。
4. 从而实现环形轮流并行传递足球。

```c

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define SIZE 4
#define PRODUCE_COUNT 4
int Number = 0;

typedef struct{
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}sema_t;

void sema_init(sema_t *sema, int value){
    sema->value = value;
    pthread_mutex_init(&sema->mutex, NULL);
    pthread_cond_init(&sema->cond, NULL);
}

void sema_wait(sema_t *sema){
    pthread_mutex_lock(&sema->mutex);
    while(sema->value <= 0)
        pthread_cond_wait(&sema->cond, &sema->mutex);

    sema->value--;
    pthread_mutex_unlock(&sema->mutex);
}

void sema_signal(sema_t *sema){
    pthread_mutex_lock(&sema->mutex);
    ++sema->value;
    pthread_cond_signal(&sema->cond);
    pthread_mutex_unlock(&sema->mutex);
}

sema_t mutex_sema;
sema_t semaArr[SIZE];

void *Produce(void *arg){
    int curID = *(int *)arg;
    int i=0;

    while(i<PRODUCE_COUNT){
        sema_wait(&semaArr[curID]);
        sema_wait(&mutex_sema);

        printf("ring(%d) => %d\n", curID, Number++);

        sema_signal(&mutex_sema);
        sema_signal(&semaArr[(curID+1)%SIZE]);
        i++;
    }
}


int main(){

    pthread_t pid[SIZE];

    sema_init(&mutex_sema, 1);
    sema_init(&semaArr[0],1);
    int i=1;
    while(i<SIZE){
        sema_init(&semaArr[i], 0);
        i++;
    }

    int ID[SIZE];
    i=0;
    while(i<SIZE){
        ID[i] = i;
        pthread_create(&pid[i], NULL, &Produce, &ID[i]);
        i++;
    }

    i=0;
    while(i<SIZE){
        pthread_join(pid[i++], NULL);
    }

    return 0;
}
```

