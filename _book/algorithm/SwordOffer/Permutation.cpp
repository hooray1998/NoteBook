/*=========================================================
> File Name: Permutation.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月15日 星期一 11时14分44秒
> =======================================================*/

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
	string str="aabc";
	Solution s;
	vector<string>res = s.Permutation(str);
	for(int i=0;i<res.size();i++)
		cout<<res[i]<<endl;

	return 0;
}
