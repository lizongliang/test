/****************************************
 *@filename main.c
 *@brief
 *@autor   lizongliang
 *@date    2014.3.29
 *@version 1.0
 ***************************************/

#include <stdio.h>

//倒叙一个8进制数
char fun(char data)
{
    data=((data&0xf0)>>4) | ((data&0x0f)<<4); 
    data=((data&0xCC)>>2) | ((data&0x33)<<2); 
    data=((data&0xAA)>>1) | ((data&0x55)<<1); 
    
    return data;
}

int main(int argc,char *argv[])
{
    char data[]  = {0x5a,0x18,0x0d,0x52,0x02,
                     0x14,0x50,0x06,0x10,0x2b,
                     0x2a,0x2c,0x4f,0x5b,0x46,
                     0x47,0x1c,0x15,0x16,0x40,0x4e,0x04};
    char value    = 0;
    int  i        = 0;
    
    for(i = 0;i < sizeof(data)/sizeof(char);i++)
    {
        value = fun(data[i]);
        printf("data[%d] is %x,value is %x\n",i,data[i],value);
    }
    return 0;
}
