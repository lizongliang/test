PWD = $(shell pwd)
KERNEL_SRC =/home/lizongliang/work/external/z1/Amlogic-905/common
 
obj-m := driverdemo.o
module-objs := driverdemo.o
 
all:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) modules

clean:
	rm *.ko
	rm *.o

