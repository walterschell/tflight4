
# TODO: add a sign target to sign the module when secure booted
obj-m += hid-tflight4.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
