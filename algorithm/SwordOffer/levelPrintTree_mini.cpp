/*=========================================================
> File Name: SwordOffer/levelPrintTree_mini.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月06日 星期六 23时50分12秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};
//class Solution {
//public:
    //bool BalancedTreeDepth(TreeNode* pRoot, int *depth)
    //{
        //if(pRoot)
        //{
            //int ldepth,rdepth;
            //bool lbalance = BalancedTreeDepth(pRoot->left,&ldepth);
            //bool rbalance = BalancedTreeDepth(pRoot->right,&rdepth);
            //if(!lbalance||!rbalance)
                //return false;
            //ldepth ++;
            //rdepth ++;
            
            //if(ldepth>rdepth)
            //{
                //*depth = ldepth;
                //return ((ldepth-rdepth)>1)?false:true;
            //}
            //else
            //{
                //*depth = rdepth;
                //return ((rdepth-ldepth)>1)?false:true;
            //}
        //}
        //else
        //{
            //*depth = 0;
            //return true;
        //}
    
    //}
    //bool IsBalanced_Solution(TreeNode* pRoot) {
        //int depth;
        //return BalancedTreeDepth(pRoot, &depth);
        
    //}
//};
//class Solution {
//public:
    //vector<int> PrintFromTopToBottom(TreeNode* root) {
        //queue<TreeNode*> q;
        //vector<int> v;
        //TreeNode *p;
        //q.push(root);
        //while(!q.empty())
        //{
            //p = q.front();
            //v.push_back(p->val);
            //q.pop();
            //if(p->left)
                //q.push(p->left);
            //if(p->right)
                //q.push(p->right);
            
        //}
        //return v;

    //}
//};
/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
bool cmp(vector<int> &a, vector<int> &b)
{
	return a.size()>b.size();
}
class Solution {
public:
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
        // 后序遍历，入栈出栈的同时记录当前栈中数据的总和。当到子节点的时候判断。
		stack<TreeNode*> s;
		vector<int> numStack;
		vector<vector<int> > result;
		int sum = 0;
		TreeNode *p = root, *last = NULL;
			while(p||!s.empty())
			{
				while(p)
				{
					s.push(p);
					numStack.push_back(p->val);
					sum += p->val;
					p = p->left;
				}

				p = s.top();
				if(p->right&&p->right!=last)
					p = p->right;
				else
				{
					if(sum==expectNumber&&!p->left&&!p->right&&numStack.size())
						result.push_back(numStack);
					sum -= p->val;
					s.pop();
					numStack.pop_back();
					last = p;
					p = NULL;
				}
			}

			sort(result.begin(),result.end(),cmp);
		return result;
        
    }
};
int main(){

	TreeNode *r,*p;
	r = new TreeNode(0);
	r->left = new TreeNode(1);
	r->right = new TreeNode(2);
	r->left->left = new TreeNode(3);
	r->left->right = new TreeNode(9);
	r->right->left = new TreeNode(5);
	r->right->right = new TreeNode(6);

	p = r->right;
	p->left->left = new TreeNode(7);
	p->left->right = new TreeNode(2);
	p->left->right->left = new TreeNode(1);
	p->right->left = new TreeNode(2);
	p->right->right = new TreeNode(10);

	Solution s;
	vector<vector<int>> v = s.FindPath(r,10);
	for(int i=0;i<v.size();i++)
	{
		for(int j=0;j<v[i].size();j++)
			cout<<v[i][j]<<' ';
		cout<<endl;
	}
	
	return 0;
}
