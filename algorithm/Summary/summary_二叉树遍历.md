# 二叉树遍历

```cpp
//先序遍历T
Status PreOrderTraverse(BiTree T,Status(*Visit)(TElemType e) )
{
	if(T)
	{
		if(Visit(T->data))
			if(PreOrderTraverse(T->lchild,Visit))
				if(PreOrderTraverse(T->rchild,Visit))
				return 1;
		return 0;
	}
	return 1;
}
//中序遍历T
Status InOrderTraverse(BiTree T,Status(*Visit)(TElemType e) )
{
	if(T)
	{
		if(InOrderTraverse(T->lchild,Visit))
			if(Visit(T->data))
				if(InOrderTraverse(T->rchild,Visit))
				return 1;
		return 0;
	}
	return 1;
}

//

////后序遍历T
Status PostOrderTraverse(BiTree T,Status(*Visit)(TElemType e) )
{
	if(T)
	{
		if(PostOrderTraverse(T->lchild,Visit))
			if(PostOrderTraverse(T->rchild,Visit))
				if(Visit(T->data))
				return 1;
		return 0;
	}
	return 1;
}

//

```

## 非递归遍历

``` cpp


////层序遍历T
Status LeverOrderTraverse(BiTree T,Status(*Visit)(TElemType e))
{
	if(!T) return 0;
	queue<BiTree> Q;
	BiTree p = NULL;
	Q.push(T);
	while(!Q.empty())
	{
		p = Q.front();
		Q.pop();
		if(!Visit(p->data)) return 0;
		
		if(p->lchild) 
			Q.push(p->lchild);
		if(p->rchild)
			Q.push(p->rchild);
				
	}
	
}


//先序遍历--非递归
int PreOrderTraverse2(BiTree T,int (*visit)(TElemType e))
{
	stack <BiTree> S;
	BiTree p = T;
	while(p || !S.empty())
	{
		if(p)
		{
			if(!visit(p->data)) return 0;  //错误返回
			S.push(p->rchild);
			p=p->lchild;
		}
		else 
		{
			p = S.top();
			S.pop();
		}
	  
	}
	return 1; //正常返回

}

//中序遍历--非递归
int InOrderTraverse2(BiTree T,int (*visit)(TElemType e))
{
	stack <BiTree> S;
	BiTree p = T;
	while(p || !S.empty())
	{
		if(p)
		{
			S.push(p);	
			p=p->lchild;
		}
		else 
		{
			p = S.top();
			S.pop();
			if(!visit(p->data)) return 0;  //错误返回
			p=p->rchild;
		}
	}
	return 1;   //正常返回
}
int PostOrderTraverse2(BiTree T,int (*Visit)(TElemType e)) 
{
	BiTree last = NULL;
	BiTree p = T;
	stack<BiTree> S;
	while(p||!S.empty())
	{
		while(p)
		{
			S.push(p);
			p = p->lchild;
		}
		p = S.top();
		if(p->rchild&&p->rchild!=last)
			p = p->rchild;
		else
		{
			if(!Visit(p->data)) return 0;
			S.pop();
			last = p;
			p = NULL;//为了下一次的循环 ,因为p的左子树已经遍历过了. 
		} 
	
	}
	return 1;
```
