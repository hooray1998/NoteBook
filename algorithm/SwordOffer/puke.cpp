/*************************************************************************
    > File Name: puke.cpp
    > Author:hooray
    > Mail:hoorayitt@gmail.com 
    > Created Time: 2019年04月02日 星期二 21时29分37秒
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool IsContinuous( vector<int> numbers ) {
        sort(numbers.begin(),numbers.end());
        int len = numbers.size();
        
		int sum = 0;
		int zero = 0;
        int pre;
        bool findHead = false;
        for(int i=0;i<len;i++)
        {
            if(numbers[i]==0)
			{
                ++ zero;
			}
            else if(!findHead)
            {
                findHead = true;
                pre = numbers[i];
            }
            else if(numbers[i]==pre)
            {
                return false;
            }
			else
			{
				sum += numbers[i]-pre-1;
				pre = numbers[i];
			}
        }
		if(sum<=zero)
		{
			return true;
		}
		else
		{
			return false;
		}

        
    }
};
int main(){
	vector<int> list={5,2,3,6,0};

	Solution s;
	cout<<s.IsContinuous(list);

	return 0;
}
