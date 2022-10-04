# 100-gdb-tips

TODO: campus_utils 制作这个.gdbrc文件，  逐行打印结构体

## 信息显示

show version # 版本
show copying # 版权
gdb -q # 启动时不显示提示信息
set confirm off # 退出时不显示提示信息
set pagination off 或 set height 0 # 不分页输出

## 函数

info functions # 显示所有带符号信息和不带符号信息的函数列表
info functions <regex> # 显示符合规则的函数列表
step、s # 进入带调试信息的函数内部
next、n # 不进入函数内部
set step-mode on # 可以通过step进入没有调试信息的函数， 比如printf
finish # 执行完函数退出
return <expression> # 直接返回
call 或者 print # 直接执行函数

i frame # 显示函数堆栈信息
i registers # 显示寄存器
disassemble <funcname> # 显示函数的汇编指令

当一个函数最后一条指令是调用另外一个函数时，开启优化选项(`-O`)的编译器常常以最后被调用的函数返回值作为调用者的返回值，这称之为“尾调用（`Tail call`）”. 默认`i frame`看不到尾调用的信息， 可以通过 `set debug entry-values 1` 开启， 可以看到`tailcall: initial:`信息。

frame 0/1/2 or frame <addr> 切换当前的函数堆栈帧, bt可以看到所有堆栈帧的序号和地址， i frame可以看到当前堆栈帧信息
up [number] / down [number] / up-silently [number] / down-silently [number] 上下切换, up(1->2)


## 断点

b Foo::foo
b (anonymous namespace)::bar # 匿名空间
(gdb) b *0x400522 # 在程序地址上打断点
readelf -h a.out # 可以查看程序入口地址
（gdb） info files # 查看程序入口地址
如果没有调试信息， main函数找不到的情况下， 直接执行start没有效果， 需要断点入口地址， 然后run
b file.c:6
b 6

断点保存与加载
save breakpoints <file-name-to-save>
source file-name-to-save

tb / tbreak # 让断点只生效一次
b 10 if i==101 # 条件断点
ignore bnum count # 忽略接下来count次的断点bnum


## 观察点

watch *(data type*)address
`watch a` 与 `watch *(int*)0x6009c8` 效果相同
```sh
(gdb) p &a
$1 = (int *) 0x6009c8 <a>
(gdb) watch *(int*)0x6009c8
Hardware watchpoint 2: *(int*)0x6009c8
```

查看观察点 `info watchpoints`
watch a thread 3 # 设置观察点只针对特定线程生效
rw / rwatch a # 当发生读取变量行为时，程序就会暂停住。
aw / awatch a # 当发生读取变量或改变变量值的行为时，程序就会暂停住。

## Catchpoint
https://www.cnblogs.com/arnoldlu/p/13815087.html
catch load # 捕获load 动态库
`set $rax = 0` # 通过修改rax寄存器的值，达到修改返回值的目的


## 打印

	char str1[] = "abcd";
	wchar_t str2[] = L"abcd";

用gdb调试程序时，可以使用“`x/s`”命令打印ASCII字符串。
由于当前平台宽字符的长度为4个字节，则用“`x/ws`”命令。如果是2个字节，则用“`x/hs`”命令。

打印数组
如果要打印索引下标，则可以通过如下命令进行设置：

	(gdb) set print array-indexes on
	p *array@num
	p array[60]@10

bt full n

打印进程内存信息
用gdb调试程序时，如果想查看进程的内存映射信息，可以使用“i proc mappings”命令（i是info命令缩写），首先输出了进程的flags，接着是进程的内存映射信息。  
此外，也可以用"i files"（还有一个同样作用的命令：“i target”）命令，它可以更详细地输出进程的内存信息，包括引用的动态链接库等等，例如：

打印静态变量的值:你可以显式地指定文件名（上下文）：

	(gdb) p 'static-1.c'::var


打印变量的类型和所在文件

	(gdb) whatis he
	(gdb) ptype he
	(gdb) i variables ^he$ #gdb会显示所有包含（匹配）该表达式的变量。如果只想查看完全匹配给定名字的变量：

### 打印内存的值

gdb中使用“`x`”命令来打印内存的值，格式为“`x/nfu addr`”。含义为以`f`格式打印从`addr`开始的`n`个长度单元为`u`的内存值。参数具体含义如下：  
a）n：输出单元的个数。  
b）f：是输出格式。比如`x`是以16进制形式输出，`o`是以8进制形式输出,等等。  
c）u：标明一个单元的长度。`b`是一个`byte`，`h`是两个`byte`（halfword），`w`是四个`byte`（word），`g`是八个`byte`（giant word）。  

