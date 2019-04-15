/*=========================================================
> File Name: IsPopOrder.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月02日 星期二 22时56分26秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool IsPopOrder2(vector<int> pushV,vector<int> popV) {
		int len = pushV.size();
		if(!len)
			return true;

		int p_top,p_ready;
		bool fin = false;
		for(int i=0;i<len;i++)
			if(pushV[i]==popV[0])
			{
				p_top = i-1;
				p_ready = i+1;
				fin = true;
				break;
			}
		if(!fin)
			return false;
		fin = false;

		for(int i=1;i<len;i++)
		{
			if(p_top<0)
			{
				//重新findtop
				for(int j=0;j<len;j++)
					if(pushV[j]==popV[i])
					{
						p_top = j-1;
						p_ready = j+1;
						break;
					}
				//p_top = p_ready;
				//++p_ready;
			}
			if(pushV[p_top]==popV[i])
				--p_top;
			else if(p_ready<len&&pushV[p_ready]==popV[i])
				++p_ready;
			else
				return false;
		}
		return true;
        
    }
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
		int len = pushV.size();
		stack<int> s;

		int i=0;
		for(int j=0;j<len;j++)
		{
			while(s.empty()||s.top()!=popV[j])
			{
				if(i!=len)
					s.push(pushV[i++]);
				else
					return false;
			}
			s.pop();
		}
		return true;

	}
};
int main(){
	Solution s;
	vector<int> pushv={1,2,3,4,5};
	vector<int> popv={3,5,4,2,1};
	if(s.IsPopOrder(pushv,popv))
		cout<<"ok";
	else
		cout<<"no";



	return 0;
}
