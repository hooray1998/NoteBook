NP-hard
编辑
其中，NP是指非确定性多项式（non-deterministic polynomial，缩写NP）。所谓的非确定性是指，可用一定数量的运算去解决多项式时间内可解决的问题。
例如，著名的推销员旅行问题（Travel Saleman Problem or TSP）：假设一个推销员需要从香港出发，经过广州，北京，上海，…，等 n 个城市， 最后返回香港。 任意两个城市之间都有飞机直达，但票价不等。假设公司只给报销 C 元钱，问是否存在一个行程安排，使得他能遍历所有城市，而且总的路费小于 C？
推销员旅行问题显然是 NP 的。因为如果你任意给出一个行程安排，可以很容易算出旅行总开销。但是，要想知道一条总路费小于 C 的行程是否存在，在最坏情况下，必须检查所有可能的旅行安排！ 这将是个天文数字。
旅行推销员问题是数图论中最著名的问题之一，即“已给一个n个点的完全图，每条边都有一个长度，求总长度最短的经过每个顶点正好一次的封闭回路”。Edmonds，Cook和Karp等人发现，这批难题有一个值得注意的性质，对其中一个问题存在有效算法时，每个问题都会有有效算法。
迄今为止，这类问题中没有一个找到有效算法。倾向于接受NP完全问题（NP-Complete或NPC）和NP难题（NP-Hard或NPH）不存在有效算法这一猜想，认为这类问题的大型实例不能用精确算法求解，必须寻求这类问题的有效的近似算法。
此类问题中，经典的还有 子集和问题； Hamilton回路问题；最大团问题


算法中的P问题、NP问题、NP完全问题和NP难问题





在讨论算法的时候，常常会说到这个问题的求解是个P类问题，或者是NP难问题等等，于是我特地搜了这方面的资料，自己总结了下，估计研究算法的大家应该都知道，要是我总结的哪里不对，欢迎一起探讨~



在讲P类问题之前先介绍两个个概念：多项式，时间复杂度。(知道这两概念的可以自动跳过这部分)

1、多项式：axn-bxn-1+c

恩....就是长这个样子的，叫x最高次为n的多项式....

咳咳，别嫌我啰嗦。。有些人说不定还真忘了啥是多项式了。。例如第一次看到的鄙人→_→

2、时间复杂度

我们知道在计算机算法求解问题当中，经常用时间复杂度和空间复杂度来表示一个算法的运行效率。空间复杂度表示一个算法在计算过程当中要占用的内存空间大小，这里暂不讨论。时间复杂度则表示这个算法运行得到想要的解所需的计算工作量，他探讨的是当输入值接近无穷时，算法所需工作量的变化快慢程度。

举个例子：冒泡排序。

在计算机当中，排序问题是最基础的，将输入按照大小或其他规则排好序，有利于后期运用数据进行其他运算。冒泡排序就是其中的一种排序算法。假设手上现在有n个无序的数，利用冒泡排序对其进行排序，

①首先比较第1个数和第2个数，如果后者>前者，就对调他们的位置，否则不变

②接着比较第2个数和第3个数，如果后者>前者，就对调他们的位置，否则不变

③一直向下比较直到第n-1和第n个数比较完，第一轮结束。（这时候最大的数移动到了第n个数的位置）

④重复前三步，但是只比较到第n-1个数（将第二大的数移动到第n-1个数位置）

⑤持续每次对越来越少的元素重复上面的步骤，直到没有任何一对数字需要比较。

举个实例：5,4,3,2,1，对其进行排序，先是比较5跟4变成4,5,3,2,1，第一轮结束后变成43215，可以计算，当对其排序完正好要经过4+3+2+1=10次比较，当然这是最复杂的情况，即完全反序。可以知道对于n个数，至多要经过1+2+...+n-1即(n^2-n)/2次比较才能排好序。这个式子里n的最高次阶是2，可知道当n→∞时，一次性对其比较次数影响很小，所以我们把这个算法的时间复杂度比作：o(n^2)。取其最高次，可以看出，这是一个时间复杂度为多项式的表示方式。

时间复杂度排序o(1)<o(n)<o(lgn)<o(n^2)<o(n^a)<o(e^n)（a>2,n表示输入的数据个数，o(1)为常数级别）



好了，介绍完上面的概念就可以开始讲关于什么叫P类问题了。以上个例子冒泡排序为例，我们知道了，在排序这个大问题里，是可以找到一种时间复杂度为多项式o(n^2)的算法(如冒泡排序法)来求解排序问题的，所以我们说排序问题是一个有多项式时间算法的问题。

所以我们称，

