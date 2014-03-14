#include <stdio.h>

#define MIN(A,B) ((A) - (B) < 0?(A):(B))
int main()
{
    int sum = 0;
    sum = MIN(2,3);
    printf("sum is %d\n",sum);
    return 0;
}
