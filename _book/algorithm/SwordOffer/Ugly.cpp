/*************************************************************************
    > File Name: Ugly.cpp
    > Author:hooray
    > Mail:hoorayitt@gmail.com 
    > Created Time: 2019年04月01日 星期一 16时33分31秒
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int GetUglyNumber_Solution(int index) {
        int n = 0;
        while(index)
        {
            ++n;
            if(Ugly(n))
                --index;
        }
        return n;
    }
    bool Ugly(int n){
        while(n%2==0) n/=2;
        while(n%3==0) n/=3;
        while(n%5==0) n/=5;
        if(n==1) return true;
        else     return false;
    }
};
int main(){

	Solution s;
	cout<<s.GetUglyNumber_Solution(10000);
	return 0;
}