P类问题：存在多项式时间算法的问题。(P：polynominal，多项式)



然后扯个题外话，为什么我们要研究这个？因为计算机处理的输入常常不是那么几十个几千个那么一点点，想象一下，当计算机处理的数据达到100万个的时候，时间复杂度为o(n^2)和o(e^n)的算法，所需的运行次数简直是天壤之别，o(e^n)指数级的可能运行好几天都没法完成任务，所以我们才要研究一个问题是否存在多项式时间算法。而我们也只在乎一个问题是否存在多项式算法，因为一个时间复杂度比多项式算法还要复杂的算法研究起来是没有任何实际意义的。



好了，接下来我们介绍NP，先给定义，

NP类问题：能在多项式时间内验证得出一个正确解的问题。(NP:Nondeterministic polynominal，非确定性多项式)

P类问题是NP问题的子集，因为存在多项式时间解法的问题，总能在多项式时间内验证他。



注意定义，这里是验证。NP类问题，我用个人的俗话理解就是，不知道这个问题是不是存在多项式时间内的算法，所以叫non-deterministic非确定性，但是我们可以在多项式时间内验证并得出这个问题的一个正确解。举个例子，

著名的NP类问题：旅行家推销问题(TSP)。即有一个推销员，要到n个城市推销商品，他要找出一个包含所有n个城市的环路，这个环路路径小于a。我们知道这个问题如果单纯的用枚举法来列举的话会有(n-1)! 种，已经不是多项式时间的算法了，(注：阶乘算法比多项式的复杂)。那怎么办呢？我们可以用猜的，假设我人品好，猜几次就猜中了一条小于长度a的路径，我画画画画，好的，我得到了一条路径小于a的环路，问题解决了，皆大欢喜。可是，我不可能每次都猜的那么准，也许我要猜完所有种呢？所以我们说，这是一个NP类问题。也就是，我们能在多项式的时间内验证并得出问题的正确解，可是我们却不知道该问题是否存在一个多项式时间的算法，每次都能解决他(注意，这里是不知道，不是不存在)。

所以这就引出了这类讨论的一个千年问题：是否 NP类问题=P类问题？

即，是否所有能在多项式时间内验证得出正确解的问题，都是具有多项式时间算法的问题呢？

太让人震惊了，要是解决了这个问题，那岂不是所有的NP问题都可以通过计算机来解决？



圣战的结果是，有的存在，有的不存在。=_=

在这场圣战中，人们还发现了很多的东东，也就是我们接下来要介绍的NPC问题(啊喂，我不是游戏NPC)和NPH问题。

(PS :网络上经常有人说，这不是个NP问题吗，其实很多时候他们说的应该是NPC问题，而不是NP问题)

为了证明这个千古难题，科学家想出了很多办法。其中之一就是问题的约化。所谓问题约化就是，可以用问题B的算法来解决A ，我们就说问题A可以约化成问题B。举个例子，一元一次方程的求解，跟二元一次方程的求解，我们知道，只要能求解二元一次方程，那就可以用二元一次方程的解法来求解一元一次方程，只需要将一元一次方程加上y，并附加一个方程y=0就可以将一元一次方程变形为一个二元一次方程，然后用二元一次方程的解法来求解这个方程。注意，这里二元一次方程的解法会比一元一次的复杂。所以我们说，只需要找到解二元一次方程的规则性解法，那就能用这个规则性解法来求解一元一次方程。从这里也可以看出，约化是具有传递性的，如A约化到B，B约化到C，A就可以约化到C，同时不断约化下去，我们会发现一个很惊人的特性，就是他一定会存在一个最大的问题，而我们只需要解决了这个问题，那其下的所有问题也就解决啦！这就是我们所说的NPC问题的概念！！！

引到NP问题里就是，对于同一类的所有的NP类问题，若他们都可以在多项式时间内约化成最难的一个NP类问题，（我们直观的认为，被约化成的问题应具有比前一个问题更复杂的时间复杂度）当我们针对这个时间复杂度最高的超级NP问题要是能找到他的多项式时间算法的话，那就等于变向的证明了其下的所有问题都是存在多项式算法的，即NP=P！！！！给出NPC问题定义，

NPC问题:如果所有np问题都能在多项式时间内转化为他，则称该np问题为npc问题(NPC:NP complete又叫NP完全问题)

NPC问题是NP问题的子集。



当然，很多时候NPC问题是找不到一个多项式时间算法的，更多时候他是一个指数级的算法。



最后介绍下NPH问题。

NPH问题：我们又叫NP难问题，他不是一个NP问题，然后所有的NPC问题都可以在多项式时间内转化为他的话，我们就叫他NPH（hard）问题。


