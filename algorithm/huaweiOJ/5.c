/*=========================================================
> File Name: 5.c
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年11月03日 星期日 09时36分46秒
> =======================================================*/

#include<stdio.h>
#include<string.h>

short findNext(char *s, short *low, short *len){
	for(short i=(*len)-1;i>*low;i--){
		if(s[i]==s[*low])
			return i;
	}
	return -1;
}
void printS(char *s, short low, short high){
	putchar('>');
	for(short i=low;i<=high;i++){
		putchar(s[i]);
	}
	putchar(10);
}

char judgePalind(char *s, short low, short high){
	for(short step=1;step<=(high-low-1)/2;step++){
		if(s[low+step]!=s[high-step]){
			return 0;
		}
	}
	return 1;
}
char *longestPalindrome(char *s){
	short len = strlen(s);
	if(!len) return s;
	short max = 0, maxIndex = -1;
	short low=0, high=0;

	while(low<len-max){
		high = findNext(s,&low,&len);
		if(high != -1){
			do{
				if(1+high-low<=max){
					break;
				}
				else if(judgePalind(s,low,high)){
					if((1+high-low)> max){
						printS(s,low,high);
						max = 1+high-low;
						maxIndex = low;
					}
					break;
				}
				else{
					high = findNext(s,&low,&high);
				}
			}while(high != -1);
		}
		low ++;
	}

	if(max==0){
		s[1] = 0;
		return s;
	}
	else{
		s[maxIndex+max] = 0;
		return s+maxIndex;
	}

}

int main(){
	/*char s[] = "aaabaaaa";*/
	char s[] = "aaabaaaa";
	printf("result:%s\n",longestPalindrome(s));
	return 0;
}
