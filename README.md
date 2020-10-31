# tflight4
Linux Kernel HID Module for Thrustmaster T.Flight HOTAS 4 Joystick

The joystick's HID Report Descriptor does not provide a mappingn for the throttle, stick twist, or throttle paddles. This driver replaces the HID report descriptor with one that (hopefully works)

# How to Use

Install whatever package your distro requires for compiling C. On ubuntu this is `build-essential`. 

Now build the module:

    make

Load the module into the current running kernel to test it out for your use. A reboot will undo this change:

    insmod hid-tflight4.ko

If it works well for you, then install it and set it up to be loaded at boot. After this next step, a reboot will not undo this change:

    sudo cp hid-tflight4.ko /lib/modules/$(uname -r)/kernel/drivers/hid/ \
      && sudo depmod \
      && sudo modprobe hid-tflight4 \
      && grep -qxF 'hid-tflight4' /etc/modules || echo 'hid-tflight4' | sudo tee -a /etc/modules 
    
To undo the previous step, do the following:

    sudo rm -f /lib/modules/$(uname -r)/kernel/drivers/hid/hid-tflight4.ko \
      && sudo depmod \
      && sudo sed -i '/hid-tflight4/d' /etc/modules

# TODO
Need to test if the optional foot rudders are correctly supported.
