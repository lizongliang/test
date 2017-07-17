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

#define HID_DRIVER_TEST_NAME "HID TEST"


#define VENDOR_ID_TEST    0x00D2
#define DEVICE_ID_TEST    0x0580

static const struct hid_device_id test_devices[] = {
    {HID_BLUETOOTH_DEVICE(VENDOR_ID_TEST,DEVICE_ID_TEST)},
};

static int test_probe(struct hid_device *hdev,const struct hid_device_id *id)
{
    printk("######hid probe \n");

    return 0;
}

static void test_remove(struct hid_device *hdev)
{
    printk("#####hid remove  \n");
}

static struct hid_driver test_driver = {
	.name     = HID_DRIVER_TEST_NAME,
    .id_table = test_devices,
    .probe    = test_probe,
    .remove   = test_remove,
};

static int test_init(void)
{
	int ret;
	ret = hid_register_driver(&test_driver);
	if (ret)
    {
		pr_err("%s: can't register hid driver\n", __func__);
    }

    printk("#####hid init succefull\n");
	return ret;
}

static void test_exit(void)
{
	hid_unregister_driver(&test_driver);
    printk("#####3hid exit succefull\n");
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
