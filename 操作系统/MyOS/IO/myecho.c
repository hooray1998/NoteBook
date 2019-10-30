//>>> 使用参数
#include<stdio.h>

int main(int argc, char** argv)
{
    while(*++argv!=NULL)
    {
        printf("%s ", *argv);
    }
    if(argc>1)
        printf("\n");

    return 0;
}
