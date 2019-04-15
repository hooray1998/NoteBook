/*=========================================================
> File Name: MyNutStore/Notes/algorithm/SwordOffer/uglyNumber.cpp
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月15日 星期一 14时00分02秒
> =======================================================*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int GetUglyNumber_Solution(int index) {
        // 0-6的丑数分别为0-6
        if(index < 7) return index;
        //p2，p3，p5分别为三个队列的指针，newNum为从队列头选出来的最小数
		//index:    1  2  3  4  5  6  7  8
		//array:    1  2  3  4  5  6  8  9
		//   x2:    2  4  6  8 10 12 16 18  p2记录队列头的索引值
		//   x3:    3  6  9 12 15 18 24 27  p3记录队列头的索引值
		//   x5:    5 10 15 20 25 30 35 40  p5记录队列头的索引值
		//   可以看出x3队列头的元素就等于arr的第p3个元素乘3
        int p2 = 0, p3 = 0, p5 = 0, newNum = 1;
        vector<int> arr;
        arr.push_back(newNum);
        while(arr.size() < index) {
            //选出三个队列头最小的数
            newNum = min(arr[p2] * 2, min(arr[p3] * 3, arr[p5] * 5));
            //这三个if有可能进入一个或者多个，进入多个是三个队列头最小的数有多个的情况
            if(arr[p2] * 2 == newNum) p2++;
            if(arr[p3] * 3 == newNum) p3++;
            if(arr[p5] * 5 == newNum) p5++;
            arr.push_back(newNum);
        }
        return newNum;
    }
};
int main(){
	Solution s;
	cout<<s.GetUglyNumber_Solution(7);

	return 0;
}
