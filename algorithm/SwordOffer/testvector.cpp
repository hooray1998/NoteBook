/*=========================================================
> File Name: MyNutStore/Notes/algorithm/SwordOffer/testvector.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月09日 星期二 09时54分38秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;

int main(){
	vector<int> v;
	v.push_back(1);
	v.push_back(3);
	v[0] += 7;
	for(int i=0;i<v.size();i++)
		cout<<' '<<v[i];

	return 0;
}
