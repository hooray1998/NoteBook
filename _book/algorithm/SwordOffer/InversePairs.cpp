/*=========================================================
> File Name: InversePairs.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月14日 星期日 22时16分53秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
	private:
		int cnt;
public:
    int InversePairs(vector<int> data) {
		cnt = 0;
		if(!data.empty())
			return MergeSort(&data, 0, data.size())%1000000007;//don't include end
		else
			return 0;
    }

	int MergeSort(vector<int> *data, int begin, int end){
//		cout<<"sort: ";
		//for(int i=begin;i<end;i++)
//			cout<<data->at(i)<<' ';
//		cout<<endl;
		if(end>begin+1)
		{
			int mid = (begin+end)/2;
			MergeSort(data, begin,mid);
			MergeSort(data, mid,end);
			MergeTwoList(data,begin,mid,end);
		}
		return cnt;
	}

	void MergeTwoList(vector<int> *data, int begin, int mid, int end){
		//arr1: begin -> mid
		//arr2: mid   -> end
		vector<int> tmp(end-begin);
		int index= end-begin-1;
		int p = mid-1;
		int q = end-1;

		while(p>=begin&&q>=mid)
		{
			if(data->at(p)>data->at(q))
			{
				tmp[index--] = data->at(p);
				cnt += q-mid+1;
				--p;
			}
			else
			{
				tmp[index--] = data->at(q);
				--q;
			}
		}
		while(p>=begin) tmp[index--] = data->at(p--);
		while(q>=mid) tmp[index--] = data->at(q--);
		++index;
//		cout<<index<<begin<<end<<endl;
		while(index<(end-begin))
		{
			(*data)[begin+index] = tmp[index];
			++index;
		}
		tmp.clear();
//		cout<<"merge: ";
		//for(int i=begin;i<end;i++)
//			cout<<data->at(i)<<' ';
//		cout<<endl;
	}
};
int main(){

	Solution s;
	vector<int> v={};
	cout<<"result:"<<s.InversePairs(v);
	return 0;
}
