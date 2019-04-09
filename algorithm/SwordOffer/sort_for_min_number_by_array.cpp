/*=========================================================
> File Name: algorithm/SwordOffer/sort_for_min_number_by_array.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月07日 星期日 23时43分34秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;
bool cmp(int a,int b)
{
	stringstream ssa,ssb;
	string sa,sb;
	ssa<<a;
	ssa>>sa;
	ssb<<b;
	ssb>>sb;
	sa += sb;
	sb += sa;
	return sa<sb;
	
}
class Solution {
public:
    
    string PrintMinNumber(vector<int> numbers) {
		sort(numbers.begin(),numbers.end(),cmp);
		stringstream ss;
		for(int i=0;i<numbers.size();i++)
			ss<<numbers[i];
		return ss.str();
    }
};
int main(){
	Solution s;
	vector<int> v={3,32,321};
	cout<<s.PrintMinNumber(v);

	return 0;
}
