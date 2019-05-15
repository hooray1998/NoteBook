# Ubuntu18.04开机美化

[参考博客](https://www.cnblogs.com/lishanlei/p/9090404.html)

### 登录界面

1. 备份ubuntu.css
2. 将stwassp中的ubuntu.css 拷贝到 /usr/share/gnome-shell/theme/ 下

```sh
sudo cp /usr/share/gnome-shell/theme/ubuntu.css /usr/share/gnome-shell/theme/ubuntu.bak
sudo cp ubuntu.css  /usr/share/gnome-shell/theme/
```

### 开机动画


### grub引导界面








# [如是说](https://www.cnblogs.com/lishanlei/)
### 参考博客：[点击打开链接](https://www.cnblogs.com/feipeng8848/p/8970556.html)


## 

	</div><!--end: blogTitle 博客的标题和副标题 -->
	<div id="navigator">

*   [博客园](https://www.cnblogs.com/)
*   [首页](https://www.cnblogs.com/lishanlei/)
*   [新随笔](https://i.cnblogs.com/EditPosts.aspx?opt=1)
*   [联系](https://msg.cnblogs.com/send/%E5%A6%82%E6%98%AF%E8%AF%B4)
*   [订阅](https://www.cnblogs.com/lishanlei/rss)
<!--[![订阅](//www.cnblogs.com/images/xml.gif)](https://www.cnblogs.com/lishanlei/rss)-->
*   [管理](https://i.cnblogs.com/)

# [Ubuntu18.04美化主题(mac主题)](https://www.cnblogs.com/lishanlei/p/9090404.html)


前端时间Ubuntu18.04LTS发布，碰巧之前用的Ubuntu16.04出了一点问题，懒得解决，索性就换了Ubuntu18.04。

成果：

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709155601754-1632984450.png)

&nbsp;

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709155618224-1553837022.png)

&nbsp;

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709155638509-130612044.png)

&nbsp;

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709155655920-693049429.jpg)

&nbsp;

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709155708258-2066594321.png)

&nbsp;

参考博客：[https://www.cnblogs.com/feipeng8848/p/8970556.html](https://www.cnblogs.com/feipeng8848/p/8970556.html)

下面开始进行美化配置：

安装主题工具：**GNOME Tweaks**&nbsp;（Ubuntu18.04对软件中心也做了强化，也可以去软件中心进行下载）

<div class="cnblogs_code">
<pre><span style="color: #0000ff;">sudo</span> apt-<span style="color: #000000;">get update
</span><span style="color: #0000ff;">sudo</span> apt-get <span style="color: #0000ff;">install</span> gnome-tweak-tool</pre>
</div>

安装完成后打开**Tweaks**:

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709155725004-743266618.png)

&nbsp;

修改窗口的按钮位置：

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709155735908-939536801.png)

&nbsp;

将按钮位置修改到左边：

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709155755631-1808789307.png)

&nbsp;

显示或隐藏桌面上的图标：

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709155807231-126882602.png)

&nbsp;

去掉shell上无法修改的叹号：

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709155831025-500757354.png)

&nbsp;

执行命令

<div class="cnblogs_code">
<pre><span style="color: #0000ff;">sudo</span> apt-get <span style="color: #0000ff;">install</span> gnome-shell-extensions</pre>
</div>

安装完成后打开Tweaks，选择&ldquo;**Extensions**&rdquo;选项

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709155846628-1875461362.png)

&nbsp;

将&ldquo;**User themes**&rdquo;设置为**ON**

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709155911944-1250818322.png)

&nbsp;

开启后去&ldquo;Appearances&rdquo;选项中，此时shell的感叹号就没了

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709155927459-747646743.png)

&nbsp;

&nbsp;

现在已经完成了工具的安装配置，下面进行主题美化

&nbsp;

1. 安装GTK主题

链接：[点击打开链接](https://www.opendesktop.org/s/Gnome/p/1171688/)

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709155942941-1209716845.png)

&nbsp;

点击&ldquo;Files&rdquo;标签，点击文件名就可以下载

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709155952659-1905996409.png)

&nbsp;

可以看到里面一共有6个压缩文件，分别包装了各种主题，每一个文件名中有一个&ldquo;2&rdquo;，这个&ldquo;2&rdquo;的意思是该压缩包下有两个主题。

