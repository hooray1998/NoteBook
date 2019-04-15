/*=========================================================
> File Name: ./maxInWindows.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月13日 星期六 11时09分53秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> maxInWindows(const vector<int>& num, unsigned int size)
    {
        vector<int> res;
        int len = num.size();
        deque<int> deq;
        
        for(int i=0;i<len;i++)
        {
            while(!deq.empty()&&num[deq.back()]<num[i]) deq.pop_back();
            deq.push_back(i);
            if((deq.front()+size)<=i) deq.pop_front();//unsigned 没有负数，和整数减法会出问题。
			if(i>=(size-1))
				res.push_back(num[deq.front()]);
        }

		return res;
    }
};
int main(){
	Solution s;
	vector<int> num = {2,3,4,2,6,2,5,1};
	vector<int> res = s.maxInWindows(num, 3);
		for(int i=0;i<res.size();i++)
			cout<<"--"<<res[i]<<endl;

	return 0;
}
