# 排序算法


### 三种颜色排序

> 使用i，j记录前两个颜色的尾巴的后一个元素，k记录第三种颜色的前端的前一个

```python
l = [x%3+1 for x in range(1,20)]
i = j = 0
k = len(l)-1

count = 0
while j<=k:
    count += 1 # 记录迭代的次数
    if l[j] == 1:
        l[i], l[j] = l[j], l[i]
        j += 1
        i += 1
    elif l[j] == 2:
        j += 1
    else:
        l[k], l[j] = l[j], l[k]
        k -= 1
print(l)
print('count: ',count)
```

### 快速排序


```python
l = [3,5,1,4,9,2,1,2]
def partition(start, end):
    print('start', start, 'end',end)
    key = l[start]
    while start<end:
        while start<end and l[end]>=key: end -= 1
        l[start] = l[end]
        while start<end and l[start]<=key: start += 1
        l[end] = l[start]
    l[start] = key
    return start

def qsort(start, end):
    if start< end:
        m = partition(start, end)
        qsort(start,m-1)
        qsort(m+1,end)

qsort(0,len(l)-1)
print(l)
```
