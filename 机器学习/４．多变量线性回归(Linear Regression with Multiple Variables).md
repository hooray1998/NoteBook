## 多维特征
![37169802.png](４．多变量线性回归(Linear Regression with Multiple Variables)_files/37169802.png)
梯度下降算法：
求解各个thera的偏导
![38467389.png](４．多变量线性回归(Linear Regression with Multiple Variables)_files/38467389.png)
![38890672.png](４．多变量线性回归(Linear Regression with Multiple Variables)_files/38890672.png)
特征缩放，为了让梯度下降算法更快的收敛
![39099521.png](４．多变量线性回归(Linear Regression with Multiple Variables)_files/39099521.png)
范围未必很一致， 大致相差不大即可，比如0 ～ 3 ， -2～0.5
![39270811.png](４．多变量线性回归(Linear Regression with Multiple Variables)_files/39270811.png)
![39461449.png](４．多变量线性回归(Linear Regression with Multiple Variables)_files/39461449.png)
让梯度下降正常工作，需要将上述的学习率降低，通常都是因为学习率过高引起的，
#### 总结
- 学习率太小，收敛太慢
- 太大，在不断地迭代后未cost function必会减小，可能不会收敛
- 所以要选择不同的学习率
例如，
![39707777.png](４．多变量线性回归(Linear Regression with Multiple Variables)_files/39707777.png)
### 构造新的特征
例如将房子的宽高合并为房子的size
### 多项式回归
![39894603.png](４．多变量线性回归(Linear Regression with Multiple Variables)_files/39894603.png)
eg： price不会因为size的升高而降低
所以二维不适合
![39948429.png](４．多变量线性回归(Linear Regression with Multiple Variables)_files/39948429.png)
从多种拟合的方式中选择
### 正规方程算法
可以一步得到最优的thera
![40287214.png](４．多变量线性回归(Linear Regression with Multiple Variables)_files/40287214.png)
#### 与梯度下降比较
gradient decreat|Normal Equation
:-:|:-:
需要选择学习率|不需要选择学习率
需要很多次迭代|No need
当特征很多时工作很好|特征很多时计算很慢（例如n>10000)

###　正规方程失效情况
解决X'X不可逆
- 某些特征线性相关
- 正规化