# Django学习之路
[学习链接](https://www.django.cn/course/show-35.html)


### 需求分析

### 数据库设计分析


### 创建项目

blog                #APP应用名和目录
│  admin.py        #对应应用后台管理配置文件。
│  apps.py         #对应应用的配置文件。
│  models.py       #数据模块，数据库设计就在此文件中设计。后面重点讲解
│  tests.py        #自动化测试模块，可在里面编写测试脚本自动化测试
│  views.py        #视图文件，用来执行响应代码的。你在浏览器所见所得都是它处理的。
│  __init__.py
│
├─migrations        #数据迁移、移植文目录，记录数据库操作记录，内容自动生成。
│  │  __init__.py
myblog               #项目配置目录
│  __init__.py       #初始化文件，一般情况下不用做任何修改。
│  settings.py        #项目配置文件，具体如何配置后面有介绍。
│  url.py             #项目URL设置文件，可理解为路由，可以控制你访问去处。
│  wsgi.py          #为Python服务器网关接口，是Python与WEB服务器之间的接口。
myblogvenv            #Pycharm创建的虚拟环境目录，和项目无关，不需要管它。
templates           #项目模板文件目录，用来存放模板文件
manage.py     #命令行工具，通过可以与项目与行交互。在终端输入python manege.py help，可以查看功能。


### Django2.0入门教程:Django常用命令

前面一章，我们使用过Django创建APP应用的命令，下面再向大家介绍一些Django常用的命令。

安装Django：	pip install django  指定版本 pip3 install django==2.0
新建项目：	django-admin.py startproject mysite
新建APP :	python manage.py startapp blog
启动：python manage.py runserver 8080
同步或者更改生成 数据库：
python manage.py makemigrations
python manage.py migrate
清空数据库：	python manage.py flush
创建管理员：	python manage.py createsuperuser
修改用户密码： python manage.py changepassword username
Django项目环境终端： python manage.py shell
这个命令和 直接运行 python 进入 shell 的区别是：你可以在这个 shell 里面调用当前项目的 models.py 中的 API，对于操作数据的测试非常方便。

更多关于Django的命令在终端输入：python manage.py 查看

###  创建数据库模型

Django是 **通过Model操作数据库** ，不管你数据库的类型是MySql或者Sqlite，Django它 **自动帮你生成相应数据库类型的SQL语句**，所以不需要关注SQL语句和类型，对数据的操作Django帮我们自动完成。只要 **回写Model** 就可以了！

django **根据代码中定义的类来自动生成数据库表**。
我们写的 **类表示数据库的表**，如果根据这个类创建的 **对象是数据库表里的一行数据**，对象.id 对象.value是 **每一行里的数据**。

基本的原则如下：
1. 每个模型在Django中的存在形式为一个Python类
2. 每个模型都是django.db.models.Model的子类
3. 模型里的 **每个类代表数据库中的一个表**
4. 模型的 **每个字段（属性）代表数据表的某一列**
5. Django将自动为你生成数据库访问API

之前我们在前面的数据库设计分析文章里已经分析过数据库的结构。
完成博客，我们需要存储六种数据：文章分类、文章、文章标签、幻灯图、推荐位、友情链接。
每种数据一个表。
[详细视图](./database_summary.html)

1. 分类表结构设计： 
	- 表名：Category、分类名：name
2. 标签表设计： 
	- 表名：Tag、标签名：name
3. 文章表结构设计： 
	- 表名：Article、标题：title、摘要：excerpt、分类：category、标签：tags、推荐位、内容：body、创建时间：created_time、作者：user、文章封面图片img
4. 幻灯图表结构设计： 
	- 表名：Banner、图片文本text_info、图片img、图片链接link_url、图片状态is_active。
5. 推荐位表结构设计： 
	- 表名：Tui、推荐位名name。
6. 友情链接表结构设计： 
	- 表名：Link、链接名name、链接网址linkurl。

其中：
文章和分类是一对多的关系，文章和标签是多对多的关系，文章和作者是一对多的关系，文章和推荐位是一对多关系(看自己的需求，也可以设计成多对多)。

##### 相关内容
[用Admin管理后台数据](https://www.django.cn/course/show-11.html)
[数据模型字段及属性详解](https://www.django.cn/course/show-12.html)
[多个数据模型间的关系](https://www.django.cn/course/show-13.html)
[元数据Meta选项详解](https://www.django.cn/course/show-14.html)

### 用Admin管理后台数据

1. 在settings.py 注册APP
2. 在blog/admin.py 中导入需要管理的数据库表(那些对应的类)


### URL与视图函数

```python
urlpatterns = [
    path(正则表达式, views视图函数，参数，别名),
]
括号里的参数说明：
1、一个正则表达式字符串
2、一个可调用对象，通常为一个视图函数或一个指定视图函数路径的字符串
3、可选的要传递给视图函数的默认参数（字典形式）
4、一个可选的name参数(别名)
```

### 体验django模板

存储在templates文件夹下
模板页面包含一些基础的HTML代码和一些特殊的语法
这些特殊的语法主要用于如何将数据动态的 **插入**HTML页面中。

### 数据库加载到网页

1、在models.py里定义 **数据模型**，以类的方式定义数据表的字段。
 **在数据库创建数据表时，数据表由模型定义的类**生成。

2、在视图views.py导入模型所定义的类，我们把这个类称之为 **数据表对象**，然后在 **视图函数**里使用Django的 **数据库操作方法**，实现数据库操作，从而获取到数据表里的数据。
	- 更多的数据库操作方法
	- [查  询](https://www.django.cn/course/show-18.html)
	- [增删改](https://www.django.cn/course/show-17.html)

3、视图函数获取到数据之后，将数据以字典、列表或对象（上下文context）的方式 **传递给HTML模板**，并由模板引擎接收和解析，最后生成相应的HTML网页，在浏览器里展现出来。

### 常用的模板使用方法

#### 模板包含

一个页面的结构大致如下：
重复的地方使用include填充
```django
{% include 'head.html' %}
<div>
	该页面的内容
</div>
{% include 'tail.html' %}
```

#### 模板继承

```django
{%extends "base.html" %}
{%block body%}
	{% comment %}覆盖了base中的block模块body{% endcomment %}
	<div>
		<ul>
			<h4> Blog教程目录： </h4>
			{% for list in list %}
			<li> {{list}} </li>
			{% endfor %}
		</ul>
	</div>
	{%block article %}
	{% comment %}等待被其他页面继承{% endcomment %}
	{%endblock%}
{%endblock%}
```
优点：
1. 可以快速实现不同的界面加载不同的CSS
2. 代码复用

**实际场景应该两种方法结合着使用，一些固定不改变的底层部件使用include，需要嵌套继承的使用block**


