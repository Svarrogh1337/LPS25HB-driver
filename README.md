# Kernel driver for LPS25HB Barometric Pressure and Temperature Sensors
[LPS25HB Datasheet](https://www.pololu.com/file/0J1466/LPS25HB.pdf)
# Pressure readings are WiP
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

> * Make the driver

>          Make

> * Load the driver

>         insmod lps25hb.ko

> * Instantiate device

>         echo lps25hb 0x5d > /sys/bus/i2c/devices/<i2c bus>/new_device # ex. echo lps25hb 0x5d > /sys/bus/i2c/devices/i2c-1/new_device

> * Read the raw temperature, temperature offset and temperature scale

>         cat /sys/bus/iio/devices/iio\:device0/in_temp_raw /sys/bus/iio/devices/iio\:device0/in_temp_offset /sys/bus/iio/devices/iio\:device0/in_temp_scale

> * To get the temperature in C the formula is:

>         (int_temp_raw / int_temp_scale) + int_temp_offset
    
> * To remove the driver and the device

>         /sys/bus/i2c/devices/<i2c bus>/delete_device
>         rmmod lps25hb


