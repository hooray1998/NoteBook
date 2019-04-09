/*=========================================================
> File Name: SwordOffer/VerifySequeueOfBST.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月07日 星期日 14时08分26秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool OK_inChildTree(vector<int> &v,int s, int e)
    {
        if(e-s<2) return true;
        int i,j;
        int root = v[e];
        for(i=s;i<e&&v[i]<root;i++);
        for(j=e-1;j>=s&&v[j]>root;j--);
        if(i-j==1)
            return OK_inChildTree(v,s,i-1)&&OK_inChildTree(v,j+1,e-1);
        else
            return false;
    }
    bool VerifySquenceOfBST(vector<int> sequence) {
        return OK_inChildTree(sequence,0,sequence.size()-1);
    }
};
int main(){

	vector<int> v={1,2,4,0,3};
	Solution s;
	cout<<s.VerifySquenceOfBST(v);


	return 0;
}
