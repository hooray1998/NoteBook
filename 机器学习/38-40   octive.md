

##38 基本操作

 

 

1      直接加减乘除：5+6

2  等号：==。“%”评论

3  不等号：~=

4  逻辑 AND：&&

5  逻辑Or：||

6  异或运算：XOR。如xor(1,0)

7  更改前面默认提示符：PS1。如PS1('>> ');

8  末尾输入分号阻止输出：如a=3；

9  例子： b='hi'; c=(3>=1);此时系统是记录了c的值，再输入c后不加分号，将输出c=1，相对于判断前式为“真”。

10  输出或显示：a=pi;   要输出a的值，一种是直接输“a回车”，得到a=3.1416。另几种用显示函数： disp(a); disp(sprintf('2 decimals; %0.2f', a))    表示输出字符串。将输出：2 decimals: 3.14。“%0.2f”表示此处替代A。

11  打印多位小数与少位小数“format long”、“format short”：如format long回车。a回车。将输出a=3.14159265358979。

12  矩阵输入：A=[1 2; 3 4; 5 6] A=[1 2; 3 4; 5 6] 行向量1*3：v=[1 2 3] 列向量3*1：v=[1; 2; 3]

13  从1开始到2之间每增加0.1取一个值，赋值1*11矩阵：v=1:0.1:2

14  1到6隔1取值1*11矩阵：v=1:6

15  2*3的每个值都是1的矩阵：ones(2,3)

16  2*3的每个值都是2的矩阵：2*ones(2,3)

17  zeros(1,3)：3个“0”

18  w=rand(1,3)：1*3的随机数矩阵

19  rand(3,3)：3*3的0到1之间的随机数矩阵

20  randn(1,3)：得到3个高斯随机数矩阵

21  w=-6+sqrt(10)*(randn(1,10000)); hist(w)。做出一个条形图 hist(w,50)。条形图更细

22  eye(4)：4*4的单位矩阵。

23  help命令

 

 

## 39

A = [1 2; 3 4; 5 6] % 生成3*2的矩阵

size(A) % 查看A的形状，返回的值[3, 2]，其实是个 1*2 的矩阵，同样也可以存起来

size(A, 1) % 返回A的第一维长度

length(A) % 返回A的最长一个维度的长度，如果A是上面的例子，那就返回3

%% 一般来说，只对向量使用 length

pwd % 查看当前工作路径，可以用 cd 命令来改变路径

ls % 列出当前目录下的文件

% 用 load 命令或 load('xxx.dat') 函数可以加载数据

who % 显示当前工作环境中的所有变量

whos % 更详细地查看当前工作环境中的所有变量

clear A % 删除变量 A (clear 用于删除某个变量)

save eye.dat I % 将变量 I 存于 'eye.dat' 文件中

clear % 清除工作空间中的所有变量

load eye.dat % 又把存在 'eye.dat' 文件中的变量 I (变量名还是I)读取了回来

save eye.txt I --ascii % 用 tet 文件(ASCII 编码)存储变量

A = [1 2; 3 4; 5 6]

A[:,2] = [10; 11; 12] % 对 A 的第二列赋值

A = A[A, [100; 101; 102]] % 在 A 的右边加一列

A(:) % 将矩阵 A 的所有值放入一个单独的列向量中

 

 

## 40

1. A * B

2. A .* B ; 每个元素独立乘

3. .^ 对每个元素

4. 1 ./ A

5. log(A)

6. exp(A)

7. abs(A)

8. ones

9. A' ; transport 转置

10. max

11. find(A < 3)  a中的每个元素和3比较 找到比3小的元素

12. magic; 幻方 每行每列和对角线和相同

13. sum/prod/floor/ceil 求和 求乘积 向下 向上取整



