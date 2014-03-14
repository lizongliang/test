/*
 *钩子函数，会在程序退出以后在执行
 */

#include <stdio.h>
#include <stdlib.h>

void fun()
{
    printf("hog fun\n");
}
int main(int argc,char *argb[])
{
    atexit(fun);
    printf("main test end\n");
    return 0;
}

