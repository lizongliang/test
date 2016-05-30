#include <linux/leds.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <plat/io.h>
#include <linux/amlogic/aml_gpio_consumer.h>
#include <linux/of_gpio.h>
#include <mach/pinmux.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

#define SYSLED_MODULE_NAME "aml_ir_leds"			
#define	TIME_BLINK_DELAY 50
#define TIME_FREQ_COUNT  5

struct timer_list led_timer;
static int blink_freq;
static int is_init;
static int is_press;

struct aml_LED{
	unsigned int  red_led_mode;
	int red_led_gpio;
	enum led_brightness red_led_status;
}aml_led;

void set_ir_led(enum led_brightness brightness)
{
	if(!is_init)return ;
	
	amlogic_gpio_request(aml_led.red_led_gpio, SYSLED_MODULE_NAME);
	
	if(brightness)
	{
		amlogic_gpio_direction_output(aml_led.red_led_gpio,aml_led.red_led_mode, SYSLED_MODULE_NAME);
	}
	else
	{
		amlogic_gpio_direction_output(aml_led.red_led_gpio,!aml_led.red_led_mode, SYSLED_MODULE_NAME);		
	}
	
	aml_led.red_led_status=brightness;
	
	amlogic_gpio_free(aml_led.red_led_gpio, SYSLED_MODULE_NAME);
}

EXPORT_SYMBOL_GPL(set_ir_led);

static void aml_ir_led_set(struct led_classdev *cdev,
			  enum led_brightness brightness)
{
		set_ir_led(brightness);
}

static struct led_classdev aml_ir_uled = {
	.name = "aml_ir_led",
	.brightness_set = aml_ir_led_set,
	.flags			= 0,
};

static void blink_fun_timer(unsigned long data)
{
	if(blink_freq==0)
	{
		if((aml_led.red_led_status==LED_OFF)&&is_press)
		{
			set_ir_led(!LED_OFF); //light on
		}
		is_press=0;
		return ;
	}
		
	set_ir_led(blink_freq--%2);

	mod_timer(&led_timer, jiffies + msecs_to_jiffies(TIME_BLINK_DELAY));
}

void call_irled_blink(void)
{
	blink_freq=TIME_FREQ_COUNT;
	
	if(!is_press)
	{
		mod_timer(&led_timer, jiffies + msecs_to_jiffies(TIME_BLINK_DELAY));
		is_press=1;
	}
}

EXPORT_SYMBOL_GPL(call_irled_blink);

static int __init aml_ir_led_init(void)
{
	is_init=1;
	blink_freq=0;
	is_press=0;
	aml_led.red_led_gpio=amlogic_gpio_name_map_num("GPIO_TEST_N");
	aml_led.red_led_mode=1;
	aml_led.red_led_status=0;

	setup_timer(&led_timer, blink_fun_timer, (unsigned long)&led_timer);

	return led_classdev_register(NULL, &aml_ir_uled);
}

static void __exit aml_ir_led_remove(void)
{
	is_init=0;
	del_timer(&led_timer);
	led_classdev_unregister(&aml_ir_uled);
}

module_init(aml_ir_led_init);
module_exit(aml_ir_led_remove);

MODULE_AUTHOR("ir_led wangzhongwei@youku.com");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LED aml");
