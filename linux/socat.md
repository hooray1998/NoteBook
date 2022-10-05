# socat

> socat（英文全拼：Socket CAT）是 Linux 下的一个多功能的网络工具，其功能与有瑞士军刀之称的 Netcat 类似，可以看作是 Netcat 的加强版。socat 的主要特点就是在两个数据流之间建立通道，这些数据通道包含文件、管道、设备（终端或调制解调器等）、Socket、SSL、SOCKS4 客户端或代理 CONNECT。

**socat 支持众多协议和链接方式，如 IP、TCP、 UDP、IPv6、PIPE、EXEC、System、Open、Proxy、Openssl、Socket 等。支持广播和多播、抽象 Unix sockets、Linux tun/tap、GNU readline 和 PTY，并提供了分叉、记录和进程间通信的不同模式。**

**选项：**

    -V ：显示版本信息及特性。
    -h|-? ：显示帮助信息，包括选项（options）和地址（addresses）。
    -hh ：与 -h 类似，但会列出所有通用的地址选项名称。
    -hhh ：与 -hh 类似，但会列出所有可用的地址选项名称。
    -d[ddd] ：增加详细程度（最多使用 4 次，建议使用 2 次）。
    -D ：在循环之前分析文件描述符。
    -ly[facility] ：将日志输出到 syslog 系统日志（默认使用守护进程）。
    -lf<logfile> ：将日志输出到文件。
    -ls ：将日志输出到标准错误 stderr（如果没有指定其他日志，则默认使用 stderr）。
    -lm[facility] ：混合日志模式（初始化期间使用标准错误 stderr，之后使用系统日志 syslog）。
    -lp<progname> ：设置用于日志记录的程序名称。
    -lu ：使用微秒记录日志时间戳。
    -lh ：在日志信息中添加主机名称。
    -v ：详细的数据流量，文本格式。
    -x ：详细数据流量，十六进制格式。
    -b<size_t> ：设置数据缓冲区大小（默认 8192）。
    -s ：马虎模式（出错时继续执行）。
    -t<timeout> ：在关闭第二个频道之前等待几秒钟。
    -T<timeout> ：总的不活动（inactivity ）超时时间（以秒为单位）。
    -u ：单向模式（从左到右）。
    -U ：单向模式（从右到左）。
    -g ：不检查选项组。
    -L <lockfile> ：尝试获取锁，否则失败。
    -W <lockfile> ：尝试获取锁，否则等待。
    -4 ：如果未明确指定版本，则首选 IPv4。prefer IPv4 if version is not explicitly specified
    -6 ：如果未明确指定版本，则首选 IPv6。prefer IPv6 if version is not explicitly specified

**参数：address 参数用于提供数据通道的必要信息，不同类型的数据通道有不同的地址参数。下列列出几种模式：**

- STDIN STDOUT ：表示标准输入输出，可以就用一个横杠代替。
- /var/log/syslog ：也可以是任意路径，如果是相对路径要使用 ./，打开一个文件作为数据流。
- TCP:127.0.0.1:1080 ：建立一个 TCP 连接作为数据流，TCP 也可以替换为 UDP。
- TCP-LISTEN:12345 ：建立 TCP 监听端口，TCP 也可以替换为 UDP。
- EXEC:/bin/bash ：执行一个程序作为数据流。

## 文件操作

    socat - /var/www/html/flag.php 
    # 从相对路径读取, 使用相对路径记得要加上 ./
    socat - ./flag.php
    echo "This is Test" | socat - /tmp/hello.html

## 网络管理

    # 监听TCP端口并连接
    socat TCP-LISTEN:7000 -
    socat - TCP:localhost:7000

    # 监听UDP端口并连接
    socat UDP-LISTEN:7000 -
    socat - UDP:localhost:7000

    # 向TCP12345端口发送数据
    echo "test" | socat - tcp-connect:127.0.0.1:12345


## 端口转发


