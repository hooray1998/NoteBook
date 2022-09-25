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

[打印尾调用堆栈帧信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-debug-entry-values.md)


## 断点

## 观察点

## Catchpoint

## 打印

## 多进程、线程

## coredump文件

## 汇编

## 改变程序的执行

## 信号

## 共享库

## 脚本

## 源文件

## 图形化界面

## 其他


