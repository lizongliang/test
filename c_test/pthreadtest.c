/*
 * 编译的时候加 -pthread选项
 * 进行线程创建，同步测试
 */

#include <stdio.h>
#include <pthread.h>

int g_Flag = 0;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
void* thread1(void *);
void* thread2(void *);

int main(int argc,char *argv[])
{
    pthread_t tid1,tid2;

    printf("pthread test begin\n");

    if(pthread_create(&tid2,NULL,thread2,NULL) != 0)
    {
        printf("thread2 create faild\n");
    }

    if(pthread_create(&tid1,NULL,thread1,NULL) != 0)
    {
        printf("thread1 create faild\n");
    }

    pthread_cond_wait(&cond,&mutex);
    printf("pthread test end\n");
    return 0;
}

void* thread1(void *arg)
{
    pthread_mutex_lock(&mutex);
    printf("thread 1\n");
    if(g_Flag == 2)
        pthread_cond_signal(&cond);
    g_Flag = 1;
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}
void* thread2(void *arg)
{
    pthread_mutex_lock(&mutex);
    printf("thread 2\n");
    if(g_Flag == 1)
        pthread_cond_signal(&cond);
    g_Flag = 2;
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}
