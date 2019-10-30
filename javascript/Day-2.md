# Day-2 函数

[目录](.)
1. Day-2 函数
	1. 函数定义
	1. 函数使用
		1. 类型检查
		1. arguments关键字
		1. rest参数
			1. 注意return
	1. 变量作用域
		1. 全局作用域
		1. 名字空间
		1. 局部作用域
		1. 常量
		1. 解构赋值
			1. 特殊报错场合
		1. 使用场景
	1. 对象的方法
		1. apply
		1. call(), 与之类似的方法
		1. 装饰器
	1. 高阶函数
	1. 闭包


## 函数定义

1. 方式一
	```javascript
	function abs(x, a, b) {
		if (x >= 0) {
			return x;
		} else {
			return -x;
		}
	}
	```
2. 方式二
	```javascript
	var abs = function (x, a, b) {
		if (x >= 0) {
			return x;
		} else {
			return -x;
		}
	};
	```

## 函数使用

多传值少传值都不报错
- abs(-9, 'haha', 'hehe', null); // 返回9
- abs(); // 返回NaN, 函数中x的类型是undefined

### 类型检查
要避免收到undefined，可以对参数进行检查：
```javascript
function abs(x) {
    if (typeof x !== 'number') { //类型检查
        throw 'Not a number'; //抛出异常
    }
    if (x >= 0) {
        return x;
    } else {
        return -x;
    }
}
```

### arguments关键字

1. 类似Array类型
2. 存储所有的参数
3. arguments[0]
4. arguments.length
5. 使函数可以不定义参数
6. 应用一：（参数为两个时，传给a，c）
	```javascript
	function foo(a, b, c) {
		if (arguments.length === 2) {
			// 实际拿到的参数是a和b，c为undefined
			c = b; // 把b赋给c
			b = null; // b变为默认值
		}
		// ...
	}
	```

### rest参数

rest只能写在最后，前面用...标识
```javascript
function foo(a, b, ...rest) {
    console.log('a = ' + a);
    console.log('b = ' + b);
    console.log(rest);
}

foo(1, 2, 3, 4, 5);
// 结果:
// a = 1
// b = 2
// Array [ 3, 4, 5 ]

foo(1);
// 结果:
// a = 1
// b = undefined
// Array []
```

#### 注意return


此函数会报错，因为return后会自动加入分号；
```javascript
function max(a, b){
    if (a > b) {
        return
                a;
    } else {
        return
                b;
    }
}
```

## 变量作用域

内部可以访问外部变量，但反过来不行。
内部如果跟外部重名，则屏蔽外部变量。


变量提升
JavaScript的函数定义有个特点，它会先扫描整个函数体的语句，把所有申明的变量“提升”到函数顶部：


```JavaScript
'use strict';

function foo() {
    var x = 'Hello, ' + y;
    console.log(x);
    var y = 'Bob';
}

foo();
```
1. 虽然是strict模式，但语句var x = 'Hello, ' + y;并不报错，原因是变量y在稍后申明了。
2. 但是console.log显示Hello, undefined，说明变量y的值为undefined。
3. 这正是因为JavaScript引擎自动提升了变量y的声明，但不会提升变量y的赋值。

对于上述foo()函数，JavaScript引擎看到的代码相当于：
```JavaScript
function foo() {
    var y; // 提升变量y的申明，此时y为undefined
    var x = 'Hello, ' + y;
    console.log(x);
    y = 'Bob';
}
```

### 全局作用域

不在任何函数内定义的变量和函数都具有全局作用域。
都被绑定到全局对象window的一个属性

```javascript
alert(name);
alert(window.name);
foo(); // 直接调用foo()
window.foo(); // 通过window.foo()调用
```

### 名字空间

减少冲突
```javascript
// 唯一的全局变量MYAPP:
var MYAPP = {};

// 其他变量:
MYAPP.name = 'myapp';
MYAPP.version = 1.0;

// 其他函数:
MYAPP.foo = function () {
    return 'foo';
};
```


### 局部作用域
由于JavaScript的变量作用域实际上是函数内部，我们在for循环等语句块中是无法定义具有局部作用域的变量的：

