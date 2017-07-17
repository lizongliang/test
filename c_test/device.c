/*
 *  HID driver for the Android TV remote
 *  providing keys and microphone audio functionality
 *
 * Copyright (C) 2014 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <linux/hid.h>
#include <linux/module.h>

MODULE_LICENSE("GPL v2");

struct hid_device *hid;
struct my_device {
    char *name;
    struct device *dev;
};

static void ldd_bus_release(struct device *dev)
{  
      printk("TK---testbus.c-->>>>ldd_bus_release\n");  
}

struct device dev1 = {  
    .init_name   = "ldd0",  
    .release  = ldd_bus_release,
}; 

struct my_device test_device =  {
    .name = "tt",
    .dev = &dev1,
};
//static struct hid_driver mousevsc_hid_driver;
static int mousevsc_hid_parse(struct hid_device *hid)
{
    return 0;
}

static int mousevsc_hid_open(struct hid_device *hid)
{
    return 0;
}

static int mousevsc_hid_start(struct hid_device *hid)
{
    return 0;
}

static void mousevsc_hid_close(struct hid_device *hid)
{
}

static void mousevsc_hid_stop(struct hid_device *hid)
{
}

static struct hid_ll_driver test_ll_driver = {
    .parse = mousevsc_hid_parse,
    .open = mousevsc_hid_open,
    .close = mousevsc_hid_close,
    .start = mousevsc_hid_start,
    .stop = mousevsc_hid_stop,
};
static int test_init(void)
{
    int ret;

    printk("######hid init %d\n",__LINE__);
    hid = hid_allocate_device();
    if (IS_ERR(hid))
    {
        printk("###### hid allocate device failed\n");
        return -1;
    }
    printk("######hid init %d\n",__LINE__);

    hid->ll_driver = &test_ll_driver;
   // hid->driver = &mousevsc_hid_driver;
    sprintf(hid->name, "%s", "HID DEVICE");
    hid->bus     = BUS_VIRTUAL;
    hid->vendor  = 0x00D2;
    hid->product = 0x0580;
    hid->version = 1;
   // hid->dev.parent = test_device.dev;
    //hid->driver_data = &test_device;
   // hid_set_drvdata(hid, &test_parent_device);

    printk("######hid init %d\n",__LINE__);
    ret = hid_add_device(hid);
    printk("######hid init %d\n",__LINE__);
    if (ret) 
    {
        hid_destroy_device(hid);
        printk("######hid add device failed\n");
        return -1;
    }


    printk("######hid init %d\n",__LINE__);
    printk("##### hid device init succefull\n");
	return 0;
}

static void test_exit(void)
{
    printk("##### hid device exit succefull\n");
    hid_destroy_device(hid);
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
