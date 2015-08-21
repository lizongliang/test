
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include <cutils/memory.h>
#include<native_window.h>

#include <utils/Log.h>

#include<SkCanvas.h>
#include<SkBitmap.h>
#include<SkPaint.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>

#include <ui/GraphicBuffer.h>
#include <gui/Surface.h>
#include <gui/ISurfaceComposer.h>
#include <gui/SurfaceComposerClient.h>
#include <cutils/properties.h>

#include <ui/DisplayInfo.h>
using namespace android;

#define CPU "/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq"
#define TEMP "/sys/class/thermal/thermal_zone1/temp"
int get_current_info(char *name,char *data)
{
    int fd = 0;
    ssize_t num = 0;
    char buf[32] = {'0'};

    fd = open(name,O_RDONLY);
    if(fd < 0)
    {
        printf("open %s failed,error is %d\n",name,errno);
        return -1;
    }
    
    num = read(fd,buf,32);
    if(num < 0)
    {
        printf("open %s failed,error is %d\n",name,errno);
        close(fd);
        return -1;
    }

    strncpy(data,buf,4);
    close(fd);

    return 1;
}
int main(int argv,char *argc[])
{
    sp<ProcessState> proc(ProcessState::self());
    ProcessState::self()->startThreadPool();

    sp<SurfaceComposerClient> client = new SurfaceComposerClient();
    //sp<SurfaceControl> surfaceControl = client->createSurface(String8("testsurface"),240, 160, PIXEL_FORMAT_RGBX_8888, 0);
    DisplayInfo dinfo;
    sp<IBinder> display = SurfaceComposerClient::getBuiltInDisplay(
            ISurfaceComposer::eDisplayIdMain);
    SurfaceComposerClient::getDisplayInfo(display, &dinfo);
    uint32_t dispw = dinfo.w;
    uint32_t disph = dinfo.h;
    ANativeWindow_Buffer outBuffer;
    ssize_t bpr = 0;
    dispw = 200;
    disph = 60;
    int i = 0;
    const char *str_cpu="CPU Frequency:";  
    const char *str_tmp="Temperature:";  
    char cpu_buf[32] = {'0'};
    char tmp_buf[32] = {'0'};

    /* create backgound surface */
    sp<SurfaceControl> bg_surfaceControl = client->createSurface(
            String8("test-bg-surface"), dispw, disph, PIXEL_FORMAT_RGBX_8888);

    sp<Surface> bg_surface = bg_surfaceControl->getSurface();

    /* set background layer z-order */
    SurfaceComposerClient::openGlobalTransaction();
    bg_surfaceControl->setLayer(200000);
    SurfaceComposerClient::closeGlobalTransaction();

    /* clear background layer black */
/*
    bg_surface->lock(&outBuffer, NULL);
    ssize_t bpr = outBuffer.stride * bytesPerPixel(outBuffer.format);
    android_memset32((uint32_t*)outBuffer.bits, 0xFF000000, bpr * outBuffer.height);
    bg_surface->unlockAndPost();
    sleep(5);

    bg_surface->lock(&outBuffer, NULL);
     bpr = outBuffer.stride * bytesPerPixel(outBuffer.format);
    android_memset32((uint32_t*)outBuffer.bits, 0xF800, bpr * outBuffer.height);
    bg_surface->unlockAndPost();
    sleep(5);

    bg_surface->lock(&outBuffer, NULL);
    bpr = outBuffer.stride * bytesPerPixel(outBuffer.format);
    android_memset32((uint32_t*)outBuffer.bits, 0x7e56, bpr * outBuffer.height);
    bg_surface->unlockAndPost();
    sleep(5);
    */
    SkPaint paint;
    paint.setColor(SK_ColorRED);
    paint.setTextSize(20);  


    for(i = 0;;i++)
    {
        get_current_info(CPU,cpu_buf);
        get_current_info(TEMP,tmp_buf);
       // printf("cpu %s is %d,,tmp %s is %d\n",cpu_buf,strlen(cpu_buf),tmp_buf,strlen(tmp_buf));

        bg_surface->lock(&outBuffer, NULL);

        bpr = outBuffer.stride * bytesPerPixel(outBuffer.format);
        android_memset32((uint32_t*)outBuffer.bits, 0xFFFF, bpr * outBuffer.height);

        SkBitmap bmp = SkBitmap();    
        bmp.setConfig(SkBitmap::kARGB_8888_Config,dispw,disph,bpr);    
        bmp.setPixels(outBuffer.bits);

        SkCanvas canvas(bmp);

        canvas.drawText(str_cpu,strlen(str_cpu), 0, 20 , paint);
        canvas.drawText(cpu_buf,strlen(cpu_buf),(strlen(str_cpu)+1)*10, 20 , paint);
        canvas.drawText(str_tmp,strlen(str_tmp), 0, 50 , paint);
        canvas.drawText(tmp_buf,strlen(tmp_buf),(strlen(str_tmp)+1)*10, 50 , paint);

        bg_surface->unlockAndPost();

        sleep(1);
    }

    return 0;
}
