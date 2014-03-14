/*
 *螺旋数列问题
 */

#include <stdio.h>

int foo(int x,int y)
{
    int value = 0;
    int n = 0;
    int max = 0;

    n = (abs(x)>abs(y)?abs(x):abs(y));
    printf("n is %d\n",n);

    max = (2*n+1)*(2*n+1);
    printf("n is %d\n",n);

    if(y == -n)
        value = max+x+y;
    else if(y == n)
        value = max + (-x-5*y);
    else if(x == n)
        value = max + (-7*x+y);
    else
        value = max + (3*x-y);
    return value;
}
int main(int argc,char *argv[])
{
    int value = 0;
    int n = 0,m = 0;
    
    if(argc < 3)
    {
        printf("argu error\n");
        return -1;
    }

    n = atoi(argv[1]);
    m = atoi(argv[2]);
    value = foo(n,m);
    printf("value is %d\n",value);
    return 0;
}
