# index

AJAX = Asynchronous JavaScript and XML（异步的 JavaScript 和 XML）。

AJAX 不是新的编程语言，而是一种使用现有标准的新方法。

AJAX 最大的优点是在不重新加载整个页面的情况下，可以与服务器交换数据并更新部分网页内容。
传统的网页（不使用 AJAX）如果需要更新内容，必需重载整个网页面。

有很多使用 AJAX 的应用程序案例：新浪微博、Google 地图、开心网等等。

./updateText.html


open(method,url,async)	规定请求的类型、URL 以及是否异步处理请求。
	1. method：请求的类型；GET 或 POST
	2. url：文件在服务器上的位置
	3. async：true（异步）或 false（同步）

send(string) 将请求发送到服务器。
	- string：仅用于 POST 请求

GET 还是 POST？
1. 与 POST 相比，GET 更简单也更快，并且在大部分情况下都能用。
2. 然而，在以下情况中，请使用 POST 请求：
	1. 无法使用缓存文件（更新服务器上的文件或数据库）
	2. 向服务器发送大量数据（POST 没有数据量限制）
	3. 发送包含未知字符的用户输入时，POST 比 GET 更稳定也更可靠

1. 避免有缓存，不更新
	xmlhttp.open("GET","/try/ajax/demo_get.php?t=" + Math.random(),true);
	xmlhttp.send();
2. 发送数据
	xmlhttp.open("GET","/try/ajax/demo_get2.php?fname=Henry&lname=Ford",true);
	xmlhttp.send();
3. POST附带数据
	xmlhttp.open("POST","/try/ajax/demo_post2.php",true);
	xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	xmlhttp.send("fname=Henry&lname=Ford");

setRequestHeader(header,value)	向请求添加 HTTP 头。
1. header: 规定头的名称
2. value: 规定头的值


### 获得来自服务器的响应
使用 XMLHttpRequest 对象的 responseText 或 responseXML 属性。

### AJAX - onreadystatechange 事件
onreadystatechange 事件
当请求被发送到服务器时，我们需要执行一些基于响应的任务。
每当 readyState 改变时，就会触发 onreadystatechange 事件。
readyState 属性存有 XMLHttpRequest 的状态信息。

下面是 XMLHttpRequest 对象的三个重要的属性：
onreadystatechange	存储函数（或函数名），每当 readyState 属性改变时，就会调用该函数。
readyState	存有 XMLHttpRequest 的状态。从 0 到 4 发生变化。
	0: 请求未初始化
	1: 服务器连接已建立
	2: 请求已接收
	3: 请求处理中
	4: 请求已完成，且响应已就绪
status	200: "OK"
	404: 未找到页面

### AJAX读取数据库，XML

### xmlhttp.readyState的值及解释：

0：请求未初始化（还没有调用 open()）。
1：请求已经建立，但是还没有发送（还没有调用 send()）。
2：请求已发送，正在处理中（通常现在可以从响应中获取内容头）。
3：请求在处理中；通常响应中已有部分数据可用了，但是服务器还没有完成响应的生成。
4：响应已完成；您可以获取并使用服务器的响应了。
xmlhttp.status的值及解释：
100——客户必须继续发出请求
101——客户要求服务器根据请求转换HTTP协议版本
200——交易成功
201——提示知道新文件的URL
202——接受和处理、但处理未完成
203——返回信息不确定或不完整
204——请求收到，但返回信息为空
205——服务器完成了请求，用户代理必须复位当前已经浏览过的文件
206——服务器已经完成了部分用户的GET请求
300——请求的资源可在多处得到
301——删除请求数据
302——在其他地址发现了请求数据
303——建议客户访问其他URL或访问方式
304——客户端已经执行了GET，但文件未变化
305——请求的资源必须从服务器指定的地址得到
306——前一版本HTTP中使用的代码，现行版本中不再使用
307——申明请求的资源临时性删除
400——错误请求，如语法错误
401——请求授权失败
402——保留有效ChargeTo头响应
403——请求不允许
404——没有发现文件、查询或URl
405——用户在Request-Line字段定义的方法不允许
406——根据用户发送的Accept拖，请求资源不可访问
407——类似401，用户必须首先在代理服务器上得到授权
408——客户端没有在用户指定的饿时间内完成请求
409——对当前资源状态，请求不能完成
410——服务器上不再有此资源且无进一步的参考地址
411——服务器拒绝用户定义的Content-Length属性请求
412——一个或多个请求头字段在当前请求中错误
413——请求的资源大于服务器允许的大小
414——请求的资源URL长于服务器允许的长度
415——请求资源不支持请求项目格式
416——请求中包含Range请求头字段，在当前请求资源范围内没有range指示值，请求也不包含If-Range请求头字段
417——服务器不满足请求Expect头字段指定的期望值，如果是代理服务器，可能是下一级服务器不能满足请求
合起来
500——服务器产生内部错误
501——服务器不支持请求的函数
502——服务器暂时不可用，有时是为了防止发生系统过载
503——服务器过载或暂停维修
504——关口过载，服务器使用另一个关口或服务来响应用户，等待时间设定值较长
505——服务器不支持或拒绝支请求头中指定的HTTP版本
1xx:信息响应类，表示接收到请求并且继续处理
2xx:处理成功响应类，表示动作被成功接收、理解和接受
3xx:重定向响应类，为了完成指定的动作，必须接受进一步处理
4xx:客户端错误，客户请求包含语法错误或者是不能正确执行
5xx:服务端错误，服务器不能正确执行一个正确的请求
xmlhttp.readyState==4 && xmlhttp.status==200的解释：请求完成并且成功返回
