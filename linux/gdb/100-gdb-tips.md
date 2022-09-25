# 100-gdb-tips


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


## 打印 TODO

## 多进程、线程 TODO

## coredump文件

主动生成corefile

	(gdb) generate-core-file
	Saved corefile core.12955

## 汇编 TODO

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

## 信号 TODO

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
