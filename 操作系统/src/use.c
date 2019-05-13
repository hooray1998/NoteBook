/*=========================================================
> File Name: src/use.c
> Author:hooray
> Mail:hoorayitt@gmail.com 
> Created Time: 2019年04月27日 星期六 16时46分02秒
> =======================================================*/

#include <unistd.h>

int main()
{
    char buf[80];
    int count;
    count = read(0, buf, sizeof(buf));//标准输入
    buf[count] = 0;//0 就是'\0'
    write(1, buf, count);//标准输出
}
