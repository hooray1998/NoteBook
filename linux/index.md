# index

> 安装top、strace、lsof命令

## strace

> strace可以跟踪到一个进程产生的系统调用,包括参数，返回值，执行消耗的时间。

6.3. 命令实例
跟踪可执行程序
strace -f -F -o ~/straceout.txt myserver
-f -F选项告诉strace同时跟踪fork和vfork出来的进程，-o选项把所有strace输出写到~/straceout.txt里 面，myserver是要启动和调试的程序。

跟踪服务程序
strace -o output.txt -T -tt -e trace=all -p 28979


## ipcs 

> 可以显示消息队列、共享内存和信号量的信息。


    $ipcs -m 查看系统使用的IPC共享内存资源
    $ipcs -q 查看系统使用的IPC队列资源
    $ipcs -s 查看系统使用的IPC信号量资源


7.2. 系统IPC参数查询

    ipcs -l

    ------ Shared Memory Limits --------
    max number of segments = 4096
    max seg size (kbytes) = 4194303
    max total shared memory (kbytes) = 1073741824
    min seg size (bytes) = 1

    ------ Semaphore Limits --------
    max number of arrays = 128
    max semaphores per array = 250
    max semaphores system wide = 32000
    max ops per semop call = 32
    semaphore max value = 32767

    ------ Messages: Limits --------
    max queues system wide = 2048
    max size of message (bytes) = 524288
    default max size of queue (bytes) = 5242880

## free

释放掉被系统cache占用的数据:

echo 3>/proc/sys/vm/drop_caches


##  sar 找出系统瓶颈的利器
sar是System Activity Reporter（系统活动情况报告）


## readelf

readelf elf文件格式分析
这个工具和objdump命令提供的功能类似，但是它显示的信息更为具体，并且它不依赖BFD库(BFD库是一个GNU项目，它的目标就是希望通过一种统一的接口来处理不同的目标文件）；

ELF文件类型
ELF(Executable and Linking Format)是一种对象文件的格式，用于定义不同类型的对象文件(Object files)中都放了什么东西、以及都以什么样的格式去放这些东西。它自最早在 System V 系统上出现后，被 xNIX 世界所广泛接受，作为缺省的二进制文件格式来使用。可以说，ELF是构成众多xNIX系统的基础之一。
ELF文件有三种类型：

    可重定位的对象文件(Relocatable file) 由汇编器汇编生成的 .o 文件
    可执行的对象文件(Executable file) 可执行应用程序
    可被共享的对象文件(Shared object file) 动态库文件，也即 .so 文件

    .text section 里装载了可执行代码；
    .data section 里面装载了被初始化的数据；
    .bss section 里面装载了未被初始化的数据；
    以 .rec 打头的 sections 里面装载了重定位条目；
    .symtab 或者 .dynsym section 里面装载了符号信息；
    .strtab 或者 .dynstr section 里面装载了字符串信息；
