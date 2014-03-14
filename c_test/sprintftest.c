/*
 *字符串连接
 */

#include <stdio.h>

int main()
{
    char buf[16];

    sprintf(buf,"%s %d","hellow world",1);
    printf("buf is %s\n",buf);

    return 0;
}
