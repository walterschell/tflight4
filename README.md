# tflight4
Linux Kernel HID Module for Thrustmaster T.Flight HOTAS 4 Joystick

The joystick's HID Report Descriptor does not provide a mappingn for the throttle, stick twist, or throttle paddles. This driver replaces the HID report descriptor with one that (hopefully works)

# How to Use (manually)

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

# How to Use (DKMS)

The following list should do it:

```
~$ sudo -i
~# cd /usr/src
~# git clone https://github.com/walterschell/tflight4.git tflight4-1.0
~# dkms install tflight4/1.0
```

# Enable twist and seesaw axis separation

Add configuration to the modprobe.d:

```
~$ sudo -i
~# echo 'options hid-tflight4 throttle_seesaw_extra_axis=1' > /etc/modprobe.d/80-tflight4.conf
```

# TODO
Need to test if the optional foot rudders are correctly supported.
