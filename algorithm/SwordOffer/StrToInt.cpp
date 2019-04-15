/*=========================================================
> File Name: /home/itt/MyNutStore/Notes/algorithm/SwordOffer/StrToInt.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月14日 星期日 23时38分32秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int StrToInt(string str) {
		if(str.empty())
			return 0;
		int res = 0;
		int index = 0;
		bool minus = false;
		int len = str.size();
		if(str[index] == '-')
		{
			index++;
			minus = true;
			//if(len==1)
				//return 0;
		}
		else if(str[index] == '+')
		{
			index++;
			//if(len==1)
				//return 0;
		}
		bool f = false;
		for(;index<len;index++)
			if(str[index]<'0'||str[index]>'9')
				return 0;
			else{
				f = true;
				res += str[index]-'0';
				res *= 10;
			}

		if(f)
			res /= 10;
		else
			return 0;
		if(minus)
			res = -res;
		return res;
        
    }
};
int main(){

	Solution s;
	cout<<s.StrToInt("+0");
	return 0;
}
