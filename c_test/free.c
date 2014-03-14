/*
 *free了同一块内存地址，出错，这种错误很难查
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int a;
    char *buf;
}node;

void fun_init(int a,char *buf,node *node1)
{
    node1->a = a;
    node1->buf = malloc(strlen(buf)+1);
    strcpy(node1->buf,buf);
}

void fun_copy(node *node1,node *node2)
{
    memcpy(node2,node1,sizeof(node));
}

void fun_free(node *p)
{
    free(p->buf);
}

int main(int argc,char *argv[])
{
    node node1 ;
    node node2 ;

    fun_init(1,"acb",&node1);
    printf("a is %d,buf is %s,buf addr is %x\n",node1.a,node1.buf,node1.buf);
    fun_copy(&node1,&node2);
    printf("a is %d,buf is %s,buf addr is %x\n",node2.a,node2.buf,node2.buf);

    fun_free(&node1);
    fun_free(&node2);
    return 0;
}
