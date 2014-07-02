/****************************************
 *@filename main.c
 *@brief
 *@autor   lizongliang
 *@date    2014.7.2
 *@version 1.0
 ***************************************/

#include <stdio.h>

void fun(int arg)
{
    printf("arg is %d\n",arg);
}

void callback(void (*fun1)(int))
{
    fun1(10);
}

int main(int argc,char *argv[])
{
    callback(fun);
    return 0;
}
