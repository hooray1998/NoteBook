/*=========================================================
> File Name: MyNutStore/Notes/algorithm/SwordOffer/match.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月15日 星期一 16时33分07秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
private:
	int plen;
	int slen;
public:
    bool match(char* str, char* pattern)
    {
		cout<<"match:"<<str<<" --- "<<pattern<<endl;
		//考虑临界值
		plen = strlen(pattern);
		slen = strlen(str);
		if(!plen&&!slen)
			return true;
		else if(slen&&!plen)
			return false;
		else if(!slen&&plen%2==1)
			return false;
		else if(!slen){
			for(int i=1;i<plen;i+=2)
				if(pattern[i]!='*')
					return false;
			return true;
		}
		else{//都不空
			if(pattern[1]!='*')
			{
				if(str[0]==pattern[0]||pattern[0]=='.')
					return match(str+1,pattern+1);
				else
					return false;
			}
			else{
				if(str[0]==pattern[0]||pattern[0]=='.')
				{
					return match(str,pattern+2) || match(str+1,pattern);
				}
				else
					return match(str,pattern+2);
			}
		}
    }
};
int main(){

	char a[] = "a";
	char b[] = "ab*a";
	Solution s;
	cout<<s.match(a,b);
	return 0;
}
