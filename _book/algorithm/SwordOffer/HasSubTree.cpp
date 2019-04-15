/*=========================================================
> File Name: SwordOffer/HasSubTree.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月08日 星期一 20时51分14秒
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
	bool equal(TreeNode* pRoot1, TreeNode* pRoot2)
	{
		if(!pRoot2)
			return true;
		else if(!pRoot1&&pRoot2)
			return false;

		if(pRoot1->val==pRoot2->val)
			return equal(pRoot1->left,pRoot2->left)&&equal(pRoot1->right,pRoot2->right);
		else
			return false;
	}
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
		if(!pRoot1||!pRoot2)
            return false;
        return equal(pRoot1,pRoot2)
			||HasSubtree(pRoot1->left,pRoot2)
			||HasSubtree(pRoot1->right,pRoot2);
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


	p = new TreeNode(6);
	p->left = new TreeNode(9);
	p->right = new TreeNode(10);

	Solution s;

	cout<<s.HasSubtree(r,p);

	return 0;
}
