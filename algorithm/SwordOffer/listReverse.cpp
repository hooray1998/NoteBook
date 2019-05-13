/*************************************************************************
    > File Name: listReverse.cpp
    > Author:hooray
    > Mail:hoorayitt@gmail.com 
    > Created Time: 2019年03月29日 星期五 18时28分49秒
 ************************************************************************/

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
        if(!q->next)
        {
            q->next = p;
            p = q;
            return p;
        }
        else
        {
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

int main()
{

	ListNode *p,*head;
	head = new ListNode;

}