以上面程序为例：  
（1） 以16进制格式打印数组前`a`16个byte的值：  

	(gdb) x/16xb a
	0x7fffffffe4a0: 0x00    0x01    0x02    0x03    0x04    0x05    0x06    0x07
	0x7fffffffe4a8: 0x08    0x09    0x0a    0x0b    0x0c    0x0d    0x0e    0x0f
（2） 以无符号10进制格式打印数组`a`前16个byte的值：  

	(gdb) x/16ub a
	0x7fffffffe4a0: 0       1       2       3       4       5       6       7
	0x7fffffffe4a8: 8       9       10      11      12      13      14      15
（3） 以2进制格式打印数组前16个`a`byte的值：  

	(gdb) x/16tb a
	0x7fffffffe4a0: 00000000        00000001        00000010        00000011        00000100        00000101        00000110        00000111
	0x7fffffffe4a8: 00001000        00001001        00001010        00001011        00001100        00001101        00001110        00001111
（4）  以16进制格式打印数组`a`前16个word（4个byte）的值：  

	(gdb) x/16xw a
	0x7fffffffe4a0: 0x03020100      0x07060504      0x0b0a0908      0x0f0e0d0c
	0x7fffffffe4b0: 0x13121110      0x17161514      0x1b1a1918      0x1f1e1d1c
	0x7fffffffe4c0: 0x23222120      0x27262524      0x2b2a2928      0x2f2e2d2c
	0x7fffffffe4d0: 0x33323130      0x37363534      0x3b3a3938      0x3f3e3d3c


如上所示，在gdb中可以使用`list`（简写为l）命令来显示源代码以及行号。`list`命令可以指定行号，函数：
### 每行打印一个结构体成员 
可以执行“set print pretty on”命令，这样每行只会显示结构体的一名成员，而且还会根据成员的定义层次进行缩进：

# 按照派生类型打印对象
	(gdb) set print object on


# 指定程序的输入输出设备

	$ tty
	/dev/pts/2

	(gdb) tty /dev/pts/2


"`x`"命令会把最后检查的内存地址值存在“`$_`”这个“convenience variable”中，并且会把这个地址中的内容放在“`$__`”这个“convenience variable”，以上面程序为例:

用gdb调试程序时，可以用下面的自定义命令，打印程序动态分配内存的信息：  

    define mallocinfo
      set $__f = fopen("/dev/tty", "w")
      call malloc_info(0, $__f)
      call fclose($__f)
    end

	(gdb) p func2::b
	$1 = 2
	(gdb) p func3::b
	$2 = 3

## 多进程、线程 


如果要调试子进程，要使用如下命令：“set follow-fork-mode child”，例如：
如果要同时调试父进程和子进程，可以使用“`set detach-on-fork off`”（默认`detach-on-fork`是`on`）命令，这样gdb就能同时调试父子进程，并且在调试一个进程时，另外一个进程处于挂起状态。仍以上面程序为例：

前面带“*”表示的是“current thread”，可以理解为gdb调试多线程程序时，选择的一个“默认线程”。
(gdb) thread apply all bt

如果不想显示这些信息，可以使用“`set print thread-events off`”命令，这样当有线程产生和退出时，就不会打印提示信息：

如果想在调试一个线程时，让其它线程暂停执行，可以使用“`set scheduler-locking on`”命令：
此外，“`set scheduler-locking`”命令除了支持`off`和`on`模式外（默认是`off`），还有一个`step`模式。含义是：当用"`step`"命令调试线程时，其它线程不会执行，但是用其它命令（比如"`next`"）调试线程时，其它线程也许会执行。

首先设置了观察点：“wa a”（`wa`是`watch`命令缩写），也就是当`a`的值发生变化时，程序会暂停，接下来在`commands`语句中打印线程号。  

	(gdb) command 2
	Type commands for breakpoint(s) 2, one per line.
	End with a line saying just "end".
	>printf "thread id=%d\n", $_thread
	>end


当被调试的程序正常退出时，gdb会使用`$_exitcode`这个“`convenience variable`”记录程序退出时的“`exit code`”。以调试上面程序为例:


## coredump文件

主动生成corefile

	(gdb) generate-core-file
	Saved corefile core.12955

## 汇编 

用gdb调试程序时，如果想查看寄存器的值，可以使用“i registers”命令（i是info命令缩写），例如:  
以上输出不包括浮点寄存器和向量寄存器的内容。使用“i all-registers”命令，可以输出所有寄存器的内容：
使用“disassemble /r”命令可以用16进制形式显示程序的原始机器码。以上面程序为例：

	(gdb) disassemble /r main
	Dump of assembler code for function main:

