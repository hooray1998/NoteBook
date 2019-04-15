/*=========================================================
> File Name: ./KthNode.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月09日 星期二 23时07分56秒
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
    TreeNode* KthNode(TreeNode* pRoot, int k)
    {
        stack<TreeNode*> s;
        TreeNode *p = pRoot;
        int count=0;
        while(p||!s.empty())
        {
            if(p)
            {
                s.push(p);
                p = p->left;
            }
            else
            {
                p = s.top();
                s.pop();
                if(++count==k) return p;
                p = p->right;
                
            }
        }
    }

    
};
int main(){

	TreeNode *r,*p;
	//二叉搜索树
	r = new TreeNode(5);
	r->left = new TreeNode(3);
	r->right = new TreeNode(9);
	r->left->left = new TreeNode(1);
	r->left->right = new TreeNode(4);
	r->right->left = new TreeNode(7);
	r->right->right = new TreeNode(11);

	p = r->right;
	p->left->left = new TreeNode(6);
	p->left->right = new TreeNode(8);
	p->right->left = new TreeNode(10);
	p->right->right = new TreeNode(12);
	Solution s;
	cout<<s.KthNode(r,8)->val;
	return 0;
}
