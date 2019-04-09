/*=========================================================
> File Name: SwordOffer/TreeOfBST.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月07日 星期日 14时38分08秒
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
	void PrintFromTopToBottom(TreeNode* root) {
		stack<TreeNode*> s;
		TreeNode *p = root, *last = NULL;

		while(p||!s.empty())
		{
			while(p)
			{
				s.push(p);
				p = p->left;
			}

			p = s.top();
			if(p->right&&p->right!=last)
				p = p->right;
			else
			{
				cout<<p->val<<" ";
				s.pop();
				last = p;
				p = NULL;
			}
            
		}

	}
    TreeNode* Convert(TreeNode* pRootOfTree)
	{
		if(pRootOfTree)
		{
			Convert(pRootOfTree->left);
			Convert(pRootOfTree->right);
			TreeNode *l,*r,*p;
			l = pRootOfTree->left;
			if(l)
			{
				while(l->right)
					l = l->right;
				l->right = pRootOfTree;
				pRootOfTree->left = l;
			}

			r = pRootOfTree->right;
			if(r)
			{
				while(r->left)
					r = r->left;
				r->left = pRootOfTree;
				pRootOfTree->right = r;
			}

			p = pRootOfTree;
			while(p->left)
				p = p->left;
			return p;
		}
		else
			return NULL;

	}
};
/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
int main(){

	TreeNode *r,*p;
	/*
	 * 顺序二叉树
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
	*/

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
	//s.PrintFromTopToBottom(r);
	p = s.Convert(r);
	while(p->right)
	{
		cout<<p->val<<" ";
		p = p->right;
	}
	cout<<p->val<<" ";
	cout<<endl;
	while(p->left)
	{
		cout<<p->val<<" ";
		p = p->left;
	}
	cout<<p->val<<" ";
	return 0;
}
