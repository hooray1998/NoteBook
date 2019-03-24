# -*- coding:utf-8 -*-
'''
素数环问题
回溯
'''
Count = 0 # 记录遍历的次数
MaxDeep = 8
List = [0] * (MaxDeep+2) # 在最后加上第一个元素
AllPrimeNumber = [x for x in range(3, 2*MaxDeep, 2)]

def Try(CurDeep):
    global Count
    Count += 1
    # print(List)
    '''探索第CurDeep层'''
    # for i in range(1, MaxDeep+1):
    start = 1
    if List[CurDeep-1]%2 == 1:
        start += 1
    for i in range(start, MaxDeep+1,2):
        List[CurDeep] = i
        # print('for : ',List[1:CurDeep+1])
        result = OK(CurDeep)
        if result == 6: #符合条件的结果=>初始化置零=>返回上一层
            break
        elif result == 1: #前面符合条件=>继续深一层Try
            Try(CurDeep+1)
    List[CurDeep] = 0

def OK(CurDeep):
    List[-1] = List[1]
    num = 0
    if CurDeep == 1:
        return 1
    for i in range(1, CurDeep):
        if List[i]+List[i+1] in AllPrimeNumber:
            num += 1
        else:
            return 0
    if CurDeep == MaxDeep:
        if List[CurDeep]+List[CurDeep+1] in AllPrimeNumber:
            if len(set(List[2:])) == MaxDeep:
                print(List[1:-1])
                return 6
            else:
                return 0
        else:
            return 0
    else:
        return 1

if __name__ == "__main__":
    for i in range(1,MaxDeep*2,2):
        for ii in range(2,int(1+i/2)):
            if i%ii == 0:
                AllPrimeNumber.remove(i)
                break
    # print(AllPrimeNumber)
    List[1] = 1
    Try(2)
    print("Count:",Count)


