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
public:
    char* Serialize(TreeNode *root) {    
        
    }
    TreeNode* Deserialize(char *str) {
		const char *seq = ",";
		char *p = strtok(str,seq);
		TreeNode *t= new TreeNode(0);
		stack<TreeNode*> s;

		bool left = true;
		while(p)
		{
			if(*p=='#')
			{
				if(left)
				{
					left = false;
					t->left = NULL;
				}
				else
				{
					t->right = NULL;
					t = s.top();
					s.pop();
				}
			}
				//cout<<"NULL"<<endl;
			else
			{
				if(left)
				{
					t->left = new TreeNode(atoi(p));
					s.push(t);
					t = t->left;
				}
				else
				{
					t->right = new TreeNode(atoi(p));
					s.push(t);
					t = t->right;
					left = true;
				}
			}
				//cout<<atoi(p)<<'-'<<endl;
			p = strtok(NULL,seq);
		}

    
    }
};
int main(){
	Solution s;
	char str[] = "1,2,#,3,#,#,4,5,#,#,6,#,7,#,#";
	s.Deserialize(str);

	return 0;
}
