/*=========================================================
> File Name: ./reOrderArray.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月02日 星期二 22时19分29秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    void reOrderArray(vector<int> &array) {
        int len = array.size();

		int tail1=0;
		int head2=len;

		for(int i=0;i<len;i++)
			if(array[i]%2==0)
			{
				head2 = i;
				break;
			}
		if(head2==len)
			return ;

		int temp;
		for(int i=0;i<len;i++)
		{
			if(array[i]%2==1)
			{
				if(i>head2)
				{
					//Insert(head2,i);
					temp = array.at(i);
					for(int j=i;j>head2;j--)
						array[j] = array[j-1];
					array[head2] = temp;
					head2++;
				}
			}
		}
	}
};
int main(){
	Solution s;
	vector<int> a={1,2,3,4,5,6,8,7,9};
	s.reOrderArray(a);
	for(int i=0;i<a.size();i++)
		cout<<a[i]<<" ";
	return 0;
}