for循环外仍然可以使用i
```javascript
'use strict';

function foo() {
    for (var i=0; i<100; i++) {
        //
    }
    i += 100; // 仍然可以引用变量i
}
```

使用let可以申明一个块级作用域的变量：
```javascript
'use strict';

function foo() {
    var sum = 0;
    for (let i=0; i<100; i++) {
        sum += i;
    }
    // SyntaxError:
    i += 1;//!!!!!!!!!!ERROR!!!!!!!!1
}
```

### 常量

`const PI=3.14`
后面的赋值语句不报错，但是没效果，修改不成功

### 解构赋值


层次对应
```JavaScript
var arr=[1,2,3];
var [x,y,z] = arr;
let [x, [y, z]] = ['hello', ['JavaScript', 'ES6']];
```

从对象中取出属性，层次对应
```javascript
// name, age, passport分别被赋值为对应属性:
console.log('name = ' + name + ', age = ' + age + ', passport = ' + passport);
'use strict';

var person = {
    name: '小明',
    age: 20,
    gender: 'male',
    passport: 'G-12345678',
    school: 'No.4 middle school'
};
var {name, age, passport} = person;
// name, age, passport分别被赋值为对应属性:
console.log('name = ' + name + ', age = ' + age + ', passport = ' + passport);
```

对象嵌套对应 =>下面的address不是变量
```javascript
var person = {
    name: '小明',
    age: 20,
    gender: 'male',
    passport: 'G-12345678',
    school: 'No.4 middle school',
    address: {
        city: 'Beijing',
        street: 'No.1 Road',
        zipcode: '100001'
    }
};
var {name, address: {city, zip}} = person;
name; // '小明'
city; // 'Beijing'
zip; // undefined, 因为属性名是zipcode而不是zip
// 注意: address不是变量，而是为了让city和zip获得嵌套的address对象的属性:
address; // Uncaught ReferenceError: address is not defined, 他不是变量
```

事先使用默认值，找不到就用默认值

```javascript
var person = {
    name: '小明',
    age: 20,
    gender: 'male',
    passport: 'G-12345678'
};

// 如果person对象没有single属性，默认赋值为true:
var {name, single=true} = person;
name; // '小明'
single; // true
```

#### 特殊报错场合


有些时候，如果变量已经被声明了，再次赋值的时候，正确的写法也会报语法错误：
```JavaScript
// 声明变量:
var x, y;
// 解构赋值:
{x, y} = { name: '小明', x: 100, y: 200};
// 语法错误: Uncaught SyntaxError: Unexpected token =
这是因为JavaScript引擎把{开头的语句当作了块处理，于是=不再合法。解决方法是用小括号括起来：
({x, y} = { name: '小明', x: 100, y: 200});
```

### 使用场景


1. 交换变量 `[x, y] = [y, x]`
2. 快速获取当前页面的域名和路径：` var {hostname:domain, pathname:path} = location;`


```JavaScript
如果一个函数接收一个对象作为参数，那么，可以使用解构直接把对象的属性绑定到变量中。例如，下面的函数可以快速创建一个Date对象：
function buildDate({year, month, day, hour=0, minute=0, second=0}) {
    return new Date(year + '-' + month + '-' + day + ' ' + hour + ':' + minute + ':' + second);
}
```

```javascript
它的方便之处在于传入的对象只需要year、month和day这三个属性：
buildDate({ year: 2017, month: 1, day: 1 });
// Sun Jan 01 2017 00:00:00 GMT+0800 (CST)
也可以传入hour、minute和second属性：
buildDate({ year: 2017, month: 1, day: 1, hour: 20, minute: 15 });
// Sun Jan 01 2017 20:15:00 GMT+0800 (CST)
```

## 对象的方法

简单使用
```javascript
var xiaoming = {
    name: '小明',
    birth: 1990,
    age: function () {
        var y = new Date().getFullYear();
        return y - this.birth; //会随着调用的对象而改变，指向调用的当前的对象,所以容易出错
    }
};

xiaoming.age; // function xiaoming.age()
xiaoming.age(); // 今年调用是25,明年调用就变成26了
```

