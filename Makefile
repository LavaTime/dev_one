KVER := $(shell uname -r)

M := $(shell pwd)

KDIR := /lib/modules/$(KVER)/build

obj-m += dev_one.o

CC = x86_64-linux-gnu-gcc-13

all:
	make -C $(KDIR) M=$(M) modules

clean:
	$(MAKE) -C $(KDIR) M=$(M) clean