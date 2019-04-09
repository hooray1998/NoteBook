/*************************************************************************
    > File Name: SwordOffer/printMatrix.cpp
    > Author:hooray
    > Mail:hoorayitt@gmail.com 
    > Created Time: 2019年03月31日 星期日 00时14分02秒
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;
	int Sum_Solution(int n) {
			if(n==1)
				return 1;
			else
		return Sum_Solution(n-1)+n;
	}

int a[9] = {1,2,3,4,2,5,2,3,2};
int len = 9;
int search(int i){
	int k = a[i];
	int count = 1;
	int index = i+1;
	while(count!=0&&index<len)
	{
		if(a[index]!=k)
			count --;
		else
			count ++;
		index ++;
	}
	if(count==0)
		return search(index);
	else
		return k;
}
class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix) {
        int vcount = matrix.size()-1;
        int hcount = matrix.at(0).size();
        bool hdir = true;
        bool vdir = true;
        int row = 0,clo=-1;
        
        vector<int> result;
        while(true)
        {
			if(!hcount)
				break;
            for(int i=0;i<hcount;i++)
            {
                if(hdir)
                    clo++;
                else
                    clo--;
                result.push_back(matrix[row][clo]);
            }
            hcount --;
            hdir=!hdir;
			if(!vcount)
				break;
            for(int i=0;i<vcount;i++)
            {
                if(vdir)
                    row++;
                else
                    row--;
                result.push_back(matrix[row][clo]);
            }
            vcount --;
            vdir=!vdir;
        }
        return result;

    }
};
int main(){
	/*
	Solution s;
	vector<vector<int>> m;
	vector<int> n1;
	vector<int> n2;
	vector<int> n3;

	for(int i=1;i<=5;i++)
	{
		n1.push_back(i);
		n2.push_back(i+5);
		n3.push_back(i+10);
	}
	m.push_back(n1);
	m.push_back(n2);
	m.push_back(n3);


	s.printMatrix(m);

	string str="abcXYZdef";
	int n = 3;
	int len = str.length();
	n %= len;
	n = len-n;
	int t;
	for(int i=0;i<len/2;i++)
	{
		t = str[i];
		str[i] = str[len-1-i];
		str[len-1-i] = t;
	}
	for(int i=0;i<n/2;i++)
	{
		t = str[i];
		str[i] = str[n-i-1];
		str[n-i-1] = t;
	}
	for(int i=n;i<(len+n)/2;i++)
	{
		t = str[i];
		str[i] = str[len+n-1-i];
		str[len+n-1-i] = t;
	}

	cout<<Sum_Solution(5);

	*/

	//cout<<endl;
	//int k = search(0);
	//int count = 0;
	//int index = 0;
	//while(index<len)
	//{
		//if(a[index]!=k)
			//count --;
		//else
			//count ++;
		//index ++;
	//}
	//if(count>0)
		//cout << k;
	//else
		//cout<<0;
	vector<int> numbers{1,2,2,5,2};

	int len = numbers.size();
        if(len==0)
            return 0;
        int index = 0;
        int count;
        int k;
        bool flag = false;
        while(!flag)
        {
            count = 1;
            k = numbers[index];
            while(count!=0&&index<len)
            {
                if(a[index]!=k)
                    count --;
                else
                    count ++;
                index ++;
            }
            if(count!=0)
            {
                flag = true;
            }
        }
        count = 0;
        index = 0;
        while(index<len)
        {
            if(a[index]!=k)
                count --;
            else
                count ++;
            index ++;
        }
        if(count!=0)
		cout<<k<<"------";
        else
		cout<<0<<"------";


	return 0;
}