this指向window，strict模式下指向undefined
```javascript
function getAge() {
    var y = new Date().getFullYear();
    return y - this.birth;
}

var xiaoming = {
    name: '小明',
    birth: 1990,
    age: getAge
};

xiaoming.age(); // 25, 正常结果
getAge(); // NaN
```

第一种情况下，如下方式也是报错的,为了让this正确指向，只能使用obj.xxx()的形式调用，也就是xiaoming.age()
```javascript
var fn = xiaoming.age;
fn();//NaN。  strict模式下会报错Uncaught TypeError: Cannot read property 'birth' of undefined
```

重构，以便能更有条例

Error
因为this所在的函数外层不是一个对象,this指针只在age方法的函数内指向xiaoming，在函数内部定义的函数，this又指向undefined了！（在非strict模式下，它重新指向全局对象window！）
```javascript
'use strict';

var xiaoming = {
    name: '小明',
    birth: 1990,
    age: function () {
        function getAgeFromBirth() {
            var y = new Date().getFullYear();
            return y - this.birth;
        }
        return getAgeFromBirth();
    }
};

xiaoming.age(); // Uncaught TypeError: Cannot read property 'birth' of undefined
```

修复方法：用that暂存,这样还能在方法中定义其他函数
```javascript
'use strict';

var xiaoming = {
    name: '小明',
    birth: 1990,
    age: function () {
        var that = this; // 在方法内部一开始就捕获this
        function getAgeFromBirth() {
            var y = new Date().getFullYear();
            return y - that.birth; // 用that而不是this
        }
        return getAgeFromBirth();
    }
};

xiaoming.age(); // 25
```

### apply

1. 虽然在一个独立的函数调用中，根据是否是strict模式，this指向undefined或window
2. 不过，我们还是可以通过apply()控制this的指向的！
3. apply()接收两个参数，第一个参数就是需要绑定的this变量，第二个参数是Array，表示函数本身的参数。

用apply修复getAge()调用：

```JavaScript
function getAge() {
    var y = new Date().getFullYear();
    return y - this.birth;
}

var xiaoming = {
    name: '小明',
    birth: 1990,
    age: getAge
};

getAge();//NaN或报错
xiaoming.age(); // 25
getAge.apply(xiaoming, []); // 25, this指向xiaoming, 参数为空。 成功执行
```

### call(), 与之类似的方法

- apply()把参数打包成Array再传入；
- call()把参数按顺序传入。

比如调用Math.max(3, 5, 4)，分别用apply()和call()实现如下：
```JavaScript
Math.max.apply(null, [3, 5, 4]); // 5
Math.max.call(null, 3, 5, 4); // 5
```
对普通函数调用，我们通常把this绑定为null。


### 装饰器

- 利用apply()，我们还可以动态改变函数的行为。
- JavaScript的所有对象都是动态的，即使内置的函数，我们也可以重新指向新的函数。

现在假定我们想统计一下代码一共调用了多少次parseInt()，最佳方案是用我们自己的函数替换掉默认的parseInt()：
```javascript
'use strict';

var count = 0;
var oldParseInt = parseInt; // 保存原函数

window.parseInt = function () {
    count += 1;
    return oldParseInt.apply(null, arguments); // 调用原函数
};
// 测试:
parseInt('10');
parseInt('20');
parseInt('30');
console.log('count = ' + count); // 3
```
### 匿名函数

(function (x) {
    return x * x;
})(3); // 9
理论上讲，创建一个匿名函数并立刻执行可以这么写：

function (x) { return x * x } (3);
但是由于JavaScript语法解析的问题，会报SyntaxError错误，因此需要用括号把整个函数定义括起来：

(function (x) { return x * x }) (3);
通常，一个立即执行的匿名函数可以把函数体拆开，一般这么写：

(function (x) {
    return x * x;
})(3);

## 高阶函数
能将函数作为参数, 该函数参数就是回调函数。
[源文件](./高阶函数.md)

### 闭包

特点：
函数作为返回值。
返回的函数并没有立刻执行，而是直到调用了f()才执行。
**相关参数和变量**都保存在返回的函数中。
每次调用都会返回一个 **新的函数**，即使传入相同的参数。


**高阶函数除了可以接受函数作为参数外，还可以把函数作为结果值返回。**

