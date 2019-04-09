/*=========================================================
> File Name: MyNutStore/Notes/algorithm/SwordOffer/split.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月09日 星期二 10时37分22秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;
//#include <string.h>
//#include <stdio.h>

int main(){
	char s[] = "a,b,c,d";
	const char *sep = ","; //可按多个字符来分割
	char *p;
	p = strtok(s, sep);//第一次使用参数s
	while(p){
		printf("%s\n", p);
		p = strtok(NULL, sep);//以后使用参数NULL
	}
	printf("\n");
	return 0;
}
//输出: a b c d