## 改变程序的执行

也可以用“`set {type}address=expr`”的方式，含义是给存储地址在`address`，变量类型为`type`的变量赋值，仍以上面代码为例：  

	(gdb) p &i
	$5 = (int *) 0x8047a54
	(gdb) set {int}0x8047a54 = 8

	(gdb) set var $eax = 8
可以看到因为eax寄存器存储着函数的返回值，所以当把eax寄存器的值改为`8`后，函数的返回值也变成了`8`。  

修改pc寄存器， 跳过某些步骤

	(gdb) disassemble main
	Dump of assembler code for function main:
	0x08050921 <main+0>:    push   %ebp
	0x08050922 <main+1>:    mov    %esp,%ebp
	0x08050924 <main+3>:    sub    $0x8,%esp
	0x08050927 <main+6>:    and    $0xfffffff0,%esp
	0x0805092a <main+9>:    mov    $0x0,%eax
	(gdb) p $pc
	$3 = (void (*)()) 0x8050944 <main+35>
	(gdb) set var $pc=0x08050949

1. `jump`命令只改变pc的值，所以改变程序执行可能会出现不同的结果，比如变量i的值

**使用断点命令改变程序的执行**: 每次到断点1都会执行一些命令

	(gdb) command 1
	Type commands for breakpoint(s) 1, one per line.
	End with a line saying just "end".
	>silent
	>set variable n = 0
	>continue
	>end
	(gdb)


gdb不仅可以用来调试程序，还可以修改程序的二进制代码。
缺省情况下，gdb是以只读方式加载程序的。可以通过命令行选项指定为可写：

	$ gcc -write ./a.out
	(gdb) show write
	Writing into executable and core files is on.

也可以在gdb中，使用命令设置并重新加载程序：

	(gdb) set write on
	(gdb) file ./a.out
	(gdb) set variable *(short*)0x400651=0x0ceb
	(gdb) disassemble /mr drawing 

## 信号


用gdb调试程序时，可以用“`i signals`”命令（或者“`i handle`”命令，`i`是`info`命令缩写）查看gdb如何处理进程收到的信号:  

	(gdb) i signals 
	Signal        Stop      Print   Pass to program Description
	
	SIGHUP        Yes       Yes     Yes             Hangup
	SIGINT        Yes       Yes     No              Interrupt
	SIGQUIT       Yes       Yes     Yes             Quit
	......
	SIGALRM       No        No      Yes             Alarm clock
	......

第一项（`Signal`）：标示每个信号。  
第二项（`Stop`）：表示被调试的程序有对应的信号发生时，gdb是否会暂停程序。  
第三项（`Print`）：表示被调试的程序有对应的信号发生时，gdb是否会打印相关信息。  
第四项（`Pass to program`）：gdb是否会把这个信号发给被调试的程序。  
第五项（`Description`）：信号的描述信息。

从上面的输出可以看到，当`SIGINT`信号发生时，gdb会暂停被调试的程序，并打印相关信息，但不会把这个信号发给被调试的程序。而当`SIGALRM`信号发生时，gdb不会暂停被调试的程序，也不打印相关信息，但会把这个信号发给被调试的程序。  

用gdb调试程序时，可以用“`handle signal stop/nostop`”命令设置当信号发生时，是否暂停程序的执行，以上面程序为例:  
用gdb调试程序时，可以用“`handle signal print/noprint`”命令设置当信号发生时，是否打印信号信息，以上面程序为例:  
用gdb调试程序时，可以用“`handle signal pass(noignore)/nopass(ignore)`”命令设置当信号发生时，是否把信号丢给程序处理.其中`pass`和`noignore`含义相同，`nopass`和`ignore`含义相同。以上面程序为例:  

