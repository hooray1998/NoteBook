# -*- coding:utf-8 -*-

import math

target = 73

s = "abcXYZdef"

length = len(s)

for i in range(int(length/2)):
    s[i],s[length-i] = s[length-i],s[i]

l = [ i+22 for i in range(100) ]

length = len(l)
flag = False
for i in range(length):
    start = i+1
    end = length-1

    while start<=end:
        m = int((start+end)/2)
        sum = l[i] + l[m]
        if sum == target:
            print(l[i],l[m])
            flag = True
            break
        elif sum >target:
            end  = m-1
        else:
            start = m+1
    if flag:
        break
