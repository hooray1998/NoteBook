# Day-1


通常我们都把JavaScript代码放到<head>中
顺序执行


使用方法：
1. 使用<script></script>包含
2. 使用<script src="/path/to/xxx.js"></script>指明文件路径


### Chrome调试(F12，Console)


#### 输入输出
var height = parseFloat(prompt('请输入身高(m):'));
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

#### 数组补充

1. 可以直接对arr.length赋值，空缺的用undefined填充
2. 可以直接对越界的赋值，例如arr[100] = 1, 空缺的用undefined填充
3. indexOf()
4. slice() 对应string的subString(), 无参数就是返回一个copy
5. push('a',"B") 和pop(), pop()空了也不报错，返回undefined
6. unshift('A','b')和shift()头部添加删除
7. sort()默认方法排序
8. reverse()反转
9. splice(2,1,'A',"C") 从第2个删除一个，再添加AC，返回一个数组，包含删除量
10. concat()返回当前数组连接所有参数和数组后的新数组,e.g. arr.concat(1, 2, [3, 4]);
11. arr.join('-'), 返回字符串（如果元素不是字符串，先转化为字符串)
12. 通过[[],[]]嵌套可形成多维数组


#### 对象

```JavaScript
var person = {
    name: 'Bob',
    age: 20,
    tags: ['js', 'web', 'mobile'],
    city: 'Beijing',
    hasCar: true,
    zipcode: null
	'middle-shool':	'No.1 Middle School'
};
//TODO:获取属性
person.name;
person.zipcode;
person['age'];
person['middle-school'] ;
// Add && Delete
person.sex = 'boy';
person['sex']='boy';
delete person.sex;
delete person['sex'];
//Judge in this object
'name' in person;//true
'toString' in person;//true
persion.hasOwnProperty('name');//true
persion.hasOwnProperty('toString');//false
//traverse遍历
for(var k in list){ console.log(k+':'+list[k]);}
```

1. 属性是无序的。
2. 如果属性含有特殊字符，定义时必须用引号，使用时必须用 person['middle-school'] 这种形式。
3. {...}代表一个对象，最后一个属性不加逗号','
4. 访问未定义的属性返回undefined
5. 添加属性直接赋值即可，删除使用delete
6. 判断是否包含此属性使用hasOwnProperty()


#### 条件判断

和C语言同样的结构：
- if () { ... }else if{ ... } else { ... }
注意：
- JavaScript把null、undefined、0、NaN和空字符串''视为false，其他值一概视为true

#### 循环

for(;;)结构

```JavaScript
var x = 0;
var i;
for (i=1; i<=10000; i++) {
    x = x + i;
}
x;
```

for(var a in arr) 结构
```JavaScript
for (var key in o) {
    console.log(key); // 'name', 'age', 'city'
}
for (var key in o) {
    if (o.hasOwnProperty(key)) {// 过滤掉对象继承的属性
        console.log(key); // 'name', 'age', 'city'
    }
}
```
对Array遍历,遍历的是String类型的索引。因为Array每个元素的索引被视为对象的属性
```JavaScript
var a = ['A', 'B', 'C'];
for (var i in a) {
    console.log(i); // '0', '1', '2', ！！此处i是String，而不是Number
    console.log(a[i]); // 'A', 'B', 'C'
}
```

while 和 do while结构, 和C类似


#### Map 和 Set


**Map**
由于对象的属性只能是String，所以引入了Map()
初始化,使用二维数组或者空
```JavaScript
var m0 = new Map();
var m = new Map([['Michael', 95], ['Bob', 75], ['Tracy', 85]]);
m.set('Adam', 67); // 添加新的key-value
m.set('Bob', 59); //更新
m.has('Adam'); // 是否存在key 'Adam': true
m.get('Adam'); // 67
m.delete('Adam'); // 删除key 'Adam'
m.get('Adam'); // undefined
```

**Set**
```JavaScript
var s = new Set();
var s = new Set([1, 2, 3, 3, '3']);
s.add('3');
s.delete(3);
```


#### iterable类型
Array、Map和Set都是iterable类型

可以使用for of遍历
```JavaScript
var a = ['A', 'B', 'C'];
var s = new Set(['A', 'B', 'C']);
var m = new Map([[1, 'x'], [2, 'y'], [3, 'z']]);
for (var x of a) { // 遍历Array
    console.log(x);
}
for (var x of s) { // 遍历Set
    console.log(x);
}
for (var x of m) { // 遍历Map
    console.log(x[0] + '=' + x[1]);
}
```

几种遍历的方法。
1. for in ,输出name，不输出length
	- for ... in循环由于历史遗留问题，它遍历的实际上是对象的属性名称。一个Array数组实际上也是一个对象，它的每个元素的索引被视为一个属性。
	- 当我们手动给Array对象添加了额外的属性后，for ... in循环将带来意想不到的意外效果：

```JavaScript
var a = ['A', 'B', 'C'];
a.name = 'Hello';
for (var x in a) {
    console.log(x); // '0', '1', '2', 'name'
}
```

2. for of ,只输出Array的元素
```JavaScript
var a = ['A', 'B', 'C'];
a.name = 'Hello';
for (var x of a) {
    console.log(x); // 'A', 'B', 'C'
}
```

3. iterable内置的forEach方法，它接收一个函数，每次迭代就自动回调该函数。

```JavaScript
'use strict';
var a = ['A', 'B', 'C'];
a.forEach(function (element, index, array) {
    // element: 指向当前元素的值
    // index: 指向当前索引
    // array: 指向Array对象本身
    console.log(element + ', index = ' + index);
});
```


补充:
1. Set回调函数的前两个参数都是元素本身：
2. Map的回调函数参数依次为value、key和map本身：
3. 如果对某些参数不感兴趣，可以忽略它们。
	```JavaScript
	例如，只需要获得Array的element：
	var a = ['A', 'B', 'C'];
	a.forEach(function (element) {
		console.log(element);
	});
	```
