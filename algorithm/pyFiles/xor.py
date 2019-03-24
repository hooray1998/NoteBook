# -*- coding:utf-8 -*-
'''
抑或重要性质:
    a^b^a = a
用reduce函数简化
'''
from functools import reduce

a, b = 3, 4
print('{:0>4b}'.format(a))
print('{:0>4b}'.format(b))

a = a^b
# a = 0111
b = b^a # b^(a^b) => a
# b = 0011
a = a^b # (a^b)^a => b
# a = 0100


# 找出唯一的落单数
l1 = [1, 2, 3, 4, 5, 2, 4, 5, 1]
xor = 0
for i in l1:
    xor ^= i
print(xor)
print(reduce(lambda x, y: x^y, l1, 0))

# 找出仅有的两个落单数
l2 = [1, 6, 2, 3, 4, 5, 4, 5, 6, 1]
xor = reduce(lambda x, y: x^y, l2, 0)
xor_bin_str = '{:0>32b}'.format(xor) # 32位数最大支持几百万
index = (32-1) - xor_bin_str.rfind('1') # 从右往左找第一个1
# l21, l22 = [], []
# for i in l2:
    # if (i>>index)%2==1:
        # l21.append(i)
    # else:
        # l22.append(i)
l21 = [ i for i in l2 if (i>>index)%2 == 1 ]
l22 = [ i for i in l2 if (i>>index)%2 == 0 ]
print(reduce(lambda x, y: x^y, l21, 0))
print(reduce(lambda x, y: x^y, l22, 0))
