/*=========================================================
> File Name: MyNutStore/Notes/algorithm/SwordOffer/movingCount.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月15日 星期一 13时55分19秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
private:
	set<string> s;
	int cnt;
	int k;
	int rows;
	int cols;

public:
    int movingCount(int threshold, int rows, int cols)
    {
		cnt = 0;
		this->k = threshold;
		this->rows = rows;
		this->cols = cols;

		for(int i=0;i<rows;i++)
			for(int j=0;j<cols;j++)
				Try(i,j);
		return cnt;
    }
	void Try(int x, int y){
		if(visit(x,y))
		{
			if(x>0)
				Try(x-1,y);
			if(y>0)
				Try(x,y-1);
			if(x<(rows-1))
				Try(x+1,y);
			if(y<(cols-1))
				Try(x,y+1);
		}
	}
	bool visit(int x, int y){
		char temp[20];
		sprintf(temp,"%d-%d",x,y);
		string str(temp);
		int sum = 0;
		for(int i=0;i<str.size();i++)
			if(str[i]!='-')
				sum += str[i]-'0';
		if(sum<=k)
		{
			s.insert(str);
			if(cnt==s.size()){//存在了
				return false;
			}
			else {
				cout<<str<<endl;
				cnt ++;
				return true;
			}
		}
		return false;

	}
};
int main(){
	Solution s;
	cout<<"res"<<s.movingCount(5, 10,10);

	return 0;
}
