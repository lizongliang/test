/*
 *用来测试芯片的大小端,大端模式就是高字节放在低地址
 */
#include <stdio.h>

int main(int argc,char *argv[])
{
    int a = 12345678;
    char  b = *(char *)&a;
    printf("b is %d\n",b);
    
    if(b == 78)
    {
        printf("This is big endian\n");
    }
    else
    {
        printf("This is little endian\n");
    }

    return 0;
}
