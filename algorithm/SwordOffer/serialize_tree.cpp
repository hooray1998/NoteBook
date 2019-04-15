/*=========================================================
> File Name: MyNutStore/Notes/algorithm/SwordOffer/serialize_tree.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月09日 星期二 10时34分42秒
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
private:
	const char *seq = ",";
	char *p;
public:
    char* Serialize(TreeNode *root) {    
		if(root == NULL)
		   return NULL;
		string str;
		Serialize2(root, str);
		char *ret = new char[str.size() + 1];
		unsigned long i=0;
		for(; i < str.size(); i++){
			ret[i] = str[i];
		}
		ret[i] = '\0';
		return ret;
    }
	void Serialize2(TreeNode *root, string& str){
		if(root == NULL){
			str += "#,";
			return ;
		}
		string r = to_string(root->val);
		str += r;
		str += ',';
		Serialize2(root->left, str);
		Serialize2(root->right, str);
	}

    TreeNode* Deserialize(char *str) {
		this->p = strtok(str,seq);
		return Create();
	}
	//char str[] = "1,2,#,3,#,#,4,#,#";
	TreeNode* Create(){
		if(p)
		{
			string s(p);
			if(s=="#")
			{
				return NULL;
			}
			else{
				TreeNode *t= new TreeNode(atoi(s.c_str()));
				p = strtok(NULL,seq);
				t->left  = Create();
				p = strtok(NULL,seq);
				t->right = Create();
				return t;
			}
		}
		else
			return NULL;
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
	//char str[] = "1,2,#,3,#,#,4,#,#";
	char str[] = "1,2,#,3,#,#,4,5,#,#,6,#,7,#,#,";
	//vector<vector<int>> v = s.Print(r);

	cout<<s.Serialize(s.Deserialize(str));


	return 0;
}
