/*=========================================================
> File Name: SwordOffer/levelPrintTree.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月06日 星期六 21时27分41秒
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
class Solution {
public:
        vector<vector<int> > Print(TreeNode* pRoot) {
            stack<TreeNode*> q1,q2;
            vector<int> v;
            vector<vector<int>> result;
            TreeNode *p;
            p = pRoot;
            q1.push(p);
			if(p)
            while(!q1.empty()||!q2.empty())
            {
                v.clear();
                while(!q1.empty())
                {
                    p = q1.top();
                    q1.pop();
                    v.push_back(p->val);
                    if(p->left)
                        q2.push(p->left);
                    if(p->right)
                        q2.push(p->right);
                }
                if(v.size())
                    result.push_back(v);
                v.clear();
                while(!q2.empty())
                {
                    p = q2.top();
                    q2.pop();
                    v.push_back(p->val);
                    if(p->right)
                        q1.push(p->right);
                    if(p->left)
                        q1.push(p->left);
                }
                if(v.size())
                    result.push_back(v);
            }
            
            return result;
        
        }
    
};
int main(){
	TreeNode *r,*p;
	r = new TreeNode(0);
	r->left = new TreeNode(1);
	r->right = new TreeNode(2);
	r->left->left = new TreeNode(3);
	r->left->right = new TreeNode(4);
	r->right->left = new TreeNode(5);
	r->right->right = new TreeNode(6);

	p = r->right;
	p->left->left = new TreeNode(7);
	p->left->right = new TreeNode(8);
	p->right->left = new TreeNode(9);
	p->right->right = new TreeNode(10);
	Solution s;
	vector<vector<int>> v = s.Print(r);
	for(int i=0;i<v.size();i++)
	for(int j=0;j<v[i].size();j++)
		cout<<v[i][j];



	return 0;
}
