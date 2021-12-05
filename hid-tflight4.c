/**
 * This driver adds support for the Thrustmaster T.Flight 4 Joystick
 * The HID Report Description provided by the device does not map the
 * fields where the stick twist, throttle paddles, and throttle position
 * are reported. The replaces the mapping with one that includes those fields
 * It removes the 8bit X/Y mappings provided and replaces them with 16bit
 * mappings for the X/Y axis.
 */
#include <linux/device.h>
#include <linux/hid.h>
#include <linux/module.h>
#include <linux/kernel.h>

#define USB_VENDOR_ID_THRUSTMASTER 0x044f
#define USB_DEVICE_ID_THRUSTMASTER_TFLIGHT4 0xb67b
/*
static u8 orig_rdesc[] = {
0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
0x09, 0x05,        // Usage (Game Pad)
0xA1, 0x01,        // Collection (Application)
0x85, 0x01,        //   Report ID (1)
0x09, 0x30,        //   Usage (X)
0x09, 0x31,        //   Usage (Y)
0x09, 0x32,        //   Usage (Z)
0x09, 0x35,        //   Usage (Rz)
0x15, 0x00,        //   Logical Minimum (0)
0x26, 0xFF, 0x00,  //   Logical Maximum (255)
0x75, 0x08,        //   Report Size (8)
0x95, 0x04,        //   Report Count (4)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x09, 0x39,        //   Usage (Hat switch)
0x15, 0x00,        //   Logical Minimum (0)
0x25, 0x07,        //   Logical Maximum (7)
0x35, 0x00,        //   Physical Minimum (0)
0x46, 0x3B, 0x01,  //   Physical Maximum (315)
0x65, 0x14,        //   Unit (System: English Rotation, Length: Centimeter)
0x75, 0x04,        //   Report Size (4)
0x95, 0x01,        //   Report Count (1)
0x81, 0x42,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State)
0x65, 0x00,        //   Unit (None)
0x05, 0x09,        //   Usage Page (Button)
0x19, 0x01,        //   Usage Minimum (0x01)
0x29, 0x0E,        //   Usage Maximum (0x0E)
0x15, 0x00,        //   Logical Minimum (0)
0x25, 0x01,        //   Logical Maximum (1)
0x75, 0x01,        //   Report Size (1)
0x95, 0x0E,        //   Report Count (14)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
0x09, 0x20,        //   Usage (0x20)
0x75, 0x06,        //   Report Size (6)
0x95, 0x01,        //   Report Count (1)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x05, 0x01,        //   Usage Page (Generic Desktop Ctrls)
0x09, 0x33,        //   Usage (Rx)
0x09, 0x34,        //   Usage (Ry)
0x15, 0x00,        //   Logical Minimum (0)
0x26, 0xFF, 0x00,  //   Logical Maximum (255)
0x75, 0x08,        //   Report Size (8)
0x95, 0x02,        //   Report Count (2)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
0x09, 0x21,        //   Usage (0x21)
0x95, 0x36,        //   Report Count (54)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x85, 0x05,        //   Report ID (5)
0x09, 0x22,        //   Usage (0x22)
0x95, 0x1F,        //   Report Count (31)
0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
0x85, 0x03,        //   Report ID (3)
0x0A, 0x21, 0x27,  //   Usage (0x2721)
0x95, 0x2F,        //   Report Count (47)
0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
0xC0,              // End Collection
0x06, 0xF0, 0xFF,  // Usage Page (Vendor Defined 0xFFF0)
0x09, 0x40,        // Usage (0x40)
0xA1, 0x01,        // Collection (Application)
0x85, 0xF0,        //   Report ID (-16)
0x09, 0x47,        //   Usage (0x47)
0x95, 0x3F,        //   Report Count (63)
0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
0x85, 0xF1,        //   Report ID (-15)
0x09, 0x48,        //   Usage (0x48)
0x95, 0x3F,        //   Report Count (63)
0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
0x85, 0xF2,        //   Report ID (-14)
0x09, 0x49,        //   Usage (0x49)
0x95, 0x0F,        //   Report Count (15)
0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
0x85, 0xF3,        //   Report ID (-13)
0x0A, 0x01, 0x47,  //   Usage (0x4701)
0x95, 0x07,        //   Report Count (7)
0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
0xC0,              // End Collection
};
*/

static u8 fixed_rdesc[] = {
0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
0x09, 0x05,        // Usage (Game Pad)
0xA1, 0x01,        // Collection (Application)
0x85, 0x01,        //   Report ID (1)

//Begin Modification

0x09, 0x00,        //   Usage (Undefined) was 0x09, 0x30 Usage (X)
0x09, 0x00,        //   Usage (Undefined) was 0x09, 0x31 Usage (Y)
0x09, 0x00,        //   Usage (Undefined) was 0x09, 0x32 Usage (Z)
0x09, 0x00,        //   Usage (Undefined) was 0x09, 0x35 Usage (Rz)

//End Modification

0x15, 0x00,        //   Logical Minimum (0)
0x26, 0xFF, 0x00,  //   Logical Maximum (255)
0x75, 0x08,        //   Report Size (8)
0x95, 0x04,        //   Report Count (4)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)


0x09, 0x39,        //   Usage (Hat switch)
0x15, 0x00,        //   Logical Minimum (0)
0x25, 0x07,        //   Logical Maximum (7)
0x35, 0x00,        //   Physical Minimum (0)
0x46, 0x3B, 0x01,  //   Physical Maximum (315)
0x65, 0x14,        //   Unit (System: English Rotation, Length: Centimeter)
0x75, 0x04,        //   Report Size (4)
0x95, 0x01,        //   Report Count (1)
0x81, 0x42,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State)

