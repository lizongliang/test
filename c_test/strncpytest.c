#include <stdio.h>

char *fun(char *dest,const char *src,int n)
{
    int i = 0;
    for(i = 0;i < n && src[i] != '\0';i++)
        dest[i] = src[i];
    for(;i < n;i++)
        dest[i] = '\0';
    return dest;
}

int main(int argc,char *argv[])
{
    char *s = "hello world";
    char buf[64];

    fun(buf,s,12);
    printf("buf is %s\n",buf);
    return 0;
}
