#include <stdio.h>
static const char *keys[] = {
    "ro.hardward",
    "ro.product.board",
    "ro.board.platform",
    "ro.arch"
};
static const int keys_count = (sizeof(keys)/sizeof(keys[0]));
int test(const char *n)
{
    char *m[128] = {0};
    printf("size of n is %d\n",strlen(n));
    memcpy(m,n,128);

}

struct {
    short a;
    short b;
    short c;
}A;
struct {
    long a;
    short b;
    short d;
    int c;
}B;
int main()
{
    printf("size of a is %d,sizeof b is %d,sizeof long is%d\n",sizeof(A),sizeof(B),sizeof(long));
    //printf("sizeof key %d,sizeof key[0] %d \n",sizeof(keys),sizeof(keys[0]));
    //printf("key count is %d\n",keys_count);
    char mac[64] = {0};
    printf("num is %d\n",sizeof(mac));
    int i = 0;
    for(i = 0 ;i < 63;i++)
    {
        mac[i] = 'a';
    }
    //printf("num is %d\n",sizeof(mac));
    test(mac);

    return 0;
}
