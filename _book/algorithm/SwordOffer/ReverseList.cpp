/*=========================================================
> File Name: ./ReverseList.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月02日 星期二 22时35分45秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};
class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        ListNode *p, *q, *r;
        p = pHead;
        if(!p)
            return pHead;
        q = p->next;
		if(!q)
            return pHead;

        if(!q->next)
        {
            q->next = p;
			p->next = NULL;
            p = q;
            return p;
        }
        else
        {
			p->next = NULL;
            while(q->next!=NULL)
            {
                r = q->next;
                q->next = p;
                p = q;
                q = r;
            }
            q->next = p;
            p = q;
        }
        return p;

    }
};
int main(){
	ListNode *p,*q,*head;
	p = head = new struct ListNode(0);
	p->next = NULL;
	int n = 0;

	while(n--)
	{
		q = new struct ListNode(5-n);
		p->next = q;
		q->next = NULL;
		p = p->next;
	}

	cout<<"start"<<endl;
	p = head;
	while(p)
	{
		cout<<p->val<<" ";
		p = p->next;
	}
	cout<<endl<<"end"<<endl;

	Solution s;
	ListNode *k = s.ReverseList(head);

	p = k;
	while(p)
	{
		cout<<p->val<<" ";
		p = p->next;
	}

	return 0;
}