我们来实现一个对Array的求和。通常情况下，求和的函数是这样定义的：
```javascript
function sum(arr) {
    return arr.reduce(function (x, y) {
        return x + y;
    });
}

sum([1, 2, 3, 4, 5]); // 15
```

不立刻求和，根据需要再计算，返回求和的函数即可！
```javascript
function lazy_sum(arr) {
    var sum = function () {
        return arr.reduce(function (x, y) {
            return x + y;
        });
    }
    return sum;
}
var f = lazy_sum([1, 2, 3, 4, 5]); // function sum()返回的并不是求和结果，而是求和函数：
f(); // 15
```
内部函数sum可以引用外部函数lazy_sum的参数和局部变量，当lazy_sum返回函数sum时， **相关参数和变量**都保存在返回的函数中
请再注意一点，当我们调用lazy_sum()时，每次调用都会返回一个 **新的函数**，即使传入相同的参数：



另一个需要注意的问题是，我们来看一个例子：

```javascript
function count() {
    var arr = [];
    for (var i=1; i<=3; i++) {
        arr.push(function () {
            return i * i;
        });
    }
    return arr;
}

var results = count();
var f1 = results[0];
var f2 = results[1];
var f3 = results[2];
```
在上面的例子中，每次循环，都创建了一个新的函数，然后，把创建的3个函数都添加到一个Array中返回了。

你可能认为调用f1()，f2()和f3()结果应该是1，4，9，但实际结果是：

f1(); // 16
f2(); // 16
f3(); // 16
全部都是16！原因就在于返回的函数引用了变量i，但它并非立刻执行。等到3个函数都返回时，它们所引用的变量i已经变成了4，因此最终结果为16。

**返回闭包时牢记的一点就是：返回函数不要引用任何循环变量，或者后续会发生变化的变量。**

如果一定要引用循环变量怎么办？方法是再创建一个函数，用该函数的参数绑定循环变量当前的值，无论该循环变量后续如何更改，已绑定到函数参数的值不变：

```javascript
function count() {
    var arr = [];
    for (var i=1; i<=3; i++) {
        arr.push((function (n) {
            return function () {
                return n * n;
            }
        })(i));//创建一个匿名函数并立刻执行”的语法：
    }
    return arr;
}

var results = count();
var f1 = results[0];
var f2 = results[1];
var f3 = results[2];

f1(); // 1
f2(); // 4
f3(); // 9
```
难道闭包就是为了返回一个函数然后延迟执行吗？
比如创建一个私有变量，
在没有class机制，只有函数的语言里，借助闭包，同样可以封装一个私有变量。我们用JavaScript创建一个计数器：

```javascript
'use strict';

function create_counter(initial) {
    var x = initial || 0;
    return {
        inc: function () {
            x += 1;
            return x;
        }
    }
}
它用起来像这样：

var c1 = create_counter();
c1.inc(); // 1
c1.inc(); // 2
c1.inc(); // 3

var c2 = create_counter(10);
c2.inc(); // 11
c2.inc(); // 12
c2.inc(); // 13
```
1. 在返回的对象中，实现了一个闭包
2. 该闭包携带了局部变量x，
3. 从外部代码根本无法访问到变量x。
4. 闭包就是携带状态的函数，并且它的状态可以完全对外隐藏起来。
5. 闭包还可以把多参数的函数变成单参数的函数。

例如，要计算xy可以用Math.pow(x, y)函数，不过考虑到经常计算x2或x3，我们可以利用闭包创建新的函数pow2和pow3：
	```javascript
	'use strict';

	function make_pow(n) {
		return function (x) {
			return Math.pow(x, n);
		}
	}
	// 创建两个新函数:
	var pow2 = make_pow(2);
	var pow3 = make_pow(3);

	console.log(pow2(5)); // 25
	console.log(pow3(7)); // 343

	```

##### 脑洞大开
很久很久以前，有个叫阿隆佐·邱奇的帅哥，发现只需要用函数，就可以用计算机实现运算，而不需要0、1、2、3这些数字和+、-、*、/这些符号。
JavaScript支持函数，所以可以用JavaScript用函数来写这些计算。来试试：

