# -*- coding:utf-8 -*-
class Solution:
    # 返回[a,b] 其中ab是出现一次的两个数字
    def FindNumsAppearOnce(self, array):
        # write code here
        s = 0
        for value in array:
            s ^= value
        str_bin = '{:0>4b}'.format(s)
        loc = len(str_bin) - str_bin.rfind('1') - 1

        list1 = [i for i in array if (i>>loc)%2==1]
        list2 = [i for i in array if (i>>loc)%2==0]
        a = 0
        b = 0
        for value in list1:
            a ^= value
        for value in list2:
            b ^= value
        return [a,b]
