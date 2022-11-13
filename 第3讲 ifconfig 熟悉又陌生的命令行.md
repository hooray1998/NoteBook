`ifconfig`和`ip addr`的区别？ 这是有关net-tools和iproute2的历史故事
1. 显示所有的网卡， 每个网卡相当于是个门牌号

无类型域间选路（CIDR）
是一种新的划分网络地址的方式，  取消A/B/C的分类方法   
IP/`<mask-len>`
10.100.122.2/24  
1. 代表前面24位是网络号， 后面8位是主机号
2. 对应的广播地址的是，  10.100.122.255， 如果发送这个地址，  该网络里面的所有机器都会收到
3. 另一个是子网掩码，  255.255.255.0，  

私有IP地址
1. `10.x`
2. `172.16.x` - `172.31.x`
3. `192.168.0.0` - `192.168.255.255`


组播地址 -》 vxlan
```sh
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000                                 
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00                                                                   
    inet 127.0.0.1/8 scope host lo                                                                                          
       valid_lft forever preferred_lft forever                                                                              
    inet6 ::1/128 scope host                                                                                                
       valid_lft forever preferred_lft forever                                                                              
2: enp2s0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc fq_codel state DOWN group default qlen 1000                   
    link/ether d0:94:66:f3:13:8f brd ff:ff:ff:ff:ff:ff                                                                      
3: wlp3s0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default qlen 1000                        
    link/ether 5c:ea:1d:0e:12:b9 brd ff:ff:ff:ff:ff:ff                                                                      
    inet 192.168.2.26/24 brd 192.168.2.255 scope global dynamic noprefixroute wlp3s0                                        
       valid_lft 59094sec preferred_lft 59094sec                                                                            
    inet6 fe80::10e2:9a8e:7e7f:bc02/64 scope link noprefixroute                                                             
       valid_lft forever preferred_lft forever                                                                              
4: docker0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc noqueue state DOWN group default                             
    link/ether 02:42:4e:a3:4c:46 brd ff:ff:ff:ff:ff:ff                                                                      
    inet 172.17.0.1/16 brd 172.17.255.255 scope global docker0                                                              
       valid_lft forever preferred_lft forever
```

输出解析：
1. scope ：
	1. global ： 对外， 可以接收来自各个地方的包
	2. host   仅仅可以提供本机相互通信
			1. lo 全称是loopback，环回接口， 通常使用`127.0.0.1`  用于本机通信， 经过内核处理后直接返回， 不会再网络中出现
2. 第二行是MAC地址

Q: 既然MAC地址全球唯一， 为啥互联网通信不能直接用MAC地址？
MAC地址是全球唯一的， 但不具备定位功能， 相当于人的身份证号
一个网络包从一个地方传输到另一个地方， 除了要有确切的地址， 还需要有定位功能
MAC地址的唯一性设计是为了同一个网络的不同的网卡， 可以不同担心冲突； 从硬件角度， 保证不同的网卡有不同的标识
MAC仅有很有限的定位功能

`<BROADCAST,MULTICAST,UP,LOWER_UP>`  这个叫做`net_device flags`, 其中：

BROADCAST代表有广播地址， 支持广播
MULTICAST代表可以发送多播包
`LOWER_UP`代表`L1` 是启动的， 也就是网线是插着的

MTU 1500 代表最大传输单元MTU为1500， 这是以太网的默认值， 
MTU是二层的概念， 也就是要求MAC层的正文部分不允许超过1500字节， 正文里包括`IP` / TCP / HTTP, 如果放不下， 就分片

`qidsc pfifo_fast` 
1. qdisc shi queueing discipline, 中文叫规则接口
2. pfifo是先入先出， 不对数据包做任何的处理， 数据包进入时不做任何处理
3.  pfifo_fast 队列包括三个波段（band），每个波段中使用先入先出
	1. band 0 优先级最高
	2. land 如果高优先级的没处理完， 是不会处理其他低优先级的呢

网络数据包是通过服务类型（Type of Service, TOS）被分到三个波段里面的， TOS是IP头里面的一个字段， 代表当前报文是高优先级的还是低优先级的。


- [ ] [[ifconfig 输出详解]]
- [ ] [[ip addr 输出详解]]
