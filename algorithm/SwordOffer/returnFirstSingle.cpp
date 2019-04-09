/*=========================================================
> File Name: algorithm/SwordOffer/returnFirstSingle.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月07日 星期日 23时39分47秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        short show[256];
        for(int i=0;i<256;i++)
            show[i] = 0;
        int len = str.length();
        for(int i=0;i<len;i++)
        {
            ++show[str[i]];
        }
        for(int i=0;i<len;i++)
        {
            if(show[str[i]]<2)
                return i;
        }
        return -1;
    }
};
int main(){
	Solution s;
	string str("google");
	cout<<s.FirstNotRepeatingChar(str);

	return 0;
}
