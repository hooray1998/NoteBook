# -*- coding:utf-8 -*-
'''
组合问题
回溯法
'''

Count = 0 # 记录遍历的次数
MaxDeep = 3
MaxValue = 4
List = [0] * (MaxDeep+1)

def Try(CurDeep):
    global Count
    Count += 1
    '''探索第CurDeep层'''
    # 相比全排列，两处改动
    for i in range(List[CurDeep-1]+1, MaxValue+1): 
        List[CurDeep] = i
        result = OK(CurDeep)
        # 相比全排列，注释掉了
        # if result == 6: #符合条件不需要返回上一层 NOTE 
            # break
        if result == 1: #前面符合条件=>继续深一层Try
            Try(CurDeep+1)
    List[CurDeep] = 0

def OK(CurDeep):
    s = set(List[1:CurDeep+1])
    if len(s) == MaxDeep:
        print(List[1:])
        return 6
    elif len(s) == CurDeep:
        return 1
    else:
        return 0

if __name__ == "__main__":
    Try(1)
    print("Count:",Count)