监听 192.168.1.252 网卡的 15672 端口，并将请求转发至 172.17.0.15 的 15672 端口。

socat  -d -d -lf /var/log/socat.log TCP4-LISTEN:15672,bind=192.168.1.252,reuseaddr,fork TCP4:172.17.0.15:15672

1. -d -d  前面两个连续 -d -d 代表调试信息的输出级别。
2. -lf /var/log/socat.log 指定输出信息的文件保存位置。 
3. TCP4-LISTEN:15672 在本地建立一个 TCP IPv4 协议的监听端口，也就是转发端口。这里是 15672，请根据实际情况改成你自己需要转发的端口。
4. bind 指定监听绑定的 IP 地址，不绑定的话将监听服务器上可用的全部 IP。
5. reuseaddr 绑定一个本地端口。
6. fork TCP4:172.17.0.15:15672 指的是要转发到的服务器 IP 和端口，这里是 172.17.0.15 的 15672 端口。

转发 UDP 和 TCP 类似，只要把 TCP4 改成 UDP4 就行了。


### NAT映射

在一个 NAT 网络环境中，也是可以通过 Socat 将内机器端口映射到公网上的。

在外部公网机器上执行

    socat tcp-listen:1234 tcp-listen:3389

在内部私网机器执行

    socat tcp:outerhost:1234 tcp:192.168.1.34:3389

这样，你外部机器上的 3389 就映射在内网 192.168.1.34 的 3389 端口上了。

## 文件传递

将文件 demo.tar.gz 使用 2000 端口从 192.168.1.252 传到 192.168.1.253,文件传输完毕后会自动退出。

在 192.168.1.252 上执行

    socat -u open:demo.tar.gz tcp-listen:2000,reuseaddr

在 192.168.1.253 上执行

    socat -u tcp:192.168.1.252:2000 open:demo.tar.gz,create

- -u 表输模式为单向，从左面参数到右参数。
- -U 表输模式为单向，从右面参数到左参数。

## 虚拟串口

创建两个可以相互通信的 Linux 虚拟串口

    socat -d -d PTY PTY
    2026/07/15 05:29:51 socat[1533] N PTY is /dev/pts/0
    2026/07/15 05:29:51 socat[1533] N PTY is /dev/pts/1
    2026/07/15 05:29:51 socat[1533] N starting data transfer loop with FDs [5,5] and [7,7]

当前产生的虚拟串口为 /dev/pts/0 和 /dev/pts/1，如果想要虚拟的串口一直有效，必须使 socat 一直运行。

可以给 address 字段添加额外参数

    socat -d -d pty,raw,echo=0 pty,raw,echo=0

接着就可以使用 minicom 打开串口终端进行测试

    minicom -D /dev/pts/0 -b 9600    # 打开一个串口终端
    minicom -D /dev/pts/1 -b 9600    # 打开另一个串口终端

在 minicom 命令中输入指令，在另一个 minicom 终端就能接收到了。

## Unix本地域套接字

监听一个 Unix Socket

    socat unix-listen:/tmp/unix.sock -

向本地 Unix Socket 发送数据

    echo "test" | socat - unix-connect:/tmp/unix.sock

监听本地 Unix Datagram Socket

    socat unix-recvfrom:/tmp/unix.dg.sock -

向本地 Unix Datagram Socket 发送数据

    echo "test" | socat - unix-sendto:/tmp/unix.dg.sock

## 其他功能

在目标机上弄一个 shell 代理

    socat TCP-LISTEN:12345 EXEC:/bin/bash
    # 其他机器连接执行shell
    socat - TCP:localhost:12345

本地的 UNIX 域套接字转成 TCP socket 供局域网内的机器使用（当有多个 TCP 连上来那就 fork 一个去连接 UNIX 域套接字）

    socat TCP-LISTEN:12345,reuseaddr,fork UNIX-CONNECT:/data/deCOREIDPS/unix.domain
