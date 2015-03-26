/****************************************
 *@filename glset_recovery_flag.c
 *@brief    reboot into recovery
 *@autor    lizongliang
 *@date     2014.3.28
 *@version  1.0
 ***************************************/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cutils/log.h>

#define MISC "/dev/block/nandf"

typedef struct bootloader_message 
{
    char command[32];
    char status[32];
    char recovery[1024];
}bootloader_message_t;

/*
 *recover for help
 */
void gl_help(void)
{
    ALOGD("recovery update:reboot for update\n");
    ALOGD("recovery reboot:reboot\n");

    return ;
}

/*
 *@note waiting for device is no busy
 */
static void gl_wait_for_device(const char* fn) 
{
    int tries = 0;
    int ret;
    struct stat buf;
    do 
    {
        ++tries;
        ret = stat(fn, &buf);
        if (ret) 
        {
            ALOGE("stat %s try %d: %s\n", fn, tries, strerror(errno));
            sleep(1);
        }
    } while (ret && tries < 10);

    if (ret)
    {
        ALOGD("failed to stat %s\n", fn);
    }
    
    return ;
}

/*
 *@note get bootloader_message from misc
 */
static int gl_get_bootloader_message(bootloader_message_t *out)
{
    bootloader_message_t temp;
    int count = 0;
    FILE *f = NULL;

    gl_wait_for_device(MISC);

    f = fopen(MISC, "rb");
    if (f == NULL) 
    {
        ALOGE("open nandf faild ,errno is %s\n",strerror(errno));
        return -1;
    }

    count = fread(&temp,sizeof(temp),1,f);
    if (count != 1) 
    {
        ALOGE("read nandf faild,errno is %s\n",strerror(errno));
        return -1;
    }

    if (fclose(f) != 0) 
    {
        ALOGE("close nandf faild,errno is %s\n",strerror(errno));
        return -1;
    }

    memcpy(out, &temp, sizeof(temp));

    return 0;
}

/*
 *@note set bootloader_message for misc
 */
static int gl_set_bootloader_message(const bootloader_message_t *in)
{
    int count = 0;
    FILE *f = NULL;

    gl_wait_for_device(MISC);

    f = fopen(MISC, "wb");
    if (f == NULL) 
    {
        ALOGE("open nandf faild,errno is %s\n",strerror(errno));
        return -1;
    }

    count = fwrite(in,sizeof(*in),1,f);
    if (count != 1) 
    {
        ALOGE("write nandf faild,errno is %s\n",strerror(errno));
        return -1;
    }

    if (fclose(f) != 0)
    {
        ALOGE("close nandf faild,errno is %s\n",strerror(errno));
        return -1;
    }

    return 0;
}

/*
 *@note read-after-write for check,if error,write agian.tyr 5 times
 */
void gl_set_recovery_flag(void)
{
    bootloader_message_t boot,temp;
    int i = 5;

    memset(&boot,0,sizeof(bootloader_message_t));
    strncpy(boot.command,"boot-recovery",sizeof(boot.command));
    strncpy(boot.recovery,"recovery\n",sizeof(boot.recovery));

    gl_set_bootloader_message(&boot);
    sync();
    
    while(i)
    {
        memset(&temp,0,sizeof(bootloader_message_t));
        gl_get_bootloader_message(&temp);
        
        if(strstr(temp.command,"boot-recovery"))
        {
            ALOGD("write recovery flag successful\n");
            break;
        }
        else
        {
            ALOGD("write recovery flag faild\n");
            gl_set_bootloader_message(&boot);
            sync();
            i--;
        }
    }
    
    return ;

}
int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        gl_help();
        return 0;
    }
    
    gl_set_recovery_flag();

    if(0 == strncmp(argv[1],"help",strlen("help")))
    {
        gl_help();
    }
    else if(0 == strncmp(argv[1],"update",strlen("update")))
    {
        ALOGD("update system after reboot\n");
        gl_set_recovery_flag();
	system("mkdir -p /cache/recovery");
	system("echo --update_package=CACHE:update/update.zip > /cache/recovery/command");

    }
    else if(0 == strncmp(argv[1],"reboot",strlen("reboot")))
    {
        ALOGD("reboot system now\n");
        sync();
        system("reboot");
    }
    else
    {
        ALOGD("Invalid parameter\n");
        gl_help();
    }

    return 0;
}