```javascript
'use strict';

// 定义数字0:
var zero = function (f) {
    return function (x) {
        return x;
    }
};

// 定义数字1:
var one = function (f) {
    return function (x) {
        return f(x);
    }
};

// 定义加法:
function add(n, m) {
    return function (f) {
        return function (x) {
            return m(f)(n(f)(x));
        }
    }
}
// 计算数字2 = 1 + 1:
var two = add(one, one);

// 计算数字3 = 1 + 2:
var three = add(one, two);

// 计算数字5 = 2 + 3:
var five = add(two, three);

// 你说它是3就是3，你说它是5就是5，你怎么证明？

// 呵呵，看这里:

// 给3传一个函数,会打印3次:
(three(function () {
    console.log('print 3 times');
}))();

// 给5传一个函数,会打印5次:
(five(function () {
    console.log('print 5 times');
}))();

// 继续接着玩一会...
```

### 箭头函数

ES6标准新增了一种新的函数：Arrow Function（箭头函数）。

为什么叫Arrow Function？因为它的定义用的就是一个箭头：

x => x * x
上面的箭头函数相当于：

function (x) {
    return x * x;
}
在继续学习箭头函数之前，请测试你的浏览器是否支持ES6的Arrow Function：

'use strict';
var fn = x => x * x;

console.log('你的浏览器支持ES6的Arrow Function!');
 Run
你的浏览器支持ES6的Arrow Function!
箭头函数相当于匿名函数，并且简化了函数定义。箭头函数有两种格式，一种像上面的，只包含一个表达式，连{ ... }和return都省略掉了。还有一种可以包含多条语句，这时候就不能省略{ ... }和return：

x => {
    if (x > 0) {
        return x * x;
    }
    else {
        return - x * x;
    }
}
如果参数不是一个，就需要用括号()括起来：

// 两个参数:
(x, y) => x * x + y * y

// 无参数:
() => 3.14

// 可变参数:
(x, y, ...rest) => {
    var i, sum = x + y;
    for (i=0; i<rest.length; i++) {
        sum += rest[i];
    }
    return sum;
}
如果要返回一个对象，就要注意，如果是单表达式，这么写的话会报错：

// SyntaxError:
x => { foo: x }
因为和函数体的{ ... }有语法冲突，所以要改为：

// ok:
x => ({ foo: x })
this
箭头函数看上去是匿名函数的一种简写，但实际上，箭头函数和匿名函数有个明显的区别：箭头函数内部的this是词法作用域，由上下文确定。

回顾前面的例子，由于JavaScript函数对this绑定的错误处理，下面的例子无法得到预期结果：

var obj = {
    birth: 1990,
    getAge: function () {
        var b = this.birth; // 1990
        var fn = function () {
            return new Date().getFullYear() - this.birth; // this指向window或undefined
        };
        return fn();
    }
};
现在，箭头函数完全修复了this的指向，this总是指向词法作用域，也就是外层调用者obj：

var obj = {
    birth: 1990,
    getAge: function () {
        var b = this.birth; // 1990
        var fn = () => new Date().getFullYear() - this.birth; // this指向obj对象
        return fn();
    }
};
obj.getAge(); // 25
如果使用箭头函数，以前的那种hack写法：

var that = this;
就不再需要了。

由于this在箭头函数中已经按照词法作用域绑定了，所以，用call()或者apply()调用箭头函数时，无法对this进行绑定，即传入的第一个参数被忽略：

```javascript
var obj = {
    birth: 1990,
    getAge: function (year) {
        var b = this.birth; // 1990
        var fn = (y) => y - this.birth; // this.birth仍是1990
        return fn.call({birth:2000}, year);
    }
};
console.log(obj.getAge(2015)); // 25
```



### generator

generator（生成器）是ES6标准引入的新的数据类型。一个generator看上去像一个函数，但可以返回多次。

我们先复习函数的概念。一个函数是一段完整的代码，调用一个函数就是传入参数，然后返回结果：

function foo(x) {
    return x + x;
}

var r = foo(1); // 调用foo函数
函数在执行过程中，如果没有遇到return语句（函数末尾如果没有return，就是隐含的return undefined;），控制权无法交回被调用的代码。

generator跟函数很像，定义如下：

