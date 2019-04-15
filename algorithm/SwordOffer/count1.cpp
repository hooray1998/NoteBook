/*************************************************************************
    > File Name: count1.cpp
    > Author:hooray
    > Mail:hoorayitt@gmail.com 
    > Created Time: 2019年04月01日 星期一 17时00分59秒
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;
class Solution_better {
public:
    int NumberOf1Between1AndN_Solution(int n)
    {
        int num = n;
        int bit = 1;
        int pre = 0;
        int post = 0;
        int ret = 0;
        int tar = 0;
        int i = 0;
        while (num)
            {
            tar = num % 10;
            pre = num / 10;
            if (tar == 0)
                ret += pre * bit;
            else if (tar == 1)
                ret += post + 1 + pre * bit;
            else
                ret += (pre + 1) * bit;
            bit *= 10;
            post += tar * pow(10, i);
            num = pre;
            i++;
        }
        return ret;
    }
};
class Solution {
public:
    int NumberOf1Between1AndN_Solution(int n)
    {
		int ten[] = {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
		int c[] = {0,1,20,300,4000,50000,600000,7000000,80000000};
		int a[30];//记录低位数
		int b[30];//记录每一位
		int tenS = 1;
		int d = 0;
		int t;
		while(t = n/tenS)
		{
			a[d] = n - t*tenS; 
			b[d+1] = t%10;
			++d;
			tenS *= 10;
		}
		a[d] = n;
		//a[1] = 3		b[1] = 3
		//a[2] = 23		b[2] = 2
		//a[3] = 123	b[3] = 1
		//123 => d == 3
		int sum = 0;

		//示例：5678
		while(d>0)
		{
			//cout<<"cur sum:"<<sum<<endl;
			//cout<<"cur a[d]:"<<a[d]<<endl;
			//cout<<"cur b[d]:"<<b[d]<<endl;
			//首位=0
			if(d>1&&b[d]>0)
			{
				//cout<<"enter 1"<<endl;
				sum += c[d-1];// 维度为d-1所构成的所有的含1的总数
			}
			//首位=1
			if(b[d]==1)
			{
				//cout<<"enter 2"<<endl;
				sum += a[d-1]+1;// 最高位为1时对应的去掉最高位的值，共1000-1678个数
			}
			//首位>1
			else if(b[d]>1)
			{
				//cout<<"enter 3"<<endl;
				for(int i=0;i<d;i++)
					sum += ten[i] ; //最高位为1时的所有数
				sum += (b[d]-2)*c[d-1]; //最高位为2,3,4时对应的->维度为d-1所构成的所有的含1的总数
			//最高位为5时去掉，相当于678组成的所有的结果
			}
			//cout<<"sum-: "<<sum<<endl;
			--d;
		}

		cout<<"sum: "<<sum<<endl;
    }
};
int main(){

	Solution s;
	int temp;
	while(1)
	{
		cin>>temp;
		s.NumberOf1Between1AndN_Solution(temp);

	}
	//1 + 10-19

	return 0;
}
