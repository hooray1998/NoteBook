> 背景： 服务端的机器配置一下还行， 比如数据中心的机器，但如果是笔记本电脑， 每天频繁的更换网络， 每次都要配置IP不得累死

这时候就需要DHCP （Dynamic Host Configuration Protocol，动态主机配置协议）这种协议， 用来动态分配IP地址， 这样才能上网

协议内容：

## discover
1. 因为没有IP， 也不知道DHCP server是谁， 所以发送discover报文
2. 原IP 全0， 目标IP全F 
3. 原MAC是自己， 目标IP全F
	1. MAC地址唯一是多么重要， 不然DHCP server会认为， 你都有IP了， 叫唤啥

## offer
4. 网络中的DHCP server收到之后会回复offer报文
5. 可能有多个DHCP server
6. 原IP是自己， 目标IP是全F 因为客户端的IP还没确定
7. 原MAC是自己， 目标MAC是客户端MAC
8. 报文中包含
	1. 分配的IP地址
	2. 子网掩码
	3. 网关地址
	4. 租期信息

## request
1. 客户端可能会收到多个offer报文， 然后选择其中一个， 一般是最早到达的那个
2. 然后回应request报文，  代表使用这个server分配的，包含信息：
	1. 准备租用的IP地址
	2. 用的是哪个DHCP server的
3. 原MAC是自己， 原IP是全0， 因为还没有最终确认
4. 目标IP是全F， 目标MAC是全F, 意思是， 不仅告诉选中的DHCP server我选你， 而且告诉其他server， 我没选你们， 把之前分配给我的信息撤销吧

## reply
1. 没选中的server， **收到request之后并不会立即撤销信息， 还需要等那个server的最终确认**
1. 选中的server， 收到该request报文之后， 回应reply， 包含：
	1. 分配的IP
	2. 网关地址
	3. 子网掩码
	4. 租期信息
2. 原IP、MAC是server自己的
3. 目标IP、MAC还是广播， 告知所有的server， 他已经和客户机双向选择了， 其他server放弃吧




## IP地址的收回和续租

1. 到期了， 如果不用了， 怎么收回？
2. 如果要续租， 需要在租期到达一半的收回进行续租
	1. 直接发给那个server request， 然后收到reply