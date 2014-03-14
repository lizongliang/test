#include <stdio.h>

int main(int argc,char *argv)
{
    printf("signed test\n");
    unsigned char num,buf[256];

    for(num = 0; num < 256;num++)
    {
        buf[num] = num;
        printf("num is %d\n",num);
    }
    return 0;
}
