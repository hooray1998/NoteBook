# 异或在算法中的应用

>抑或重要性质: 

**a^b^a = a**

> 同时满足交换律，结合律


### 交换两个数

```python
a, b = 3, 4
print('{:0>4b}'.format(a)) # 输出二进制
print('{:0>4b}'.format(b))
a = a^b
# a = 0111
b = b^a # b^(a^b) => a
# b = 0011
a = a^b # (a^b)^a => b
# a = 0100
```
>python中更简单的实现
`a, b = b, a`


```python
### 找出唯一的落单数
''' 用reduce函数简化 '''
from functools import reduce # 引入reduce函数
l1 = [1, 2, 3, 4, 5, 2, 4, 5, 1]
print(reduce(lambda x, y: x^y, l1, 0)) # 相邻依次异或，初始值从0开始，避免列表长度为1
# output 3

''' 迭代实现 '''
xor = 0
for i in l1:
    xor ^= i
print(xor)
```

### 找出仅有的两个落单数

```python
from functools import reduce
l = [1, 6, 2, 3, 4, 5, 4, 5, 6, 1]
xor = reduce(lambda x, y: x^y, l, 0)
xor_bin_str = '{:0>32b}'.format(xor) # 32位数最大支持几百万
index = (32-1) - xor_bin_str.rfind('1') # 从右往左找第一个1(因为两数不等，必有1)
l1 = [ i for i in l if (i>>index)%2 == 1 ] # 第index位为1的那组
l2 = [ i for i in l if (i>>index)%2 == 0 ] # 第index位为0的那组
print(reduce(lambda x, y: x^y, l1, 0))
print(reduce(lambda x, y: x^y, l2, 0))
```
