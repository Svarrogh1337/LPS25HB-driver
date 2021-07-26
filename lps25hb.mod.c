#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x4766f3ab, "module_layout" },
	{ 0xf61e4b92, "i2c_del_driver" },
	{ 0x44e9e51e, "i2c_register_driver" },
	{ 0x67ea780, "mutex_unlock" },
	{ 0x3a00f69d, "i2c_smbus_read_word_data" },
	{ 0xc271c3be, "mutex_lock" },
	{ 0x56755c4a, "_dev_err" },
	{ 0x8033fac6, "__iio_device_register" },
	{ 0xe346f67a, "__mutex_init" },
	{ 0x91775fb1, "devm_iio_device_alloc" },
	{ 0x960dcb9b, "iio_device_unregister" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "industrialio");

MODULE_ALIAS("i2c:lps25hb");

MODULE_INFO(srcversion, "BEA07A1FD27915C4078B6F1");
