# 排列

## 分类
排列
- 每个元素只有一个，全都要上场(全排列)

组合
1. 每个元素只有一个，不用全都上场(组合数)
2. 每个元素有多个, 组合成固定的数额
	1. 不看序列，只看各元素用了几个
		1. 总个数最少(找零钱)
		2. 求可行组合的种类数(零钱组合)
	2. 看序列(爬楼梯)

### 全排列
```python
'''
输出abcd的全排列,归纳法
输出不是字典序，需要sort
'''
def p(m):
    if m==n:
        res.append(list(l))
    else:
        for i in range(m,n):
            l[i],l[m] = l[m],l[i]
            p(m+1)
            l[i],l[m] = l[m],l[i]
l=['a','b','c','d']
res = []
n=4
p(0)
res = sorted(res)
for i in res:
    print(i)

```

```python
''' 连续数字的全排列,回溯法 '''
Count = 0  # 记录迭代的次数
MaxDeep = 3
List = [0] * (MaxDeep+1)

def Try(CurDeep):
    '''探索第CurDeep层'''
    global Count
    for i in range(List[CurDeep]+1, MaxDeep+1):
        Count += 1
        List[CurDeep] = i
        if OK(CurDeep): #前面符合条件=>继续深一层Try
            if CurDeep == MaxDeep:
                print(List[1:])
                break
            Try(CurDeep+1)
    List[CurDeep] = 0

def OK(CurDeep):
    s = set(List[1:CurDeep+1])
    if len(s) == CurDeep:
        return True
    else:
        return False

Try(1)
print("Count:",Count)
```

```cpp
#include<bits/stdc++.h>
using namespace std;
class Solution {
private:
	string s;
	int len;
	vector<string> res;
public:
    vector<string> Permutation(string str) {
		s = str;
		len = str.size();
		Try(0);
		//Try2();
		return res;
    }
	void Try(int d){
		if(d==len-1)
			res.push_back(s);
		else{
			Try(d+1);//原始的也要输出
			for(int i=d+1;i<len;i++)
			{
				if(s[i]!=s[d])//如果和开头相同则不再交换
				{
					swap(s[d],s[i]);
					Try(d+1);
					swap(s[d],s[i]);
				}
			}
		}
	}
	void Try2(){//不用排序算法输出字典序, 还没解决重复的问题
		char *str = new char(strlen(s.c_str()));
		strcpy(str, s.c_str());
		sort(str,str+len);

		int i, j;
		while(true)
		{
			i = j = len-1;
			res.push_back(string(str));

			--j;
			while(j>=0&&str[j]>=str[j+1]) --j;
			if(j<0) return ;

			while(i>j&&str[i]<=str[j]) i--;//肯定有比j大的
			swap(str[i],str[j]);

			//交换j后面的
			for(int e = len-1,s = j+1;s<e;s++,e--)
				swap(str[s],str[e]);
		}
	}
};
int main(){
	string str="fabc";
	Solution s;
	vector<string>res = s.Permutation(str);
	for(int i=0;i<res.size();i++)
		cout<<res[i]<<endl;

	return 0;
}
```

# 组合


### 普通组合问题
```python
# -*- coding:utf-8 -*-
'''
组合问题 , 相比全排列，三处改动
回溯法
'''
Count = 0  # 记录迭代的次数
MaxDeep = 3
MaxValue = 4
List = [0] * (MaxDeep+1)

def Try(CurDeep):
    '''探索第CurDeep层'''
    global Count

    # 相比全排列，两处改动
    # for i in range(List[CurDeep]+1, MaxDeep+1): #全排列
    for i in range(List[CurDeep-1]+1, MaxValue+1): 
        Count += 1
        List[CurDeep] = i
        if OK(CurDeep): #前面符合条件=>继续深一层Try
            if CurDeep == MaxDeep:
                print(List[1:])
                # break # 全排列
                continue
            Try(CurDeep+1) # 没到最后一层
    List[CurDeep] = 0

def OK(CurDeep):
    s = set(List[1:CurDeep+1])
    if len(s) == CurDeep:
        return True
    else:
        return False

if __name__ == "__main__":
    Try(1)
    print("Count:",Count)
```

### 爬楼梯问题

> 若只允许一次1步，2步，3步三种走法
> n层楼梯的走法等于[n-1] + [n-2] + [n-3]

```python
stairs = 4
a = [0] * (stairs+1)
a[1] = 1
a[2] = 2
a[3] = 4

for i in range(4,stairs+1):
	a[i] = a[i-1] + a[i-2] + a[i-3]
print(a[stairs], ' ways')


```
### 零钱组合问题

>用1,2,5,20,100组成200元，共有多少种组合方式
解法
用1,2,5组成12的方式数量 等于 下面两项之和。
1. 1,2组成12的数量 (不用5的数量)
2. 1,2,5组成7的数量(用5的数量,至少一个)
	- (若用一个5相当于组成7不用5)
	- (若用两个5相当于组成7用一个5)
	- .......
	- 上述所有项相加就是组成7所有的可能

```python
money = [1,2,5,10]
l = []
for i in range(11):
	l.append(0)

l[0] = 1
for m in money:
	for i in range(1,11):
		if m<=i:
			l[i] += l[i-m]

print(l[10])
```


### 零钱找零

问题描述
>需要找66元的零钱，共有1,2,5,10这几个面额，最少需要几张钞票
思路
>k元找零 等效于 k-1,k-2,k-5,k-10找零里面最小的 再加一

```python
money = [1,2,5,10]
target = 66
l = []
for i in range(target+1):
	l.append(target)

l[0] = 0
for k in range(1,target+1):
	min = target
	for m in money:
		if m<=k:
			if min>l[k-m]:
				min = l[k-m]
		else:
			break
	l[k] = min + 1

print(l[target])
```

