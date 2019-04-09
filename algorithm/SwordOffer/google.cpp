/*************************************************************************
    > File Name: google.cpp
    > Author:hooray
    > Mail:hoorayitt@gmail.com 
    > Created Time: 2019年04月01日 星期一 15时53分49秒
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;
class Solution
{
public:
    char output='#';
    vector<char> cs;
  //Insert one char from stringstream
    void Insert(char ch)
    {
		bool fin = false;
		for(vector<char>::iterator i=cs.begin();i<cs.end();i++)
			if(*i == ch)
			{
				cs.erase(i);
				fin = true;
				break;
			}
		if(!fin)
			cs.push_back(ch);

        if(cs.size()==0)
            output = '#';
		else
			output = cs.front();
    }
  //return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
        return output;
    }

};
int main(){

	Solution s;
	s.Insert('B');
	s.Insert('a');
	s.Insert('b');
	s.Insert('y');
	s.Insert('B');
	s.Insert('a');
	s.Insert('b');
	s.Insert('y');

	int i('\0');
	cout<<i;
	return 0;
}
