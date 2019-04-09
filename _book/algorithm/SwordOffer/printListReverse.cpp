/*************************************************************************
    > File Name: printListReverse.cpp
    > Author:hooray
    > Mail:hoorayitt@gmail.com 
    > Created Time: 2019年03月29日 星期五 12时20分47秒
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;

vector<int> r;



r.push_front(1);


/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        int front=0;
        stack<TreeNode*> s;
        int len = pre.size();
        bool *use = new bool[len];
        for(int i=0;i<len;i++)
            use[i] = false;
        int cur = 0;
        struct TreeNode *head;
        struct TreeNode *node = new struct TreeNode(0);



        return head;

    }
    TreeNode * makeTree(int prestart,int preend,int vinstart,int vinend)
};




public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        int front=0;
        stack<TreeNode*> s;
        int len = pre.size();
        bool *use = new bool[len];
        for(int i=0;i<len;i++)
            use[i] = false;
        int cur = 0;
        struct TreeNode *head;
        struct TreeNode *node = new struct TreeNode(0);
        bool haveleft = true;
        bool haveright;
        for(;cur<len;cur++){
            int curVal = pre.at(cur);
            if(haveleft)
            {
                node->left = new struct TreeNode(curVal);
                node = node->left;
                s.push(node);
            }
            else if(haveright)
            {
                node->right = new struct TreeNode(curVal);
                node = node->right;
                s.push(node);
            }
            else{
                node = s.top();
                s.pop();
            }


            if(cur==0)
                head = node;
            haveleft = false;
            for(int j=front;j<len;j++){
                if(!use[j]&&vin.at(j)!=curVal)
                    haveleft = true;
                else if(vin.at(j)==curVal){
                    use[j] = true;
                    break;
                }
            }
            if(!haveleft){

            }
            haveright = false;
            for(int j=len;j>=front;j--){
                if(!use[j]&&vin.at(j)!=curVal)
                    haveright = true;
                else if(vin.at(j)==curVal){
                    use[j] = true;
                    break;
                }
            }


        }


        return head;

    }
