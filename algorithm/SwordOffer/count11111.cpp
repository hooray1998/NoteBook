/*=========================================================
> File Name: SwordOffer/count11111.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月08日 星期一 20时21分30秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int NumberOf1Between1AndN_Solution(int n){
		int a[30];//记录低位数
		int b[30];//记录每一位
		int ten[] = {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
		int c[] = {0,1,20,300,4000,50000,600000,7000000,80000000};
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
		//a[0] = 1;
		a[d] = n;
		//a[1] = 3		b[1] = 3
		//a[2] = 23		b[2] = 2
		//a[3] = 123	b[3] = 1
		//123 => d == 3
		int sum = 0;

		while(d)
		{
			if(a[d]==0)
				break;
			sum += c[d-1];//首位为0
			if(b[d]==1)
			{
				sum += a[d-1] + 1; //加一是因为还有后面全为0的情况。比如123,1为百位的有24个
			}
			else if(b[d]>1)
			{
				sum += ten[d-1];//首位为1
				//sum += a[d-1];//首位为真实首位
				sum += (b[d]-1)*c[d-1];
			}
			--d;
			cout<<"cur level sum:"<<sum<<endl;
		}

		return sum;
	}
};
int main(){
	Solution s;
	int n;
	while(1)
	{
		cin>>n;
		cout<<s.NumberOf1Between1AndN_Solution(n);
	}
	return 0;
}
// 10000 => 4001
// 10    => 2
