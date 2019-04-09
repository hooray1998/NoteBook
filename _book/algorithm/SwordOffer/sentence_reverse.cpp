/*************************************************************************
    > File Name: sentence_reverse.cpp
    > Author:hooray
    > Mail:hoorayitt@gmail.com 
    > Created Time: 2019年04月01日 星期一 22时43分12秒
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    string ReverseSentence(string str) {
        int len = str.length();
        char temp;
        for(int i=0;i<len/2;i++)
        {
            temp = str[i];
            str[i] = str[len-1-i];
            str[len-1-i] = temp;
        }
        int start = 0, end = 0;
        bool findblock = false;
        for(int i=0;i<=len;i++)
        {
            if(str[i]==' '||i==len)
            {
                if(!findblock)
                {
                    findblock = true;
                    end = i;
					for(int i=start;i<(start+end)/2;i++)
					{
						temp = str[i];
						str[i] = str[start+end-1-i];
						str[start+end-1-i] = temp;
					}
                }
                start = i+1;
            }
            else if(findblock)
                findblock = false;
            
        }
		return str;
    }
};
int main(){

	Solution s;
	string str = "dog.";
	cout<<s.ReverseSentence(str);
	return 0;
}
