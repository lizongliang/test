/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <cutils/properties.h>
#include <cutils/android_reboot.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <errno.h>
#include <dirent.h>
#include <sys/poll.h>

#define DEVICE "/dev/input/"

int get_device_fd(char *);
int get_device_keyvalue(int);
int keyvaluetosn(char *keyvalue,int len,char *sn);


int main(int argc,char **argv)
{
    int fd = 0;
    int i = 0;
    int res = 0;
    char devname[64]= {0};
    DIR *dir = NULL;
    struct dirent *de = NULL;
    char key[128] = {0};
    struct pollfd *ufds;
    int nfds;
    char sn[128] = {0};

    dir = opendir(DEVICE);
    if(dir == NULL)
        return -1;
    
    while((de = readdir(dir)))
    {
        strncpy(devname,DEVICE,sizeof(devname));
        if(de->d_name[0] == '.') 
        {
            memset(devname,0,sizeof(devname));
            continue;
        }
        strcat(devname,de->d_name);
        //printf("name is %s\n",devname);

        if((fd = get_device_fd(devname)) > 0)
            break;
        memset(devname,0,sizeof(devname));
    }
    closedir(dir);

    nfds = 1;
    ufds = calloc(1,sizeof(ufds[0]));
    ufds[0].fd = fd;
    ufds[0].events = POLLIN;
    memset(key,0,sizeof(key));

    while(1)
    {
            poll(ufds,nfds,-1);
            if(ufds[0].revents & POLLIN)
            {
                res = get_device_keyvalue(fd);
                if (res > 0)
                {
                    key[i] = res;
                    //printf("i is %d,key is %x\n",i,key[i]);
                    i++;
                }
                if(key[i-1]== 0x28 && key[i-2] == 0x28)
                {
                    close(fd);
                    free(ufds);
                    break;
                }
            }
    }

    keyvaluetosn(key,sizeof(key),sn);

#if 0
    for(i=0;i < (int)sizeof(sn);i++)
    {
        printf("sn is %x\n",sn[i]);
    }
#endif
        printf("sn is %s\n",sn);

    return 0;
}

int get_device_fd(char *name)
{
    int fd = 0;
    struct input_id id;
    
    memset(&id,0,sizeof(id));
    fd = open(name,O_RDONLY);
    if(fd < 0)
    {
        printf("open %s error, errno is %d\n",name,errno);
        return -1;
    }
    if(ioctl(fd, EVIOCGID, &id))
    {
        printf("could not get device id,errno is %d\n",errno);
    }
    if(id.vendor == 0x1fbb)   
    {
       // printf("device event is %s\n",name);
        return fd;
    }
    else
    {
        close(fd);
    }
    return 0;
}

int get_device_keyvalue(int fd)
{
    struct input_event event;
    int res = 0;
    int keyvalue = 0;

    memset(&event,0,sizeof(event));

    res = read(fd,&event,sizeof(event));
    if(res <= 0)
    {
        printf("read error,errno is %d,res %d\n",errno,res);
        close(fd);
        return -1;
    }

    if(event.type == 4 && event.code == 4)
        keyvalue = event.value & 0xFF;

    //printf("type %x,code %x,value %x,key %x\n",event.type, event.code, event.value,keyvalue);
    return keyvalue;
}

int keyvaluetosn(char *keyvalue,int len,char *sn)
{
    char keymap[37][2];
    char temp[128] = {0};
    int i = 0;
    int j = 0;
    int n = 0;

    keymap[0][0] = 0xe1;
    keymap[0][1] = 0xe1;
    keymap[1][0] = 0x27;
    keymap[1][1] = 0x30;

#if 0
    for(i = 0;i<len;i++)
    {
        printf("keyvlaue %x\n",keyvalue[i]);
    }
#endif

    for(i = 2;i < 37;i++)
    {
        for(j = 0;j < 2;j++)
        {
            if(i < 28)
            {
                if(j == 0)
                    keymap[i][j]=0x4 + i - 2;
                else
                    keymap[i][j]='a' + i -2;
            }
            else
            {
                if(j == 0)
                    keymap[i][j] = 0x1e + i - 28;
                else
                    keymap[i][j] = '1' + i - 28;
            }
        }
    }

#if 0
    for(i = 0;i < 37;i++)
    {
        printf("keymap is %x %x\n",keymap[i][0],keymap[i][1]);
    }
#endif

    for(i = 0;i < len;i++)
    {
        for(j = 0;j < 37;j++)
        {
            if(keyvalue[i] == keymap[j][0])
            {
                temp[n++] = keymap[j][1];
                break;
            }
        }
    }
#if 0
    for(i = 0;i < (int)sizeof(temp);i++)
    {
        printf("i %d, temp is %x\n",i,temp[i]);
    }
#endif
    j = 0;

    for(i = 0;i < (int)sizeof(temp);)
    {
        if(temp[i] == 0xe1 && temp[i+1] != 0xe1)
        {
            sn[j++] = temp[i+1] - 32;
            i = i + 4;

        }
        else if(temp[i] == 0xe1 && temp[i+1] == 0xe1)
        {
            i++;
        }
        else
        {
            sn[j++] = temp[i];
            i = i + 2;
        }

    }
    return 0;
}
