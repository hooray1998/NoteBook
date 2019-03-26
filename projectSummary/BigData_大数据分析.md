## 大数据项目

- (HDFS)
	- Hadoop分布式文件系统
- Hive
	- 是基于 Hadoop 的一个数据仓库工具
	- 可以将结构化的数据映射为一张数据库表
	- 并提供 HQL(Hive SQL)查询功能
	- 底层数据是存储在 HDFS 上
	- Hive的本质是将 SQL 语句转换为 MapReduce 任务运行


### 基于Hadoop、Hive的游戏日志分析


>原始数据格式为

>0-用户id、1-操作系统、2-系统编号、3-上线时间、4-下线时间、5-累计在线时长

#### 需求详解

1. TotalInfo.java累计用户、累计启动
mapreduce代码思路：累计用户为用户唯一ID不重复出现的次数，在map端聚合之后计算所有的reduce次数即可。累计启动在每个reduce的迭代器里累加1即可求得。

2. AverageInfo.java人均时长、次均时长
mapreduce代码思路：id聚合后在每个迭代器里累加每次记录的在线时长。最后除以人数和启动次数即可。

3. DataPartion.java按照日期进行分区，每日登陆总数
mapreduce代码思路：通过日期觉得Partition的返回值。从而实现按日期分区。

4. EverydayNewAndOld.java每一天的新老用户数量。
mapreduce代码思路：按照id聚合后，循环判断出用户第一次登陆的日期，则用户在那一天为新用户，相应的日期数组加一。

5. ActiveRate.java留存率（两日,三日,七日）
mapreduce代码思路：例如三日留存率：按照id聚合后，判断用户是否在那三天有过登陆记录，有则总用户加一。若该用户在那三天都有登陆记录则count加一，最后做除法即可。

6. Top20Info.java 每个用户的在线时间、次数、首登汇总
mapreduce代码思路：通过id聚合。循环累加用户的在线时间，在迭代器里取第一次的登陆时间为首登时间。循环的次数为上线次数。

7. Top20.java取出前20（在线时间、登录次数、首次登录）
mapreduce代码思路：通过把上述信息连成的字符串作为key值，Sort函数中通过split取出相关信息并比较，决定返回值，从而实现排序。

8. Authority.java统计各用户在哪天登陆了
mapreduce代码思路：通过id聚合，循环判读该用户登陆的天数，并付给相应的变量false/true值。循环之后将true对应的天数输出。

9. OnlineDay.java某天登录的人数（传参数）
mapreduce代码思路：通过上述文件，在ruduce中判断该天是否有登录，决定是否累加登录人数。

10. BeforeX.java传参，得前几天登录的人数
mapreduce代码思路：id聚合后，通过传入的参数判断该用户该日期之前是否有登录。从而累加相应变量。

11. OnlineHour.java七天各准点在线人数
mapreduce代码思路：对初始数据进行处理。通过日期以及时间对上线时间和下线时间的跨度进行判断。得出它在哪些连续的整点有在线记录。从而将相关数组进行累加。

12. LogInCount.java统计某天的某个时间段的上线人数，时间段分为 上午(6-12)，下午(12-18)，晚(18-24)，凌晨(0-6) 四个时间段，求出各时间段的比重
mapreduce代码思路：通过读取相应日期的文件，通过id聚合，判断该用户在四个时段中哪个时段有上线记录，从而将相应数组加一。

13. LogOffCount.java统计某天的某个时间段的下线人数，时间段分为 上午(6-12)，下午(12-18)，晚(18-24)，凌晨(0-6) 四个时间段，求出各时间段的比重
mapreduce代码思路：通过读取相应日期的文件，通过id聚合，判断该用户在四个时段中哪个时段有下线记录，从而将相应数组加一。

14. OSCount.jave统计IOS、Android使用人数,各版本登录次数和平均时长
mapreduce代码思路：将系统作为key值，在reduce中迭代即可求的两大系统的人数。通过将系统和版本号的连接成的字串作为key值，即可在reduce中求的各版本的累计时间和登陆次数。

Hive代码实现过程
```sql
1.累计用户
select COUNT(DISTINCT user_id) from user_test2;  33266
2。累计启动次数
select COUNT(user_id) from user_test2;333886

3.每个用户的id、在线时间、次数   ffff5256-5b6e-44f9-a33c-09d10f5cb81c  248560  11
drop table if exists id_test1;
create table if not exists id_test1 as
select user_id as id,SUM(cast(time as int)) as time,count(user_id) as counts from user_test2
group by user_id;

4.每个用户（在线时间、登录次数、）前20 排序
select * from id_test1 order by time desc,counts desc limit 20;

6.每天登录的人数
select COUNT(DISTINCT user_id) from user_test2 where logout like '2017-01-01T%';

7.前三天登录的人数
select COUNT(DISTINCT user_id)from user_test2 where logout like '2017-01-01T%' or logout like '2017-01-02T%' or logout like '2017-01-03T%';

8.系统比率（iOS，Android）
drop table if exists system_test;
create table if not exists system_test as
select system as system,count(1) as total from user_test2
group as system;
// rate:  系统总数／总次数（利用前面的结果）
```

### 基于Hadoop、Hive的电商交易日志分析

### 基于Hadoop、Hive的玩家游戏表现分析
