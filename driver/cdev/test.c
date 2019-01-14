#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main(){

    int fd;
    int i;
    char data[256];
    int ret;

    fd = open("/dev/simple",O_RDWR);
    if(fd == -1){
        printf("cant open /dev/simple%d\n",errno);
        exit(-1);
    }
    printf("open /dev/lzl succfull\n");

    ret = write(fd,"fuck you",8);
    if(ret == -1){
        printf("wirte error\n");
        exit(-1);
    }

    ret = read(fd,data,8);
    if(ret == -1){
        printf("read error\n");
        exit(-1);
    }

    data[ret] = 0;
    printf("read succful %s\n",data);
    close(fd);
    return 0;
}
