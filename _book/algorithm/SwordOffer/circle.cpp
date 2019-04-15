/*************************************************************************
    > File Name: ./circle.cpp
    > Author:hooray
    > Mail:hoorayitt@gmail.com 
    > Created Time: 2019年04月02日 星期二 21时52分47秒
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int LastRemaining_Solution2(int n, int m)
	{
        int least = n;
		int num = 0;
        
		bool *die = new bool(n);
        for(int i=0;i<n;i++)
			die[i] = false;
        int cur=0;
        while(least!=1)
        {
            if(num!=m-1)
            {
                ++num;
            }
            else
            {
				die[cur] = true;
                num = 0;
                --least;
            }
			cur = (cur+1)%n;
			while(die[cur])
				cur = (cur+1)%n;
        }
		while(die[cur])
			cur = (cur+1)%n;

	}
    int LastRemaining_Solution(int n, int m)
    {
        queue<int> l;
        int least = n;
		int num = 0;
        
        for(int i=0;i<n;i++)
            l.push(i);
        int cur;
        while(least!=1)
        {
            cur = l.front();
            l.pop();
            if(num!=m-1)
            {
                l.push(cur);
                ++num;
            }
            else
            {
                num = 0;
                --least;
            }
        }
		return l.front();
    }
};
int main(){
	Solution s;
	cout<<s.LastRemaining_Solution(7,2);

	return 0;
}
