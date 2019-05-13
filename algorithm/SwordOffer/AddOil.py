# -*- coding:utf-8 -*-
''' 合并排序 '''
import random
l = [ random.randint(1,100) for i in range(33)]

def MergeSort(s, e):
    if s != e:
        m = int((e+s)/2)
        MergeSort(s, m)
        MergeSort(m+1, e)
        MergeList(s, m, e)

def MergeList(s, m, e):
    newl = []
    i, j = s, m+1
    while i<=m and j<=e:
        if l[i]<l[j]:
            newl.append(l[i])
            i += 1
        else:
            newl.append(l[j])
            j += 1
    if i<=m:
        newl.extend(l[i:m+1])
    if j<=e:
        newl.extend(l[j:e+1])
    l[s:e+1] = newl
    del newl

MergeSort(0,len(l)-1)
print(l)

