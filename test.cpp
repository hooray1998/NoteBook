#include<stdio.h>
void fun(int i)
{
    static int value=i++;
	value++;
    printf("%d\n",value);
}

int main()
{
    fun(0);
    fun(3);
    fun(5);
    return 0;
}
