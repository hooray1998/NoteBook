# 新版的class

### 创建class
新的关键字class从ES6开始正式被引入到JavaScript中。class的目的就是让定义类更简单。

我们先回顾用函数实现Student的方法：
```javascript
function Student(name) {
    this.name = name;
}

Student.prototype.hello = function () {
    alert('Hello, ' + this.name + '!');
}
```

如果用新的class关键字来编写Student，可以这样写：
```javascript
class Student {
    constructor(name) {
        this.name = name;
    }
    hello() {
        alert('Hello, ' + this.name + '!');
    }
}
```
特点：
1. class的定义包含了构造函数constructor
2. 定义在原型对象上的没有function关键字的函数hello()

最后，创建一个Student对象代码和前面章节完全一样：
```javascript
var xiaoming = new Student('小明');
xiaoming.hello();
```


### class继承

直接通过extends来实现：
```javascript
class PrimaryStudent extends Student {
    constructor(name, grade) {
        super(name); // 记得用super调用父类的构造方法!
        this.grade = grade;
    }

    myGrade() {
        alert('I am at grade ' + this.grade);
    }
}
```

特点：
1. 也是通过class关键字实现的
2. extends则表示原型链对象来自Student。
3. 子类的构造函数参数可能不同
4. 通过super(name)来调用父类的构造函数，否则父类的name属性无法正常初始化。

PrimaryStudent已经自动获得了父类Student的hello方法，我们又在子类中定义了新的myGrade方法。

和之前的原型链没区别，只是为了简化代码。

有些浏览器可能不支持，可以通过Babel这个工具转换代码。

##### 练习
请利用class重新定义Cat，并让它从已有的Animal继承，然后新增一个方法say()，返回字符串'Hello, xxx!'：

```javascript
'use strict';

class Animal {
    constructor(name) {
        this.name = name;
    }
}
class Cat extends Animal{
    constructor(name){
        super(name);
}

say(){
return `Hello, ${this.name}!`;
}
}

// 测试:
var kitty = new Cat('Kitty');
var doraemon = new Cat('哆啦A梦');
if ((new Cat('x') instanceof Animal) && kitty && kitty.name === 'Kitty' && kitty.say && typeof kitty.say === 'function' && kitty.say() === 'Hello, Kitty!' && kitty.say === doraemon.say) {
    console.log('测试通过!');
} else {
    console.log('测试失败!');
}
```
