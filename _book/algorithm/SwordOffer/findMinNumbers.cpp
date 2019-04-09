/*=========================================================
> File Name: SwordOffer/findMinNumbers.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月08日 星期一 19时51分46秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int patition(vector<int> &v, int s, int e){
        //包括s和k
        int key = v[s];
        while(s<e)
        {
            while(s<e&&v[e]>key) e--;
            v[s] = v[e];
            while(s<e&&v[s]<=key) s++;
            v[e] = v[s];
        }
        v[s] = key;
        return s;
    }
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
		vector<int> result;
        if(findMinNumbers(input,0,input.size()-1,k))
		{
			for(int i=0;i<k;i++)
				result.push_back(input[i]);
		}
		return result;
    }
    
    bool findMinNumbers(vector<int> &v,int s,int e, int k)
    {
        if(s>e)
            return false;
		if(e==k-1)
			return true;
        int p = patition(v,s,e);
        if(p==k-1)
            return true;
        else if(p<k-1)
        {
            return findMinNumbers(v,p+1,e,k);
        }
        else
        {
            return findMinNumbers(v,s,p-1,k);
        }
    }
};
int main(){
	vector<int> v={3,5,9,10,8,4,0,2,5,1};
	Solution s;
	v = s.GetLeastNumbers_Solution(v,10);
	for(int i=0;i<v.size();i++)
		cout<<v[i]<<' ';

	return 0;
}
