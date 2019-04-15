/*=========================================================
> File Name: word_in_matrix.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月13日 星期六 00时04分15秒
> =======================================================*/

#include<bits/stdc++.h>
#define DEBUG
using namespace std;
class Solution{
private:
	char *mat;
	int directory[4];
	bool flag;
	vector<int> snake;
	char *target;
	int matlen;
	int len;
	int col;

public:
    bool hasPath(char* matrix, int rows, int cols, char* str)
    {
        
		mat = matrix;
		col = cols;
		target = str;
		flag = false;
		matlen = strlen(matrix);
		len = strlen(str);
		if(!len||!matlen)
			return true;//black
		for(int i=0;i<len;i++)
            snake.push_back(0);
		directory[0] = -col;
		directory[1] = 1;
		directory[2] = col;
		directory[3] = -1;

		for(int i=0;i<matlen;i++)
		{
			if(mat[i]!=target[0])
				continue;
			snake[0] = i; 
			Try(1);
			if(flag)
			{
				break;
			}
		}
		return flag;
    }
	void Try(int l){
		if(l == len) flag = true;
		else{
			for(int i=0;i<4;i++)
			{
				if(i==0&&snake[l-1]<col) continue;
				else if(i==1&&snake[l-1]%col==col-1) continue;
				else if(i==2&&snake[l-1]>=(matlen-col)) continue;
				else if(i==3&&snake[l-1]%col==0) continue;
				snake[l] = snake[l-1]+directory[i];
				//cout<<"dir = "<<i<<endl;
				if(ok(l))
				{
					Try(l+1);
					if(flag) break;
				}
			}
		}
	}
	bool ok(int l)
	{

		set<int> s;
		for(int i=0;i<=l;i++)
		{
			if(mat[snake[i]]!=target[i])
				return false;
			s.insert(snake[i]);
		}
		if(s.size() != l+1)
			return false;
		return true;
	}
};

int main(){
	char mat[] = "abcesfcsadee";
	char target[] = "asfbc";
	Solution s;
	if(s.hasPath(mat, 3, 4, target))
		cout<<"find path"<<endl;

	return 0;
}
