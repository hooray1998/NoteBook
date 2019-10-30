# 操作DOM

由于HTML文档被浏览器解析后就是一棵DOM树，要改变HTML的结构，就需要通过JavaScript来操作DOM。


1. 更新：更新该DOM节点的内容，相当于更新了该DOM节点表示的HTML的内容；
2. 遍历：遍历该DOM节点下的子节点，以便进行进一步操作；
3. 添加：在该DOM节点下新增一个子节点，相当于动态增加了一个HTML节点；
4. 删除：将该节点从HTML中删除，相当于删掉了该DOM节点的内容以及它包含的所有子节点。

获取DOM节点:
方式一：
1. document.getElementById() ，返回唯一
2. document.getElementsByTagName() ，返回一组，适合嵌套定位
3. document.getElementsByClassName() ，返回一组，适合嵌套定位

```javascript
// 返回ID为'test'的节点：
var test = document.getElementById('test');
// 先定位ID为'test-table'的节点，再返回其内部所有tr节点：
var trs = document.getElementById('test-table').getElementsByTagName('tr');
// 先定位ID为'test-div'的节点，再返回其内部所有class包含red的节点：
var reds = document.getElementById('test-div').getElementsByClassName('red');
// 获取节点test下的所有直属子节点:
var cs = test.children;
// 获取节点test下第一个、最后一个子节点：
var first = test.firstElementChild;
var last = test.lastElementChild;
```

方式二：selector语法
1. querySelector()
2. querySelectorAll()

```javascript
// 通过querySelector获取ID为q1的节点：
var q1 = document.querySelector('#q1');
// 通过querySelectorAll获取q1节点内的符合条件的所有节点：
var ps = q1.querySelectorAll('div.highlighted > p');
```
注意：低版本的IE小于8不支持querySelector和querySelectorAll。IE8仅有限支持。


1. DOM节点实际上是Node，Node包括Element、Comment、CDATA_SECTION等很多种，以及根节点Document类型
2. 我们这里DOM节点是指Element，绝大多数时候我们只关心Element，也就是实际控制页面结构的Node


```html
<!-- HTML结构 -->
<div id="test-div">
<div class="c-red">
    <p id="test-p">JavaScript</p>
    <p>Java</p>
  </div>
  <div class="c-red c-green">
    <p>Python</p>
    <p>Ruby</p>
    <p>Swift</p>
  </div>
  <div class="c-green">
    <p>Scheme</p>
    <p>Haskell</p>
  </div>
</div>
```
请选择出指定条件的节点：
```javascript
'use strict';
// 选择<p>JavaScript</p>:
var js = document.getElementById('test-p');
var js = document.querySelector('#test-p');
// 选择<p>Python</p>,<p>Ruby</p>,<p>Swift</p>:
var arr = document.getElementsByClassName('c-red')[1].children;
var arr = document.querySelectorAll('.c-red.c-green > p');
// 选择<p>Haskell</p>:
var haskell = document.getElementsByClassName('c-green').children[1];
var haskell = document.querySelectorAll('.c-green > p')[4];
```


## 更新DOM


可以直接修改节点的文本，方法有两种：

1. 修改innerHTML属性，这个方式非常强大，不但可以修改一个DOM节点的文本内容，还可以直接通过HTML片段修改DOM节点内部的子树：(要注意编码)
	```javascript
	// 获取<p id="p-id">...</p>
	var p = document.getElementById('p-id');
	// 设置文本为abc:
	p.innerHTML = 'ABC'; // <p id="p-id">ABC</p>
	// 设置HTML:
	p.innerHTML = 'ABC <span style="color:red">RED</span> XYZ';
	// <p>...</p>的内部结构已修改
	```

2. 修改innerText或textContent属性，保证无法设置任何HTML标签：(自动对字符串进行HTML编码)
	```javascript
	// 获取<p id="p-id">...</p>
	var p = document.getElementById('p-id');
	// 设置文本:
	p.innerText = '<script>alert("Hi")</script>';
	// HTML被自动编码，无法设置一个<script>节点:
	// <p id="p-id">&lt;script&gt;alert("Hi")&lt;/script&gt;</p>
	```
	- 读取属性时
		1. innerText不返回隐藏元素的文本
		2. textContent返回所有文本(注意IE9不支持)

