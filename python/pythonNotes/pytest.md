# pytest

<!-- 使用faker创建假的实例 -->
pip install pytest

```sh
pytest -h # 查看帮助
usage: pytest [options] [file_or_dir] [file_or_dir] [...]

pytest # 测试当前目录和所有子目录的test文件(test_开头或_test结尾)


```

## 定位测试入口

```python
@pytest.mark.finished
def test_func1():
    pass
```

### 1. 文件名::函数名

pytest test.py::func1

### 2. 模糊匹配(expreassion -k)

测试包含关键字的函数或类
-k 'test_method or test_other'
-k 'not test_method'

### 3. 标记(marker -m)

example:
-m "mark1 and mark2"、 -m "mark1 and not mark2"、-m "mark1 or mark2"


## 总结

测试文件应该命名为test_.py或_test.py
测试方法和函数应该被命名为test_。
测试类应该被命名为Test

### 结果类型

PASSED (.)：测试成功。
FAILED (F):测试失败(或XPASS + strict)。
SKIPPED (s): 测试被跳过。 你可以使用@pytest.mark.skip()或 pytest.mark.skipif()修饰器告诉pytest跳过测试
xfail (x)：预期测试失败。@pytest.mark.xfail()
XPASS (X)：测试不应该通过。
ERROR (E)：错误


--durations=3 统计最慢的3个测试函数

### traceback 设置

-l 显示本地变量
--tb=auto 默认格式，首尾为long，其他为short
--tb=long 详细的traceback信息格式化形式
--tb=native 标准库格式化形式, 没有额外信息
--tb=short 更短的traceback格式
--tb=line 每个错误一行
--tb=no 无traceback
--full-trace 最详细的格式

### 输出捕捉(capture)

默认捕捉方式为file descriptor (FD)级捕捉。捕捉所有到操作系统的1,2输出。
syslevel级捕捉只捕捉python的sys.stdout和sys.stderr。

--capture=no, -s  # 取消捕捉，print可以直接输出
--capture=sys     # replace sys.stdout/stderr with in-mem files
--capture=fd(默认)# also point filedescriptors 1 and 2 to temp file


#### 捕获异常
```python
def test_raises():
    # 报错TypeError，因为有with所以不终止
    with pytest.raises(TypeError) as e:
        a = time.sleep('1')
    # 获取异常信息
    exec_msg = e.value.args[0]
    with pytest.raises(AssertionError) as e:
        # 异常信息 不一致 ，报错AssertionError
        assert exec_msg == 'hello world'
    # 获取异常信息
    exec_msg = e.value.args[0]
    assert 'assert' in exec_msg

```
### 执行失败动作

-x, -exitfirst, --maxfail=1 # 失败后停止执行
--maxfail=n # 失败n次后停止执行

--lf, --last-failed  # 执行上次失败的测试
--ff, --failed-first # 先执行上次失败的，在执行成功的
--nf, --new-first    # 根据文件修改时间，先运行新的测试


### 跳过测试

如果测试的比较少，打正向标记比较好
如果不测试的比较少，打反向标记（跳过）

测试结果中s代表跳过
```python
@pytest.mark.skip(reason='out-of-date api')
def test_connect():
    pass

# 根据条件跳过
@pytest.mark.skipif(conn.__version__ < '0.2.0',
                    reason='not supported until v0.2.0')
def test_api():
    pass
```
### 预见的错误

使用mark.xfail()标记。
如果真的错误，输出x xfailed
如果顺利通过了,输出X xpassed
```python
@pytest.mark.xfail(gen.__version__ < '0.2.0',
                    reason='not supported until v0.2.0')
def test_api():
    assert 1 == 2
```

### 参数化

使用mark.parametrize()来遍历不同的参数
```python
# 例子1
@pytest.mark.parametrize('passwd',
                      ['123456',
                       'abcdefdfs',
                       'as52345fasdf4'])
def test_passwd_length(passwd):
    assert len(passwd) >= 8

# 例子2
@pytest.mark.parametrize('user, passwd',
                         [('jack', 'abcdefgh'),
                          ('tom', 'a123456a')])
def test_passwd_md5(user, passwd):
    db = {
        'jack': 'e8dc4081b13434b45189a720b77b6818',
        'tom': '1702a132e769a623c1adb78353fc9503'
    }
    import hashlib
    assert hashlib.md5(passwd.encode()).hexdigest() == db[user]
```

输出的时候想单独查看每个例子的结果
1. -v参数
2. 为每个例子加一个id
```python
@pytest.mark.parametrize('user, passwd',
                         [pytest.param('jack', 'abcdefgh', id='User<Jack>'),
                          pytest.param('tom', 'a123456a', id='User<Tom>')])
```

## 固件

Fixture 是一些函数，pytest会在执行函数之前（或之后）加载运行他们。
最常见的应用就是数据库的初始化连接和最后的操作。

@pytest.fixture()定义

