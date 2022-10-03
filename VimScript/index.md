# 奇技淫巧

g;  / g, 跳转到上次编辑的地方
gi 跳转到上次插入的地方

有个 verbose 命令，可以查看某个配置是在哪个文件生效的。例如 verbose set tabstop

### 命令行模式

插入当前单词`Ctrl-r,Ctrl-w`
恢复到前十秒的状态`earlier 10s `
输入当前路径`:r !pwd`
设置不可见字符`:set list`


### 正常模式

格式化代码`ggVG=`
浏览片段`((, )), [[, ]], {,}`
多次插入重复内容`{number}i#<ESC>`
gd 跳转到局部定义
gf 跳转到文件


### 插入模式

ctrl + [ ，或者ctrl+c实现ESC功能
crtl+d ctrl+t 左右缩进
ctrl + x + i 行补齐
ctrl + x + f 文件路径补齐
