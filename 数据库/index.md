# MySQL插入中文汉字错误解决办法


## 解决办法

1.  修改数据库的编码

```sql
创建时指定
mysql>create database mydb character set utf8;
修改
alter database mydb character set utf8;
```

2. 首先检查数据库编码是否是utf-8，如果不是设置数据库字符集编码为utf-8；
```sql
show variables like '%char%';

set character_set_database=utf8;
```

3. 修改表字段编码方式为utf-8，SQL语句如下：

```sql
alter table `tablename` convert to character set utf8;//修改一张表的所有字段的编码格式
```
