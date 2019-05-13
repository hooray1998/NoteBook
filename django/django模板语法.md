### django语法



### 变量

句点符号

- 取键的值
- 取列表的元素  e.g. l.0 第一个元素
- 取对象的属性
- 取对象的方法(无参数) e.g. clas.name.upper

```django
<p>{{ person_dada.dream }}</p>  <!-- .方法的时候，注意当前的dream方法是没有参数的-->
<p>{{ person_list.2 }}</p>  <!--单个取值-->
<p>{{ person_list.1.name }}</p>
<!-- 那怎么让对象变成字符串呢？在index视图函数里里面再加上一个__str__内置方法-->
<!--__str__是对象字符串的改变-->
```


### 标签语法

```django
<h3>循环取值2:倒序</h3><hr>
{% for item in person_list reversed %}
    <!--序号从1开始-->
    <p>{{ forloop.counter }}-----》{{ item.name }},{{ item.age }}</p>
    <!--序号从0开始-->
	<p>{{ forloop.counter0 }}-----》{{ item.name }},{{ item.age }}</p>
	<!-- 序号倒序 -->
	<p>{{ forloop.revcounter }}-----》{{ item.name }},{{ item.age }}</p>
{% endfor %}

<h3>循环取值3：字典</h3><hr>
{% for k,v in d.items %}
    <p>{{ k }},{{ v}}</p>
{% endfor %}

列表长度为0或不存在时执行empty
{% for person in person_list %}
    <p>{{ person.name }}</p>

{% empty %}
    <p>sorry,no person here</p>
{% endfor %}
```


### if标签

当为True或非空或存在时进入if

```django
{% if i > 300 %}
    <p>大于{{ i }}</p>
{% elif i == 200  %}
    <p>等于{{ i }}</p>
{% else %}
    <p>小于{{ i }}</p>
{% endif %}
```

### with：使用一个简单地名字缓存一个复杂的变量，当你需要使用一个“昂贵的”方法（比如访问数据库）很多次的时候是非常有用的

```django
{% with total=business.employees.count %}
    {{ total }} employee{{ total|pluralize }}
{% endwith %}
<p>{{ person_list.2.name }}</p>
{% with name=person_list.2.name %}
    <p>{{ name }}</p>
{% endwith %}
```

### csrf_token：这个标签用于跨站请求伪造保护

提交数据的时候就会做安全机制，当你点击提交的时候会出现一个forbbiddon
的错误，就是用setting配置里的scrf做安全机制的，那么我们可以吧它给注释了
或者在form表单下面添加一个{% csrf_token %}

```django
<h3>scrf_token</h3><form action="/tag/" method="post">
    {% csrf_token %}
    <p><input type="text" name="haiyan"></p>
    <input type="submit">
</form>
```

### 模板语法之过滤器：语法 {{ obj|filter__name:param }}

1、default：如果一个变量是false或者为空，使用给定的默认值。否则，使用变量的值。例如：

```django
{{ li|default:"如果显示为空或False，显示该内容" }}
{{ value|length }}  str,list的长度
{{ value|filesizeformat }} 将值格式化为可读的文件尺寸,例如12KB,4.1MB等
{{ value|date:"Y-m-d" }}　如果 value=datetime.datetime.now()
{{ value|slice:"2:-1" }}  如果value="hello world",输出llo worl
{{ value|add:"2" }}  <!--如果 value 为 4,则会输出 6.-->
{{ value|capfirst }}  <!--如果value是test过滤后转为Test-->
{{ value|random }}		如果value是列表['a', 'b', 'c', 'd'], 可能输出的是 "b"

{{ value|dictsort:"name" }} 根据指定的key值对列表字典排序，并返回
{% for book in books|dictsort:"author.age" %}
    * {{ book.title }} ({{ book.author.name }})
{% endfor %}

<p>截断字符：{{ content|truncatechars:20 }}</p>
<p>截断单词：{{ content|truncatewords:4 }}</p>
如果content是“I am is haiyan,how are you asd df dfgfdgdg?
输出结果： 截断字符：I am is haiyan,ho...
输出结果 ：截断单词：I am is haiyan,how ...

{{ body|safe  }}  不希望这些HTML元素被转义

```

### 自定义标签 和 过滤器


1. 在settings中的INSTALLED_APPS配置当前app，不然django无法找到自定义的simple_tag.
2. 在app中创建templatetags模块(模块名只能是templatetags)
3. 在templatetags里面创建任意 .py 文件，
如：my_tags.py

```python
from django import template
from django.utils.safestring import mark_safe
 
register = template.Library()   #register的名字是固定的,不可改变

@register.filter   过滤器
def multi(x,y):
    return x*y

@register.simple_tag  标签
def multitag(x,y,z):
    return x*y*z

@register.simple_tag  标签
def my_input(id,arg):
　　 result = "<input type='text' id='%s' class='%s' />" %(id,arg,)
　　 return mark_safe(result)
```
```django
使用时加载
{% load my_tags %}　
# num=12
{{ num|multi:2 }} #24
{{ num|multi:"[22,333,4444]" }}   相当于复制了，吧[22,333,4444]乘了num遍

{% multitag 2 5 6 %} 参数不限,但不能放在if for语句中 
{% simple_tag_multi num 5 %}

自定义过滤器函数的参数只能两个，可以进行逻辑判断
自定义标签无参数限制，不能进行逻辑判断
{% if i|multi:5 > 1000 %}   <!-- 判断i*5>1000 -->
    <p>大于{{ i }}</p>
{% else %}
    <p>大于等于{{ i }}</p>
{% endif %}
```


### 个人笔记补充

```django
{% url 'alias' %}
{% comment %}# 这里的alias是urls.py中匹配url中设置的 {% endcomment %}

filter查询条件里的tui__id=1，表示为通过文章里的外键推荐位进行筛选。

里面分类名和分类ID是文章里的外键字段，
所以我们是通过代码{{ a.category.name }}和{{ a.category.id}}这样的方式进行调用的。
时间字段我们进行格式化，然后通过年月日的形式展现，
{{ a.created_time|date:"Y年m月d日" }}。

文章的浏览数，我们先通过show.views查询到当前浏览数，然后对这个数进行加1操作，
意思是每访问一次页面（视图函数），就进行加1操作。
然后再通过show.save()进行保存。
show.views = show.views + 1
show.save()


category = models.ForeignKey(Category, on_delete=models.DO_NOTHING, verbose_name='分类', blank=True, null=True)
# 使用外键关联分类表 与 分类 是一对多关系
tags = models.ManyToManyField(Tag, verbose_name='标签', blank=True)
# 使用外键关联标签表 与 标签 是多对多关系


pk就是主键
为啥使用pk, 哪来的

<div><b>上一篇：</b>
{% if next_blog %}
	<a href="show-{{ next_blog.pk }}.html" class="article-tag">{{ next_blog }}</a>
{% else %}
	没有了
{% endif %}
</div>

page = request.GET.get('page')  # 在URL中获取page的关键词，也就是当前页码数

herf中的? 表示后面要带参数
```
