# day-1.md


通常我们都把JavaScript代码放到<head>中
顺序执行


使用方法：
1. 使用<script></script>包含
2. 使用<script src="/path/to/xxx.js"></script>指明文件路径


### Chrome调试(F12，Console)

输入console.log(varName) 查看变量的值
alert() 有对话框


### 语法

注释用//, /* */
;结尾，{...}语句块

#### Number

不区分整数和浮点数
```javascript
0x1d //可以直接使用十六进制，= 29
123; // 整数123
0.456; // 浮点数0.456
1.2345e3; // 科学计数法表示1.2345x1000，等同于1234.5
-99; // 负数
NaN; // NaN表示Not a Number，当无法计算结果时用NaN表示
Infinity; // Infinity表示无限大，当数值超过了JavaScript的Number所能表示的最大值时，就表示为Infinity
```

#### 字符串

单引号或双引号包括的

#### 布尔值

true和false，小写
&&,||,!, >=, ==, === 产生的都是布尔值

##### 三个注意点

1. **坚持使用===**
==比较， **自动转换数据类型**,再比较，很多时候，会得到非常 **诡异的结果**；
===比较，不会自动转换数据类型，如果 **数据类型**不一致，返回false，如果一致，再比较。
由于JavaScript这个设计缺陷，不要使用==比较，始终 **坚持使用===比较**。

2. 另一个例外是NaN这个特殊的Number与所有其他值都不相等，包括它自己：
```JavaScript
NaN === NaN; // false
唯一能判断NaN的方法是通过isNaN()函数：
isNaN(NaN); // true
```

3. 最后要注意浮点数的相等比较：
```JavaScript
1 / 3 === (1 - 2 / 3); // false
这不是JavaScript的设计缺陷。浮点数在运算过程中会产生误差，因为计算机无法精确表示无限循环小数。要比较两个浮点数是否相等，只能计算它们之差的绝对值，看是否小于某个阈值：
Math.abs(1 / 3 - (1 - 2 / 3)) < 0.0000001; // true
```

- null表示空值
- undefined表示未定义
- 两者区分不大，经常用null，判断函数参数是否传递时用undefined


#### 数组

[1,3.4,false]可包含任意类型，或new Array(1,3.4,false)
```JavaScript
var arr = [1, 2, 3.14, 'Hello', null, true];
arr[0]; // 返回索引为0的元素，即1
arr[5]; // 返回索引为5的元素，即true
arr[6]; // 索引超出了范围，返回undefined
```

#### 对象

```JavaScript
var person = {
    name: 'Bob',
    age: 20,
    tags: ['js', 'web', 'mobile'],
    city: 'Beijing',
    hasCar: true,
    zipcode: null
};
//获取属性
person.name
person.zipcode
```


#### 变量

$_字母数字的组合。


#### strict 模式

第一行写上`'use strict';`
该模式变量定义必须有var


#### 字符串补充

单双引号混合用，转义字符\  , 
\x41 表示ASCII字符‘A’
\u4e2d\u6587 表示‘中文’
反引号用来表示多行字符串
```javascript
`这是一个
多行
字符串`
```

模板字符串

```javascript
var name = '小明';
var age = 20;
var message = '你好, ' + name + ', 你今年' + age + '岁了!';
//模板字符串, **反引号包围**
var message2 = `你好, ${name}, 你今年${age}岁了!`;
alert(message);
```

字符串的操作

```javascript
var s = 'hello world'
s.length
s.[0]
s.[100] //返回undefined，并不报错
s[0] = 'H' //不可改变，但不报错

s.toUpperCase()
s.toLowerCase()
s.indexOf('world') //若失败返回-1
s.substring(0,5) //返回0,1,2,3,4
s.substring(7)//返回7到结束
```

