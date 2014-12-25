#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define UDISK_PATH "/dev/mmcblk0p1"
#define BUF_SIZE (1024*1024*7)

int main(int argc,char *argv[])
{
    unsigned char path[32] = {0};
    FILE *fd = NULL;
    long udisk_length = 0;
    char buf[BUF_SIZE];
    int w_size = 0;
    int random_num = 0;
    long i = 0;
    FILE *fp = NULL;
    FILE *std_fd = NULL;

    memset(buf,0xa,BUF_SIZE);
    memset(path,0,32);

    fp = popen("mount |grep mmcblk |awk -F' ' '{print $1}'","r");
    fscanf(fp,"%s",path);
    pclose(fp);

    //open sd card
    fd = fopen(path,"a");
    if(!fd)
    {
	    std_fd = freopen("log.log","w+",stdout);
        printf("open %s failed,errno is %d\n",path,errno);
	    fclose(std_fd);
        return -1;
    }

#if 0
    //get sdcard size 
    if(fseek(fd,0,SEEK_END) < 0)
    {
	    std_fd = freopen("log.log","w+",stdout);
        printf("fseek %s failed\n",UDISK_PATH);
	    fclose(std_fd);
        fclose(fd);
        return -1;
    }
    udisk_length = ftell(fd);
    if(udisk_length < 0)
    {
	    std_fd = freopen("log.log","w+",stdout);
        printf("ftell %s failed\n",UDISK_PATH);
	    fclose(std_fd);
        fclose(fd);
        return -1;
    }
#endif

#if 1 
    //write from begin to end
    if(fseek(fd,0,SEEK_SET) < 0)
    {

	    std_fd = freopen("log.log","w+",stdout);
        printf("fseek %s failed\n",UDISK_PATH);
	    fclose(std_fd);
        fclose(fd);
        return -1;
    }
    for(i = 0;;i++)
    {
        w_size = fwrite(buf,1,BUF_SIZE,fd);
        sync();
        if(w_size < BUF_SIZE && w_size != 0)
        {
            if(fseek(fd,0,SEEK_SET) < 0)
            {

	    std_fd = freopen("log.log","w+",stdout);
                printf("fseek %s failed\n",UDISK_PATH);
	    fclose(std_fd);
                fclose(fd);
                return -1;
            }
            if (buf[1] == 0xa)
                memset(buf,0xb,BUF_SIZE);
            else
                memset(buf,0xa,BUF_SIZE);
	    std_fd = freopen("log.log","w+",stdout);
            printf("#########w_size is %d,data is %x,i is %ld,length is %ld\n",w_size,buf[1],i,ftell(fd)); 
	    fclose(std_fd);
        }
        else if(w_size == 0)
        {
	    std_fd = freopen("log.log","w+",stdout);
            printf("@@@@@@@@@@w_size is %d,data is %x,i is %ld,length is %ld\n",w_size,buf[1],i,ftell(fd));
	    fclose(std_fd);
            fclose(fd);
            return -1;
        }
        else
        {
	    std_fd = freopen("log.log","w+",stdout);
            printf("w_size is %d,data is %x,i is %ld,length is %ld\n",w_size,buf[1],i,ftell(fd)); 
	    fclose(std_fd);

        }
    }
#endif

#if 0
    //write special block
    for(i = 0;;i++)
    {
       if( fseek(fd,0,SEEK_SET) < 0)
        {
	    std_fd = freopen("log.log","w+",stdout);
            printf("fseek %s failed\n",UDISK_PATH);
	    fclose(std_fd);
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
	    std_fd = freopen("log.log","w+",stdout);
            printf("@@@@@@@@@@write special block,w_size is %ld,data is %x,i is %d,length is %ld\n",w_size,buf[1],i,ftell(fd));
	    fclose(std_fd);
            fclose(fd);
            return -1;
        }
        else
        {
	    std_fd = freopen("log.log","w+",stdout);
            printf("write special block,w_size is %d,data is %x,i is %ld,length is %ld\n",w_size,buf[1],i,ftell(fd)); 
	    fclose(std_fd);
        }
    }
#endif

#if 0
    //wirte random block
    for(i = 0;;i++)
    {
        srand((int)time(NULL));
        random_num = rand()%100;

        if(fseek(fd,random_num*BUF_SIZE,SEEK_SET) < 0 )
        {
	    std_fd = freopen("log.log","w+",stdout);
            printf("fseek %s failed,errno is %d\n",UDISK_PATH,errno);
	    fclose(std_fd);
            fclose(fd);
            return -1;
        }
        memset(buf,random_num,BUF_SIZE);

        w_size = fwrite(buf,1,BUF_SIZE,fd);
        sync();

        if(w_size == 0)
        {
	    std_fd = freopen("log.log","w+",stdout);
            printf("@@@@@@@@@@write random block,w_size is %d,data is %d,i is %ld,length is %ld\n",w_size,buf[1],i,ftell(fd));
	    fclose(std_fd);
            fclose(fd);
            return -1;
        }
        else
        {
	    std_fd = freopen("log.log","w+",stdout);
            printf("write random block,w_size is %d,data is %d,i is %ld,length is %ld\n",w_size,buf[1],i,ftell(fd)); 
	    fclose(std_fd);
        }

    }
#endif
    fclose(fd);

    return 0;
}
