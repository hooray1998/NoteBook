/*=========================================================
> File Name: SwordOffer/cloneComplexList.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月08日 星期一 21时23分11秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
class Node{
	public:
		int from;
		int to;
		struct RandomListNode *newnode;
		Node(int f, int t):from(f),to(t){}
};
bool cmp(Node &a, Node &b)
{
	return a.to<b.to;
}

class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
		vector<Node> infoList;
		if(!pHead)
			return NULL;

		//1. 根据next申请链表空间
		int len=1;
		struct RandomListNode *newp,*newhead, *p=pHead, *q;
		newhead = newp = new struct RandomListNode(p->label);
		while(p->next)
		{
			++len;
			newp->next =  new struct RandomListNode(p->next->label);
			newp = newp->next;
			p = p->next;
		}
		newp->next = NULL;

		//2.记录第i个节点指向第几个节点
		int from=0,to=len;
		p = pHead;
		while(p)
		{
			q = p->random;
			while(q)
			{
				--to;
				q = q->next;
			}
			//cout<<"from:"<<from<<" to:"<<to<<endl;
			infoList.push_back(Node(from,to));
			++from;
			to = len;
			p = p->next;
		}
		//3.存储from的newlist的node的地址
		p = newhead;
		from = 0;
		while(p)
		{
			infoList[from].newnode = p;
			++from;
			p = p->next;
		}

		//for(int i=0;i<infoList.size();i++)
			//cout<<infoList[i].newnode->label<<' '<<infoList[i].from<<' '<<infoList[i].to<<endl;

		//4. 通过to的值排序infolist
		sort(infoList.begin(),infoList.end(),cmp);

		//for(int i=0;i<infoList.size();i++)
			//cout<<infoList[i].newnode->label<<' '<<infoList[i].from<<' '<<infoList[i].to<<endl;

		//5. 从前往后依次赋值
		to = 0;
		from = 0;
		p = newhead;
		while(p)
		{
			while(to<len&&from==infoList[to].to)
			{
				infoList[to].newnode->random = p;
				++to;
			}
			p = p->next;
			++from;
		}

		return newhead;
    }
};
int main(){
	struct RandomListNode *head,*p1,*p2, *q;
	head = p1 = new struct RandomListNode(0);
	for(int i=1;i<7;i++)
	{
		p1->next = new struct RandomListNode(i);
		p1 = p1->next;
	}
	p1->next = NULL;

	//init random
	int to[7] = {2,0,4,5,1,3,6};
	p1 = head;
	for(int i=0;i<7;i++)
	{
		int ran = to[i];
		q = head;
		while(ran--)
		{
			q = q->next;
		}
		p1->random = q;
		p1 = p1->next;
	}

	Solution s;
	p2 = s.Clone(head);

	while(p2)
	{
		cout<<p2->label<<" random:"<<p2->random->label<<endl;
		p2 = p2->next;
	}

	return 0;
}
