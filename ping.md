ping是通过ICMP实现的，ICMP ECHO REQUEST和ICMP ECHO REPLY， 额外多了一些信息：
- 标识符：区分不同的类型
- 序号： 每次ping报文序号递增
- 请求的时间值，用于计算往返时间