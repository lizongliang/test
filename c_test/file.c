#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define UDISK_PATH "/dev/sdb1"
#define BUF_SIZE (1024*1024*7)

int main(int argc,char *argv[])
{
    FILE *fd = NULL;
    long udisk_length = 0;
    char buf[BUF_SIZE];
    int w_size = 0;
    int random_num = 0;
    int i = 0;

    memset(buf,0xa,BUF_SIZE);

    //open sd card
    fd = fopen(UDISK_PATH,"a");
    if(!fd)
    {
        printf("open %s failed,errno is %d\n",UDISK_PATH,errno);
        return -1;
    }

    //get sdcard size 
    if(fseek(fd,0,SEEK_END) < 0)
    {
        printf("fseek %s failed\n",UDISK_PATH);
        fclose(fd);
        return -1;
    }
    udisk_length = ftell(fd);
    if(udisk_length < 0)
    {
        printf("ftell %s failed\n",UDISK_PATH);
        fclose(fd);
        return -1;
    }
#if 1
    //write from begin to end
    if(fseek(fd,0,SEEK_SET) < 0)
    {

        printf("fseek %s failed\n",UDISK_PATH);
        fclose(fd);
        return -1;
    }
    for(i = 0;i < 3000;i++)
    {
        w_size = fwrite(buf,1,BUF_SIZE,fd);
        sync();
        if(w_size < BUF_SIZE && w_size != 0)
        {
            if(fseek(fd,0,SEEK_SET) < 0)
            {

                printf("fseek %s failed\n",UDISK_PATH);
                fclose(fd);
                return -1;
            }
            if (buf[1] == 0xa)
                memset(buf,0xb,BUF_SIZE);
            else
                memset(buf,0xa,BUF_SIZE);
            printf("#########w_size is %d,data is %x,i is %d,length is %ld\n",w_size,buf[1],i,ftell(fd)); 
        }
        else if(w_size == 0)
        {
            printf("@@@@@@@@@@w_size is %d,data is %x,i is %d,length is %ld\n",w_size,buf[1],i,ftell(fd));
            fclose(fd);
            return -1;
        }
        else
        {
            printf("w_size is %d,data is %x,i is %d,length is %ld\n",w_size,buf[1],i,ftell(fd)); 

        }
    }
#endif

#if 1
    //write special block
    for(i = 0;i < 3000;i++)
    {
       if( fseek(fd,0,SEEK_SET) < 0)
        {
            printf("fseek %s failed\n",UDISK_PATH);
            fclose(fd);
            return -1;
        }

        if(i%2 == 0)
        {
            memset(buf,0xc,BUF_SIZE);
        }
        else
        {
            memset(buf,0xd,BUF_SIZE);
        }

        w_size = fwrite(buf,1,BUF_SIZE,fd);
        sync();
        if(w_size == 0)
        {
            printf("@@@@@@@@@@write special block,w_size is %d,data is %x,i is %d,length is %ld\n",w_size,buf[1],i,ftell(fd));
            fclose(fd);
            return -1;
        }
        else
        {
            printf("write special block,w_size is %d,data is %x,i is %d,length is %ld\n",w_size,buf[1],i,ftell(fd)); 
        }
    }
#endif

#if 1
    //wirte random block
    for(i = 0;i < 3000;i++)
    {
        srand((int)time(NULL));
        random_num = rand()%100;

        if(fseek(fd,random_num*BUF_SIZE,SEEK_SET) < 0 )
        {
            printf("fseek %s failed,errno is %d\n",UDISK_PATH,errno);
            fclose(fd);
            return -1;
        }
        memset(buf,random_num,BUF_SIZE);

        w_size = fwrite(buf,1,BUF_SIZE,fd);
        sync();

        if(w_size == 0)
        {
            printf("@@@@@@@@@@write random block,w_size is %d,data is %d,i is %d,length is %ld\n",w_size,buf[1],i,ftell(fd));
            fclose(fd);
            return -1;
        }
        else
        {
            printf("write random block,w_size is %d,data is %d,i is %d,length is %ld\n",w_size,buf[1],i,ftell(fd)); 
        }

    }
#endif
    fclose(fd);

    return 0;
}
