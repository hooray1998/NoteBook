# LSOF

lsof打开的文件可以是：

   普通文件
   目录
   网络文件系统的文件
   字符或设备文件
   (函数)共享库
   管道，命名管道
   符号链接
   网络文件（例如：NFS file、网络socket，unix域名socket）
   还有其它类型的文件，等等


   -a 列出打开文件存在的进程
   -c<进程名> 列出指定进程所打开的文件
   -g 列出GID号进程详情
   -d<文件号> 列出占用该文件号的进程
   +d<目录> 列出目录下被打开的文件
   +D<目录> 递归列出目录下被打开的文件
   -n<目录> 列出使用NFS的文件
   -i<条件> 列出符合条件的进程。（4、6、协议、:端口、 @ip ）
   -p<进程号> 列出指定进程号所打开的文件
   -u 列出UID号进程详情

实例2：查找某个文件相关的进程
$lsof /bin/bash
COMMAND     PID USER  FD   TYPE DEVICE SIZE/OFF    NODE NAME
mysqld_sa  2169 root txt    REG  253,0   938736 4587562 /bin/bash
ksmtuned   2334 root txt    REG  253,0   938736 4587562 /bin/bash
bash      20121 root txt    REG  253,0   938736 4587562 /bin/bash
实例3：列出某个用户打开的文件信息
$lsof -u username

-u 选项，u是user的缩写
实例4：列出某个程序进程所打开的文件信息
$lsof -c mysql
-c 选项将会列出所有以mysql这个进程开头的程序的文件，其实你也可以写成 lsof | grep mysql, 但是第一种方法明显比第二种方法要少打几个字符；

实例5：列出某个用户以及某个进程所打开的文件信息
$lsof  -u test -c mysql
实例6：通过某个进程号显示该进程打开的文件
$lsof -p 11968
实例7：列出所有的网络连接
$lsof -i
实例8：列出所有tcp 网络连接信息
$lsof -i tcp

$lsof -n -i tcp
COMMAND     PID  USER   FD   TYPE  DEVICE SIZE/OFF NODE NAME
svnserve  11552 weber    3u  IPv4 3799399      0t0  TCP *:svn (LISTEN)
redis-ser 25501 weber    4u  IPv4  113150      0t0  TCP 127.0.0.1:6379 (LISTEN)
实例9：列出谁在使用某个端口
$lsof -i :3306