我选的是_Gnome-OSC-HS--2themes.tar.xz&nbsp;_（第一个压缩文件），进行下载

进行解压：

<div class="cnblogs_code">
<pre>xz -d Gnome-OSC-HS--2themes.<span style="color: #0000ff;">tar</span><span style="color: #000000;">.xz
</span><span style="color: #0000ff;">tar</span> xvf Gnome-OSC-HS--2themes.<span style="color: #0000ff;">tar</span>.xz</pre>
</div>

解压后得到的文件夹中有两个文件夹

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160008169-1954505865.png)

&nbsp;

这两个文件夹分别是两个主题，将其移动到<span style="color: #ff6600;">/usr/share/themes/</span>下就行了。

打开之前的工具Tweaks(中文名叫&ldquo;优化&rdquo;)，在&ldquo;外观&rdquo;选项下可以选择刚刚安装的主题，安装后的截图：

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160018967-1659950275.png)

&nbsp;

刚刚的两个文件夹就是两个主题，这两个主题从名字上看只有transparent前面是否有个not，意思就是没有透明效果。到现在已经修改了外观样式了。

&nbsp;

2.修改图标

链接：[点击打开链接](https://www.opendesktop.org/s/Gnome/p/1102582/)

效果：

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160040296-1767862630.png)

&nbsp;

我下载的时macOS11的，解压后把文件放到<span style="color: #ff6600;">/usr/share/icons/</span>下

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160052271-216522992.png)

&nbsp;

然后去Tweaks中应用一下

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160157962-868705898.png)

&nbsp;

&nbsp;

3. 修改桌面Shell

链接：[点击打开链接](https://www.opendesktop.org/s/Gnome/p/1013741/)

下载红框中的

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160211001-1598633694.png)

&nbsp;

解压后将文件夹放到<span style="color: #ff6600;">/usr/share/themes/</span>目录下。

去Tweaks中进行应用：

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160225821-1153026074.png)

&nbsp;

效果如下：

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160237615-359680568.png)

&nbsp;

&nbsp;

4.设置开机动画

执行命令：

<div class="cnblogs_code">
<pre><span style="color: #0000ff;">vi</span> /etc/alteernatives/default.plymouth</pre>
</div>

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160251123-879744412.png)

&nbsp;

如上图所示，default.plymouth文件指定了一个logo文件夹，指定了一个执行脚本。开机的时候就用这个文件制定的logo和脚本执行。那么把这个logo文件夹和脚本制定成我们想要的就可以修改开机动画。

开机动画主题链接：[点击打开链接](https://www.opendesktop.org/p/1176419/)

下载后进行解压：

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160304183-1070327613.png)

&nbsp;

把解压的文件移动到<span style="color: #ff6600;">/usr/share/plymouth/themes/</span>目录下

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160318938-1774469212.png)

&nbsp;

然后去修改一下<span style="color: #ff6600;">/etc/alternatives/default.plymouth</span>

先做一下备份：

<div class="cnblogs_code">
<pre><span style="color: #0000ff;">sudo</span> <span style="color: #0000ff;">mv</span> /etc/alternatives/default.plymouth /etc/alternatives/default.plymouth.bak</pre>
</div>

然后修改成：

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160329495-931568015.png)

&nbsp;

&nbsp;

5. GDM (GNOME Display Manager,GDM)主题

所谓的GDM主题就是登录界面的主题

链接：[点击打开链接](https://www.opendesktop.org/s/Gnome/p/1207015/)

效果：

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160342528-2007352980.png)

&nbsp;

解压压缩包后：

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160353167-1735919034.png)

&nbsp;

修改登录界面样式的原理：

在<span style="color: #ff6600;">/usr/share/gnome-shell/theme/ubuntu.css</span>就配置了登录界面的样式。

(上面下载的包中，非系统自带的这个ubuntu.css文件)

在/usr/share/gnome-shell/theme/ubuntu.css中有这样一行代码：

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160408219-1368143842.png)

&nbsp;