用gdb调试程序的过程中，当被调试程序停止后，可以用“`signal signal_name`”命令让程序继续运行，但会立即给程序发送信号。以上面程序为例:  

	(gdb) r
	`/data1/nan/test' has changed; re-reading symbols.
	Starting program: /data1/nan/test 
	[Thread debugging using libthread_db enabled]
	^C[New Thread 1 (LWP 1)]
	
	Program received signal SIGINT, Interrupt.
	[Switching to Thread 1 (LWP 1)]
	0xfeeeae55 in ___nanosleep () from /lib/libc.so.1
	(gdb) signal SIGHUP
	Continuing with signal SIGHUP.
	Receive signal: 1

可以看到，当程序暂停后，执行`signal SIGHUP`命令，gdb会发送信号给程序处理。

可以使用“`signal 0`”命令使程序重新运行，但不发送任何信号给进程。仍以上面程序为例：

	Program received signal SIGHUP, Hangup.
	0xfeeeae55 in ___nanosleep () from /lib/libc.so.1
	(gdb) signal 0
	Continuing with no signal.

可以看到，`SIGHUP`信号发生时，gdb停住了程序，但是由于执行了“`signal 0`”命令，所以程序重新运行后，并没有收到`SIGHUP`信号。

**使用`signal`命令和在shell环境使用`kill`命令给程序发送信号的区别在于：在shell环境使用`kill`命令给程序发送信号，gdb会根据当前的设置决定是否把信号发送给进程，而使用`signal`命令则直接把信号发给进程。**

在某些平台上（比如Linux）使用gdb调试程序，当有信号发生时，gdb在把信号丢给程序之前，可以通过`$_siginfo`变量读取一些额外的有关当前信号的信息，这些信息是`kernel`传给信号处理函数的。以上面程序为例:  

## 共享库

使用"`info sharedlibrary regex`"命令可以显示程序加载的共享链接库信息，其中`regex`可以是正则表达式，意为显示名字符合`regex`的共享链接库。如果没有`regex`，则列出所有的库。以上面程序为例:

## 脚本

当gdb启动时，会读取HOME目录和当前目录下的的配置文件，执行里面的命令。这个文件通常为“.gdbinit”。

这里给出了本文档中介绍过的，可以放在“.gdbinit”中的一些配置：

    # 打印STL容器中的内容
    python
    import sys
    sys.path.insert(0, "/home/xmj/project/gcc-trunk/libstdc++-v3/python")
    from libstdcxx.v6.printers import register_libstdcxx_printers
    register_libstdcxx_printers (None)
    end

    # 保存历史命令
    set history filename ~/.gdb_history
    set history save on

    # 退出时不显示提示信息
    set confirm off

    # 按照派生类型打印对象
    set print object on

    # 打印数组的索引下标
    set print array-indexes on

    # 每行打印一个结构体成员
    set print pretty on

## 源文件

directory ../ki/ 命令 或者启动时 `-d` 参数gdb -q a.out -d /search/code/some # 设置源文件查找路径
调试时，因为源文件已经移到`/home/ki`这个文件夹下了，所以gdb找不到源文件。使用`set substitute-path /home/nan /home/ki`命令设置源文件的查找目录后，gdb就可以正常地解析源代码了。  (TODO: zhuyafei 组件测试环境能不能这样调试代码)

## 图形化界面

启动gdb时指定“`-tui`”参数（例如：`gdb -tui program`），或者运行gdb过程中使用“`Crtl+X+A`”组合键，都可以进入图形化调试界面。以调试上面程序为例：  
使用gdb图形化调试界面时，可以使用“`layout asm`”命令显示汇编代码窗口。以调试上面程序为例：  
如果既想显示源代码，又想显示汇编代码，可以使用“`layout split`”命令：  
使用gdb图形化调试界面时，可以使用“`layout regs`”命令显示寄存器窗口。以调试上面程序为例：  

如果想查看浮点寄存器，可以使用“`tui reg float`”命令：  
“`tui reg system`”命令显示系统寄存器：  
想切换回显示通用寄存器内容，可以使用“`tui reg general`”命令：  

## 其他

gdb --args ./a.out a b c # 比如一键调试pytest用例
如果想在gdb中查看宏信息，可以使用`gcc -g3`进行编译：
如果想让gcc保留这些没有被使用的类型信息（猜测应该是sizeof在编译时即被替换成常数，所以gcc认为union Type是未使用的类型），则可以使用`gcc -g -fno-eliminate-unused-debug-types`进行编译：
另外，如果直接按回车键，会重复执行上一次的命令。
执行shell命令
	(gdb) shell ls
	(gdb) !ls
`set prompt (main gdb) ` # 设置命令行提示符, 区分不同的gdb
set env LD_PRELOAD=/lib/x86_64-linux-gnu/libpthread.so.0 # 设置环境变量

帮助信息

（1）`help`命令不加任何参数会得到命令的分类：
（2）当输入`help class`命令时，可以得到这个类别下所有命令的列表和命令功能：  
（3）也可以用`help command`命令得到某一个具体命令的用法：  
（4）用`apropos <regexp>`命令查找所有符合`regexp`正则表达式的命令信息：  比如apropos set 查找所有用法描述中包含set的命令

记录gdb的执行过程，但没有记录操作的命令, 
    (gdb) set logging file log.txt
	(gdb) set logging on
保存历史命令
	set history filename ~/.gdb_history
	set history save on
