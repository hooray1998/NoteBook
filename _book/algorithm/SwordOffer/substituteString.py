# -*- coding:utf-8 -*-
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    # 返回从尾部到头部的列表值序列，例如[1,2,3]
    def printListFromTailToHead(self, listNode):
        # write code here
        l = list()
        
        p = listNode
        while p != None:
            l.append(p.val)
            p = p.next
        
        return l.reverse



n = -8
sum = 0
while n != 0:
    sum += n%2
    n = int(n/2)
print(sum)
