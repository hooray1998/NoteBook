正经的方法
https://yq.aliyun.com/articles/45035
***ffsdfasdfasdfasdsd***

普通的dump 和load
init文件修改
pip install pymysql


error： 
raise ImproperlyConfigured('mysqlclient 1.3.13 or newer is required; you have %s.' % Database.__version__)
django.core.exceptions.ImproperlyConfigured: mysqlclient 1.3.13 or newer is required; you have 0.9.3.

修改base。py文件

/home/itt/PycharmProjects/myblog/myblogvenv/lib/python3.6/site-packages/django/db/backends/mysql/base.py


error 2:

django.db.utils.InternalError: (1049, "Unknown database 'mysite_db'")

进入mysql创建db

error 3:

File "/home/itt/PycharmProjects/myblog/myblogvenv/lib/python3.6/site-packages/django/db/backends/mysql/operations.py", line 146, in last_executed_query
    query = query.decode(errors='replace')
AttributeError: 'str' object has no attribute 'decode'

修改decode为encode
✗ cd -
~/PycharmProjects/myblog/myblogvenv/lib/python3.6/site-packages/django/db/backends/mysql
(myblogvenv) ➜  mysql git:(master) ✗ vim operations.py 


error 4:

File "/home/itt/PycharmProjects/myblog/myblogvenv/lib/python3.6/site-packages/pymysql/err.py", line 109, in raise_mysql_exception
    raise errorclass(errno, errval)
django.db.utils.ProgrammingError: Problem installing fixture '/home/itt/PycharmProjects/myblog/data.json': Could not load contenttypes.ContentType(pk=1): (1146, "Table 'mysite_db.django_content_type' doesn't exist")


error 5:
 python manage.py dumpdata --exclude=contenttypes --exclude=auth.Permission > initial_data.json
CommandError: Unable to serialize database: (1146, "Table 'mysite_db.auth_group' doesn't exist")


makemigrations
migrate


error 6:

 File "/home/itt/PycharmProjects/myblog/myblogvenv/lib/python3.6/site-packages/pymysql/err.py", line 109, in raise_mysql_exception
    raise errorclass(errno, errval)
django.db.utils.IntegrityError: Problem installing fixture '/home/itt/PycharmProjects/myblog/data.json': Could not load contenttypes.ContentType(pk=7): (1062, "Duplicate entry 'blog-article' for key 'django_content_type_app_label_model_76bd3d3b_uniq'")



python manage.py dumpdata --exclude=contenttypes --exclude=auth.Permission > initial_data.json
(myblogvenv) ➜  myblog git:(master) ✗ python manage.py loaddata initial_data.json
Installed 1 object(s) from 1 fixture(s)

runserver 数据库全空

error 7:

django.db.utils.DataError: Problem installing fixture '/home/itt/PycharmProjects/myblog/initial_data.json': Could not load blog.Category(pk=2): (1406, "Data too long for column 'img' at row 1")
