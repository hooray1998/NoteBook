/*************************************************************************
    > File Name: Matrix2.cpp
    > Author:hooray
    > Mail:hoorayitt@gmail.com 
    > Created Time: 2019年04月01日 星期一 15时21分18秒
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;

class Test{
	public:
		char s=1;
		void output(){
			int d= s;
			cout<<"ddd"<<d<<"ddd"<<endl;

		}
};
int main(){
	vector<int> A;
	for(int i=0;i<5;i++)
		A.push_back(i+1);
	vector<int> B;
	int len = A.size();
	int sum = 1;
	for(int i=0;i<len;i++)
	{
		B.push_back(sum);
		sum *= A.at(i);
	}
	sum = 1;
	for(int i=len-1;i>-1;i--)
	{
		B.at(i) *= sum;
		sum *= A.at(i);
	}

	for(int i=0;i<len;i++)
		cout<<A.at(i)<<" "<<B.at(i)<<endl;

	cout<<"helloworld";
	string s="helloworld";
	sum = 0;
	for(int i=0;i<s.length();i++)
	{
		sum ^= s[i];
		cout<<sum<<endl;
	}
	cout<<"set test"<<endl;

	set<char> cs;
	cs.insert('a');
	cs.insert('a');
	cs.erase('a');
	cout<<cs.size();
	char a  = 'a';
	//set<char>::iterator i = *cs.find(a);
	cout<<('a'==*cs.find(a));
	//cout<<cs.find('a')<<"  "<<cs.find('b');
	return 0;
}