0x65, 0x00,        //   Unit (None)
0x05, 0x09,        //   Usage Page (Button)
0x19, 0x01,        //   Usage Minimum (0x01)
0x29, 0x0E,        //   Usage Maximum (0x0E)
0x15, 0x00,        //   Logical Minimum (0)
0x25, 0x01,        //   Logical Maximum (1)
0x75, 0x01,        //   Report Size (1)
0x95, 0x0E,        //   Report Count (14)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)

0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
0x09, 0x20,        //   Usage (0x20)
0x75, 0x06,        //   Report Size (6)
0x95, 0x01,        //   Report Count (1)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x05, 0x01,        //   Usage Page (Generic Desktop Ctrls)

// Begin Modification

0x09, 0x00,        //   Usage (Undefined) was 0x09, 0x33 Usage (Rx)
0x09, 0x00,        //   Usage (Undefined) was 0x09, 0x34 Usage (Ry)

// End Modification

0x15, 0x00,        //   Logical Minimum (0)
0x26, 0xFF, 0x00,  //   Logical Maximum (255)
0x75, 0x08,        //   Report Size (8)
0x95, 0x02,        //   Report Count (2)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)

0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)

//Begin Additions
//UNK Padding
0x09, 0x21,        //   Usage (0x21)
0x95, 0x21,        //   Report Count (33)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)

//Higher Precision X/Y Axis
0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
0x09, 0x30,        // Usage (X)
0x09, 0x31,        // Usage (Y)
0x15, 0x00,        //   Logical Minimum (0)
0x27, 0xFF, 0xFF,  0x00, 0x00, //   Logical Maximum (65535)
0x75, 0x10,        //   Report Size (16)
0x95, 0x02,        //   Report Count (2)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)

//Stick Rotation, Throttle, Throttle Paddles
0x09, 0x35,       // Usage (rZ) Stick Rotation -- This is patched to 0x09, 0x32 (Usage (Z)) if throttle_seesaw_extra_axis is enabled
0x09, 0x36,       // Usage (Slider) Throttle Position
0x09, 0x35,       // Usage (rZ) Throttle Paddles
0x15, 0x00,        //   Logical Minimum (0)
0x26, 0xFF, 0x00,  //   Logical Maximum (255)
0x75, 0x08,        //   Report Size (8)
0x95, 0x03,        //   Report Count (3)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)

//UNK Padding
0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
0x09, 0x21,        //   Usage (0x21)
0x95, 0x0E,        //   Report Count (14)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)

//End Additions

0x85, 0x05,        //   Report ID (5)
0x09, 0x22,        //   Usage (0x22)
0x95, 0x1F,        //   Report Count (31)
0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
0x85, 0x03,        //   Report ID (3)
0x0A, 0x21, 0x27,  //   Usage (0x2721)
0x95, 0x2F,        //   Report Count (47)
0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
0xC0,              // End Collection

0x06, 0xF0, 0xFF,  // Usage Page (Vendor Defined 0xFFF0)
0x09, 0x40,        // Usage (0x40)
0xA1, 0x01,        // Collection (Application)
0x85, 0xF0,        //   Report ID (-16)
0x09, 0x47,        //   Usage (0x47)
0x95, 0x3F,        //   Report Count (63)
0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
0x85, 0xF1,        //   Report ID (-15)
0x09, 0x48,        //   Usage (0x48)
0x95, 0x3F,        //   Report Count (63)
0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
0x85, 0xF2,        //   Report ID (-14)
0x09, 0x49,        //   Usage (0x49)
0x95, 0x0F,        //   Report Count (15)
0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
0x85, 0xF3,        //   Report ID (-13)
0x0A, 0x01, 0x47,  //   Usage (0x4701)
0x95, 0x07,        //   Report Count (7)
0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
0xC0,              // End Collection
};


static int throttle_seesaw_extra_axis = 0;
module_param(throttle_seesaw_extra_axis, int, 0664);
MODULE_PARM_DESC(throttle_seesaw_extra_axis, "Assign stick twist to a Z axis, unlocking throttle seesaw as a separate Rz axis. Default is 0 (off), which matches proprietary driver. Set to 1 to enable.");


static __u8 *tflight_report_fixup(struct hid_device *hdev,
                                      __u8 *rdesc,
                                      unsigned int *rsize)
{
    hid_info(hdev, "Fixing up HID Descriptor Report for T.Flight 4 Joystick");

    rdesc = fixed_rdesc;

// 0x32 Usage (Z) Stick Rotation
// 0x35 Usage (rZ) Stick Rotation
rdesc[121] = (throttle_seesaw_extra_axis) ? 0x32 : 0x35;

    *rsize = sizeof(fixed_rdesc);

    return rdesc;
}

static const struct hid_device_id tflight_devices[] = {
    { HID_USB_DEVICE(USB_VENDOR_ID_THRUSTMASTER, USB_DEVICE_ID_THRUSTMASTER_TFLIGHT4)},
    { }
};

static struct hid_driver tflight_driver = {
    .name = "Thrustmaster T.Flight",
    .id_table = tflight_devices,
    .report_fixup = tflight_report_fixup,
};

module_hid_driver(tflight_driver);

MODULE_LICENSE("GPL");
