/*=========================================================
> File Name: SwordOffer/deleteDuplication.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月06日 星期六 22时03分03秒
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
    ListNode* deleteDuplication(ListNode* pHead)
    {
        ListNode *p, *q, *r;
        p = new ListNode(0);
        p->next = pHead;
        r = p;
        int pre;
        if(p->next)
        {
            pre = p->next->val;//初始化

            while(p->next->next)
            {
                if(p->next->next->val == pre)
                {
                    //先删第一个
                    q = p->next;
                    p->next = p->next->next;
                    delete q;
                    //再删后n-1个重复的
                    while(p->next&&p->next->val == pre)
                    {
                            q = p->next;
                            p->next = p->next->next;
                            delete q;
                    }
                }
                else
                    p = p->next;
				if(!p->next)
					break;
				pre = p->next->val;
            }
        }
            
        return r->next;
    }
};
int main(){
	ListNode *p,*r;
	p = new ListNode(0);
	r = p;
	p->next = new ListNode(1);
	p = p->next;
	p->next = new ListNode(1);
	p = p->next;
	p->next = new ListNode(2);
	p = p->next;
	p->next = new ListNode(2);
	p = p->next;
	p->next = new ListNode(3);
	p = p->next;
	p->next = NULL;

	p = r;
	while(p)
	{
		cout<<p->val;
		p = p->next;
	}
	cout<<endl;
	Solution s;
	p = s.deleteDuplication(r);

	while(p)
	{
		cout<<p->val;
		p = p->next;
	}
	cout<<endl;
	return 0;
}
