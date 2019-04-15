/*=========================================================
> File Name: /home/itt/MyNutStore/Notes/algorithm/SwordOffer/IsNumeric.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月14日 星期日 23时57分35秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isNumeric(char* string)
    {
		int len = strlen(string);
		if(!len)
			return false;

		int index = 0;
		if(string[index] == '-') index++;
		else if(string[index] == '+') index++;

		if(string[index]>='0'&&string[index]<='9')
			while(index<len&&string[index]>='0'&&string[index]<='9') index++;

		if(string[index]=='.')
		{
			index++;
			if(string[index]>='0'&&string[index]<='9')
				while(index<len&&string[index]>='0'&&string[index]<='9') index++;
			else
				return false;
		}
		if(string[index]=='e'||string[index]=='E')
		{
			index++;
			if(string[index] == '-') index++;
			else if(string[index] == '+') index++;

			if(string[index]>='0'&&string[index]<='9')
				while(index<len&&string[index]>='0'&&string[index]<='9') index++;
			else
				return false;
		}
		if(index<len)
			return false;
		else
			return true;
        
    }

};
int main(){
	Solution s;
	char a[] = "-.1E22";
	cout<<s.isNumeric(a);
	float b = -000.123;
	cout<<b;


	return 0;
}
