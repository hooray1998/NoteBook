# Git用法整理


### 基本用法

初始化一个git仓库
`git init`
显示git提交日志
git log				 # catch commit log
显示当前git仓库状态
git status
显示工作区和暂存区或最近的一次提交的不同
git diff [filename]
记录每一次的版本变动
git reflog

# 丢弃工作区的修改,恢复到暂存区或最近的一次提交
git checkout -- *
git checkout -- <filename> 


# 丢弃工作区和暂存区的所有改动
git reset --hard HEAD # 重置到最新的一次提交, 丢弃未提交的所有内容.
git reset --hard HEAD^  # 再上一个
git reset --hard HEAD^^
git reset --hard versionNumber # 只输入前几位即可

`只要是版本变动都会清空工作区和暂存区的内容`


### 推送到远程仓库

创建ssh秘钥
ssh-keygen -t rsa -C "hooray1998@foxmail.com"
增加远程仓库，起名origin
git remote add origin git@github.com:hooray1998/linuxConfig.git
初次push需要加-u参数
git push -u origin master
后续push不需要
git push origin master


### 克隆远程仓库
git clone git@github.com:hooray1998/QtCoding.git
git clone git@github.com:GoldenPlan666/loveyue.git


### 使用分支

查看分支
git branch 
创建分支
git branch <name>     # make this branch
git branch -d <name>   # del this branch
切换分支
git checkout <name>  # change to this branch
创建并切换
git checkout -b <name>  #  make and change to this branch
删除分支
git branch -D <name>  # delete a branch unmerged

快进(Fast-forward)合并到当前分支
git merge <name>  # merge <name>branch to current branch
快进(no-Fast-forward)合并到当前分支,方便看到合并的痕迹
git merge  --no-ff -m "合并说明"  develop


暂时储藏
git stash    # save the current workspace uncomplish
显示所有储藏
git stash list   # show the list of you stash before
恢复最新的储藏
git stash apply [stash@{N}]
恢复并删除
git stash pop
删除储藏
git stash drop [stash@{N}]


在当前版本上创建轻量级标签
git tag <name>   #new a tag;  init version is HEAH
在当前版本上创建带注释的标签
git tag -a <tagname> -m  "balabala..." # 带注释的标签
展示所有的标签
git tag     # show the tag list
删除标签
git tag -d <tagname> # delete a tag
展示某个标签的信息
git show <tagname>
切换某一标签
git checkout <tagname> # 切换到某一标签
git push origin <tagname> # push a tag to remote
git push origin --tags   # push all tags to remote
git push origin :refs/tags/<tagname> # delete a tag in remote

#ignore Some files
https:#github.com/github/gitignore


```



## 建议初始配置

```sh
git config --global color.ui true

# 使用git unstage取消暂存
git config --global alias.unstage 'reset HEAD'
eg: git unstage test.py   =>   git reset HEAD test.py

# git lg 显示更精简的信息
git config --global alias.lg "log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"
```

## bash中别名设置

```sh
alias gb='git branch'
alias gd='git diff'
alias gst='git status'
alias gaa='git add --all'
alias gcm='git checkout master'
alias gcd='git checkout develop'
alias ggpush='git push origin "$(git_current_branch)"'
alias ggpull='git pull origin "$(git_current_branch)"'
alias glg='git lg' # 显示提交日志
alias grlg='git reflog' # 显示版本变更操作记录
alias ignore='vim .gitignore' # 编辑.gitignore文件
cm(){ gaa; git commit -m "$*" }
gmerge_dev(){ git merge --no-ff -m "$*" develop }
```