function* foo(x) {
    yield x + 1;
    yield x + 2;
    return x + 3;
}
generator和函数不同的是，generator由function*定义（注意多出的*号），并且，除了return语句，还可以用yield返回多次。

大多数同学立刻就晕了，generator就是能够返回多次的“函数”？返回多次有啥用？

还是举个栗子吧。

我们以一个著名的斐波那契数列为例，它由0，1开头：

0 1 1 2 3 5 8 13 21 34 ...
要编写一个产生斐波那契数列的函数，可以这么写：

function fib(max) {
    var
        t,
        a = 0,
        b = 1,
        arr = [0, 1];
    while (arr.length < max) {
        [a, b] = [b, a + b];
        arr.push(b);
    }
    return arr;
}

// 测试:
fib(5); // [0, 1, 1, 2, 3]
fib(10); // [0, 1, 1, 2, 3, 5, 8, 13, 21, 34]
函数只能返回一次，所以必须返回一个Array。但是，如果换成generator，就可以一次返回一个数，不断返回多次。用generator改写如下：

function* fib(max) {
    var
        t,
        a = 0,
        b = 1,
        n = 0;
    while (n < max) {
        yield a;
        [a, b] = [b, a + b];
        n ++;
    }
    return;
}
直接调用试试：

fib(5); // fib {[[GeneratorStatus]]: "suspended", [[GeneratorReceiver]]: Window}
直接调用一个generator和调用函数不一样，fib(5)仅仅是创建了一个generator对象，还没有去执行它。

调用generator对象有两个方法，一是不断地调用generator对象的next()方法：

var f = fib(5);
f.next(); // {value: 0, done: false}
f.next(); // {value: 1, done: false}
f.next(); // {value: 1, done: false}
f.next(); // {value: 2, done: false}
f.next(); // {value: 3, done: false}
f.next(); // {value: undefined, done: true}
next()方法会执行generator的代码，然后，每次遇到yield x;就返回一个对象{value: x, done: true/false}，然后“暂停”。返回的value就是yield的返回值，done表示这个generator是否已经执行结束了。如果done为true，则value就是return的返回值。

当执行到done为true时，这个generator对象就已经全部执行完毕，不要再继续调用next()了。

第二个方法是直接用for ... of循环迭代generator对象，这种方式不需要我们自己判断done：

'use strict'

function* fib(max) {
    var
        t,
        a = 0,
        b = 1,
        n = 0;
    while (n < max) {
        yield a;
        [a, b] = [b, a + b];
        n ++;
    }
    return;
}
for (var x of fib(10)) {
    console.log(x); // 依次输出0, 1, 1, 2, 3, ...
}

 Run
generator和普通函数相比，有什么用？

因为generator可以在执行过程中多次返回，所以它看上去就像一个可以记住执行状态的函数，利用这一点，写一个generator就可以实现需要用面向对象才能实现的功能。例如，用一个对象来保存状态，得这么写：

var fib = {
    a: 0,
    b: 1,
    n: 0,
    max: 5,
    next: function () {
        var
            r = this.a,
            t = this.a + this.b;
        this.a = this.b;
        this.b = t;
        if (this.n < this.max) {
            this.n ++;
            return r;
        } else {
            return undefined;
        }
    }
};
用对象的属性来保存状态，相当繁琐。

generator还有另一个巨大的好处，就是把异步回调代码变成“同步”代码。这个好处要等到后面学了AJAX以后才能体会到。

没有generator之前的黑暗时代，用AJAX时需要这么写代码：

ajax('http://url-1', data1, function (err, result) {
    if (err) {
        return handle(err);
    }
    ajax('http://url-2', data2, function (err, result) {
        if (err) {
            return handle(err);
        }
        ajax('http://url-3', data3, function (err, result) {
            if (err) {
                return handle(err);
            }
            return success(result);
        });
    });
});
回调越多，代码越难看。

有了generator的美好时代，用AJAX时可以这么写：

try {
    r1 = yield ajax('http://url-1', data1);
    r2 = yield ajax('http://url-2', data2);
    r3 = yield ajax('http://url-3', data3);
    success(r3);
}
catch (err) {
    handle(err);
}

看上去是同步的代码，实际执行是异步的。