3. 修改CSS
	```javascript
	// 获取<p id="p-id">...</p>
	var p = document.getElementById('p-id');
	// 设置CSS:
	p.style.color = '#ff0000';
	p.style.fontSize = '20px';
	p.style.paddingTop = '2em';
	```

## 插入DOM

如果这个DOM节点是空的，例如，<div></div>，那么，直接使用innerHTML = '<span>child</span>'就可以修改DOM节点的内容，相当于“插入”了新的DOM节点。
1. 如果DOM节点是空的，使用innerHTML
	- 例如，<div></div>，那么，直接使用innerHTML = '<span>child</span>'就行
2. 非空
	1. appendChild
	2. insertBefore


### appendChild
- `Q: 把<p id="js">JavaScript</p>添加到<div id="list">的最后一项：`
- `A: **先从原先的位置删除，再插入到新的位置。**`

```javascript
var
    js = document.getElementById('js'),
    list = document.getElementById('list');
list.appendChild(js);
```

从零创建一个新的节点，然后插入到指定位置：
```javascript
var
    list = document.getElementById('list'),
    haskell = document.createElement('p');
haskell.id = 'haskell';
haskell.innerText = 'Haskell';
list.appendChild(haskell);
```

还可以创建style节点，然后把它添加到`<head>`节点的末尾，这样就动态地给文档添加了新的CSS定义：
```javascript
var d = document.createElement('style');
d.setAttribute('type', 'text/css');
d.innerHTML = 'p { color: red }';
document.getElementsByTagName('head')[0].appendChild(d);
```

### insertBefore

如果我们要把子节点插入到指定的位置怎么办？
- 使用parentElement.insertBefore(newElement, referenceElement);
- 子节点会插入到referenceElement之前。

还是以上面的HTML为例，假定我们要把Haskell插入到Python之前：

```javascript
var
    list = document.getElementById('list'),
    ref = document.getElementById('python'),
    haskell = document.createElement('p');
haskell.id = 'haskell';
haskell.innerText = 'Haskell';
list.insertBefore(haskell, ref);
```
**可见，使用insertBefore重点是要拿到一个“参考子节点”的引用。很多时候，需要循环一个父节点的所有子节点，可以通过迭代children属性实现：**
```javascript
var
    i, c,
    list = document.getElementById('list');
for (i = 0; i < list.children.length; i++) {
    c = list.children[i]; // 拿到第i个子节点
}
```
练习

对于一个已有的HTML结构：
```javascript
<!-- HTML结构 -->
<ol id="test-list">
    <li class="lang">Scheme</li>
    <li class="lang">JavaScript</li>
    <li class="lang">Python</li>
    <li class="lang">Ruby</li>
    <li class="lang">Haskell</li>
</ol>
按字符串顺序重新排序DOM节点：

'use strict';
// sort list:
var list = document.getElementById('test-list'),li = list.children; 
for(var i = 0; i<li.length; i++ ){ 
	for(var j = 0; j<li.length-i-1; j++){
		if(li[j].innerText >= li[j+1].innerText){
			list.insertBefore(li[j+1],li[j]);
		}
	}
}
```


## 删除DOM


要删除一个节点，首先要获得该节点本身以及它的父节点，然后，调用父节点的removeChild把自己删掉：

```javascript
// 拿到待删除节点:
var self = document.getElementById('to-be-removed');
// 拿到父节点:
var parent = self.parentElement;
// 删除:
var removed = parent.removeChild(self);
removed === self; // true
```
注意到删除后的节点虽然不在文档树中了，但其实它还在内存中，可以随时再次被添加到别的位置。

当你遍历一个父节点的子节点并进行删除操作时，要注意，children属性是一个只读属性，并且它在子节点变化时会实时更新。
当删除一个时，长度立刻减一

练习
```html
<!-- HTML结构 -->
<ul id="test-list">
    <li>JavaScript</li>
    <li>Swift</li>
    <li>HTML</li>
    <li>ANSI C</li>
    <li>CSS</li>
    <li>DirectX</li>
</ul>
```
把与Web开发技术不相关的节点删掉：

```javascript
'use strict';
// TODO
// 1.获取id为test-list的元素
var parent = document.querySelector('#test-list');
// 2.由于parent.children是HTMLCollection对象，需要转换为数组
var children = Array.from(parent.children);
// 3.利用数组的forEach函数
children.forEach((element)=>{
  if(element.innerText=='Swift' || element.innerText=='ANSI C'||element.innerText=='DirectX'){
    parent.removeChild(element); 
  }
});
```
