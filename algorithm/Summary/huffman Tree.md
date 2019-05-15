```cpp
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<iostream>
#include<conio.h>
#include<time.h>
 
using namespace std; 
typedef struct{
 unsigned int weight;
 unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;


void Select(HuffmanTree ht, int num, unsigned int &s1, unsigned int &s2)
{
	
 //初始化s1,s2; 
 s1 = 0;
 s2 = 0; 
 for(int i=1;i<=num;i++)
 {
  if(ht[i].parent == 0)
  {
   if(s1==0)
   s1 = i;
   else 
   {
    s2 = i;
    break;
   }  
  } 
 }
	

	
 for(int i=1;i<=num;i++)
 {
  unsigned int max = (ht[s1].weight>ht[s2].weight)?ht[s1].weight:ht[s2].weight;
  if(ht[i].parent == 0)
  if(ht[i].weight<max&&i!=s1&&i!=s2) 
  { 
   if(ht[s1].weight==max) s1 = i;
   else s2 = i;
  }
 }
	
// printf("Select %d %d\n",s1,s2);

}
void ShowHuffmanTree(HuffmanTree HT,int n)
{
 putchar(10);
 for(int i=1;i<=(2*n-1);i++)
 {
  printf("%-3d%-4d%-4d%-4d%-4d\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);  
  } 
 putchar(10);
	
 } 



void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC,int *w, int n)
{
 if(n<=1) return ; 
 int m = 2*n-1;
 HT = (HuffmanTree)malloc( (m+1)*sizeof(HTNode));
	
 HuffmanTree p;
 int i;
 for(p = HT+1,i=1;i<=n;i++,p++)
 {
  p->weight = w[i];
  p->parent = 0;
  p->lchild = 0;
  p->rchild = 0;
 }
// *p = {*w,0,0,0};
 for(;i<=m;i++,p++)
 {
  p->weight = 0;
  p->parent = 0;
  p->lchild = 0;
  p->rchild = 0;
 }
// *p = {0,0,0,0};
	
	
 unsigned int s1,s2;
 //组建HuffmanTree
 for(i=n+1;i<=m;i++)
 {
  
// ShowHuffmanTree(HT,n);
// getch();
  Select(HT,i-1,s1,s2);
  HT[s1].parent = i;
  HT[s2].parent = i;
  HT[i].lchild = s1;
  HT[i].rchild = s2;
  HT[i].weight = HT[s1].weight + HT[s2].weight;

 }

	
 //从叶子结点开始逆向求每个字符的Huffman编码
 HC = (HuffmanCode)malloc((n+1)*sizeof(char*));//分配n个字符编码的头指针向量
 char *cd = (char *)malloc(n*sizeof(char));
 cd[n-1] = '\0';
	
 int start;
 for(i=1;i<=n;i++)
 {
  start = n-1;
  
  int c,f;
  for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
   if(HT[f].lchild == c) cd[--start] = '0';//if "0"
   else cd[--start] = '1';
  HC[i] = (char*)malloc((n-start)*sizeof(char));
  strcpy(HC[i],&cd[start]);
  
  } 
 free(cd);
	
	
  
 } 
 
 
 int main()
 {
  HuffmanTree HT;
  HuffmanCode HC;
  int w[100],n;
  puts("输入总数");
  scanf("%d",&n);
  puts("依次输入");

 for(int i=1;i<=n;i++)
  {
   scanf("%d",&w[i]); 
  }
  HuffmanCoding(HT,HC,w,n);
  
  for(int i=1;i<=n;i++)
 printf("%-3d 's Huffmancode is : %s\n",w[i],HC[i]);  
  
  
 }
 
 

```