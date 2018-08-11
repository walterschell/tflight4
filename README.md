# tflight4
Linux Kernel HID Module for Thrustmaster T.Flight HOTAS 4 Joystick

The joystick's HID Report Descriptor does not provide a mappingn for the throttle, stick twist, or throttle paddles. This driver replaces the HID report descriptor with one that (hopefully works)

# TODO
Need to test if the optional foot rudders are correctly supported.
