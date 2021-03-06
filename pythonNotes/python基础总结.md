# Python 面试准备fasd
[python面试](https://www.django.cn/article/show-19.html)

__str__是对象字符串的改变
可以将对象输出成字符串

1. 使用join(list)，拼接字符串
2. 使用解压赋值取出list中的连续的一串
3. 什么是元类: 
	- 在python中皆为对象，而元类即是用来创建类的”东西”。
	- 类也是元类的实例。
	- 而在python中，它们要么是类的实例，要么是元类的实例，除了type。type实际上是它自己的元类。
	- 元类主要的用途是用来创建API,比如django的ORM。
4. re中search和match的区别:
	- search和match都在re模块中.
	- match只匹配字符串的开始，如果字符串开始不符合正则表达式，则匹配失败，函数返回None。
	- search匹配整个字符串，直到找到一个匹配。
5. 深浅拷贝的区别:
	- **浅拷贝**没有拷贝子对象，所以原对象发生改变，其子对象也发生了改变。
	- 而**深拷贝**拷贝了子对象，原对象发生改变，其本身也不会改变。

6. Python 内存管理
	- python内部使用引用计数，来保持追踪内存中的对象
	- Python内部记录了对象有多少个引用，即引用计数
	- 当对象被创建时就创建了一个引用计数，当对象不再需要时，这个对象的引用计数为0时，它被垃圾回收。
	- 所有这些都是自动完成，不需要像C一样，人工干预，从而提高了程序员的效率和程序的健壮性。

7. filter
	- 用于过滤与函数func()不匹配的值

8. shuffle
```python
# random模块中的shuffle(洗牌函数)
import random
list = [1, 2, 3, 4]
random.shuffle(list)
print(list)
```

9. 装饰器

>装饰器是一个函数，接收一个函数返回另一个函数。用法如下：

```python
from functools import wraps
import time

def recordtime(func):
	"""
    Decorator that reports the execution time.
	"""
	@wraps(func)
	def www(*args, **kwargs):
		start = time.time()
		re = func(*args, **kwargs)
		end = time.time()
		print(func.__name__, end - start)
		return re
	return www

@recordtime
def foo(n):
	sum = 1
	for i in range(1, n):
		sum *= i

foo(1000)
	


```

10. 输入一个列表

```python
>>> x=input()
1 2 3 4
>>> xlist=x.split(" ")
>>> print(xlist)
['1', '2', '3', '4']
>>> xlist = [int(xlist[i]) for i in range(len(xlist))]
>>> print(xlist)
[1, 2, 3, 4]
```
