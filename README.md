# Kernel driver for LPS25HB Barometric Pressure and Temperature Sensors
[LPS25HB Datasheet](https://www.pololu.com/file/0J1466/LPS25HB.pdf)

Integration details
=====================
### Source code integration

> * Install kernel headers for your oS
> * Ubuntu/Debian

>         apt install linux-headers-$(uname -r)

> * CentOS/RHEL 7

>         yum install kernel-devel 
>         yum install kernel-headers

> * CentOS/RHEL8

>         dnf install kernel-devel
>         dnf install kernel-headers

> * Raspbian

>         apt-get install raspberrypi-kernel-headers

> * Load the industrialio 

>         modprobe industrialio

> * Get the code

>         gh repo clone DreadlordGG/LPS25HB-driver

> * Make

>          Make

> * Load
>         insmod lps25hb.ko

> * Instantiate device

>         echo lps25hb 0x5d > /sys/bus/i2c/devices/<i2c bus>/new_device # ex. echo lps25hb 0x5d > /sys/bus/i2c/devices/i2c-1/new_device

> * To remove the driver and the device

>         /sys/bus/i2c/devices/<i2c bus>/delete_device
>         rmmod lps25hb
