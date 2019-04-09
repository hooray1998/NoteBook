/*************************************************************************
    > File Name: reConstructBinaryTree.cpp
    > Author:hooray
    > Mail:hoorayitt@gmail.com 
    > Created Time: 2019年03月29日 星期五 13时50分00秒
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    //二分法思想，
    int minNumberInRotateArray(vector<int> rotateArray) {
        
        int start=0;
        int end = rotateArray.size()-1;
        if(end==-1)
            return 0;
        int mid;
        int a,b,c;
        while(start<=end)
        {
            mid = (start+end)/2;
            a = rotateArray.at(start);
            b = rotateArray.at(mid);
            c = rotateArray.at(end);
            if(a<=b&&b<=c)
                return a;
            else if(a<=b&&b>c)
                start = mid+1;
            else
                end = mid;
        }
    }
};
vector<int> v1;

int main()
{
	cout<<-3%2;

	return 0;
}