Ubuntu18.04的登录界面是用css文件渲染的。那么如果只是想替换登录界面的背景，把系统自带的这个css文件中指定图像文件中的位置修改成自己图片的绝对目录就行了。当然我们也可以修改css文件渲染你想要的结果，让你的登录界面炫酷一些。在我们解压的SetAsWallpaperV1.3中，还有一个脚本文件，内容如下：

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160422602-1170148419.png)

&nbsp;

这个脚本的作用是把你现在正在用的壁纸进行模糊处理，然后放到~/Pictures/gdm_look.jpg,执行过脚本后，你的~/Pictures目录下就会多一个gdm_look.jpg文件，这个文件就是当前是用的壁纸的模糊处理后的图片。

然后~/Pictures/gdm_look.jpg又被复制到/usr/share/backgrounds/目录下，再看这个图：

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160437520-2101475081.png)

&nbsp;

这个包中提供的css文件制定的登录页面壁纸，也就是脚本处理完后复制到/usr/share/backgrounds的gdm_look.jpg。

以上就是修改登录界面的原理，操作如下：

<div class="cnblogs_code">
<pre><span style="color: #0000ff;">sudo</span> <span style="color: #0000ff;">cp</span> /usr/share/gnome-shell/theme/ubuntu.css /usr/share/gnome-shell/theme/ubuntu.css.backup</pre>
</div>

用下图中的ubuntu.css替换系统自带的/usr/share/gnome-shell/theme/ubuntu.css

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160448550-1461121543.png)

&nbsp;

把SetAsWallpaper脚本文件复制到<span style="color: #ff6600;">~/.local/share/nautilus/scripts/</span>目录下，然后修改下权限

<div class="cnblogs_code">
<pre><span style="color: #0000ff;">sudo</span> <span style="color: #0000ff;">chmod</span> +x SetAsWallpaper</pre>
</div>

然后重启nautilus

<div class="cnblogs_code">
<pre>nautilus -q 该命令时关闭</pre>
</div>

点击桌面右下角&ldquo;所有应用&rdquo;,查找&ldquo;nautilus&rdquo;

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160506309-875709364.png)

&nbsp;

修改/usr/share/backgrounds的权限

<div class="cnblogs_code">
<pre><span style="color: #0000ff;">sudo</span> <span style="color: #0000ff;">chmod</span> <span style="color: #800080;">777</span> /usr/share/backgrounds/</pre>
</div>

之后去~/.local/share/nautilus/scripts/目录下执行SetAsWallpaper脚本。（执行脚本后你的桌面壁纸可能会没了，重新设置下就好了）

最后重启系统，放一张效果图（手机拍的，像素不是很高）：

![](https://images2018.cnblogs.com/blog/1201942/201807/1201942-20180709160517566-1787531285.jpg)

&nbsp;

&nbsp;

6. 修改TopBar

之前设置的gnome-shell主题是_Sierra-compact-light_,它的topbar是这样的

![](https://img-blog.csdn.net/20180525185048441?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xpc2hhbmxlaWxpeGlu/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

字体很粗且很宽，略丑，修改后：

![](https://img-blog.csdn.net/20180525185158845?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xpc2hhbmxlaWxpeGlu/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)，比较美观，下面开始修改：

我们用的Sierra-compact-light主题，所以需要去这个主题下的配置文件（.css）进行修改

<div class="cnblogs_code">
<pre>/usr/share/themes/Sierra-compact-light/gnome-shell/gnome-shell.css</pre>
</div>

当然你也如果可以修改Ubuntu默认的TopBar就不能去上面的目录了，而是应该去Ubuntu默认的shell的目录，应该是修改下面这几个文件：_gnome-classic.css, gnome-classic-high-contrast.css, gnome-shell.css_

![](https://img-blog.csdn.net/2018052518554463?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xpc2hhbmxlaWxpeGlu/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

回到<span style="color: #ff6600;">/usr/share/theme/Sierra-compact-light/gnome-shell/gnome-shell.css</span>文件，查找<span style="color: #ff6600;">#panel</span>

修改TopBar高度：

![](https://img-blog.csdn.net/20180525185833271?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xpc2hhbmxlaWxpeGlu/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

加粗字体改成正常字体：

![](https://img-blog.csdn.net/20180525185901750?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xpc2hhbmxlaWxpeGlu/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

然后注销用户再次进入就可以了。

以上。

&nbsp;

&nbsp;


