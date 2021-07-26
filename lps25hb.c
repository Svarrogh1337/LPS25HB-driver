#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/iio/iio.h>
#include <linux/mfd/iqs62x.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>
#define DRIVER_NAME "lps25hb"
#define DRIVER_CLASS "lps25hbClass"
#define SLAVE_DEVICE_NAME	"LPS25HB"	
#define LPS25HB_SLAVE_ADDRESS_1	0x5D		/* LPS25HB address with pull up */
#define LPS25HB_SLAVE_ADDRESS_2 0x5C            /* LPS25GB address with pull down */
#define LPS25HB_READ_REG        0x80     
#define LPS25HB_TEMP_SCALE      480
#define LPS25HB_TEMP_OFFSET     42.50
#define LPS25HB_TEMP_OUT_H      0x2C
#define LPS25HB_TEMP_OUT_L      0x2B
#define LPS25HB_PRESS_OUT       0x2

struct lps25hb_priv {
	struct i2c_client	*client;
	struct mutex		lock;
	s32			pressure;	
	s32			temp;		
};

static const struct iio_chan_spec lps25hb_channels[] = {
	{
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
	},
	{
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),

	},
};

static int lps25hb_get_temp_pressure(struct lps25hb_priv *priv)
{
	uint16_t ret;
	const int temp_l = i2c_smbus_read_word_data(priv->client,LPS25HB_TEMP_OUT_L | LPS25HB_READ_REG  );
	const int temp_h = i2c_smbus_read_word_data(priv->client,LPS25HB_TEMP_OUT_H | LPS25HB_READ_REG  ); 
	ret = (temp_h << 8) | temp_l;
	return ret;
	
	}

static int lps25hb_read_raw(struct iio_dev *indio_dev,
			 struct iio_chan_spec const *chan,
			 int *val, int *val2, long mask)
{
	/* Pressure channel is still WiP */
	uint16_t raw;
	struct lps25hb_priv *priv = iio_priv(indio_dev);
	mutex_lock(&priv->lock);
	raw = lps25hb_get_temp_pressure(priv);
        mutex_unlock(&priv->lock);
	priv->temp = raw; 
	switch (mask) {
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
                case IIO_TEMP:
			/* Switch to float when available, for now it's useless. */
                        *val = LPS25HB_TEMP_OFFSET;
                        return IIO_VAL_INT;  
                default:
                        return -EINVAL;
                }
                break;
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_PRESSURE:
			*val = priv->pressure;
                        return IIO_VAL_INT;
		case IIO_TEMP:
			*val = priv->temp;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
		break;
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_PRESSURE:
			*val = 0;
			*val2 = 0;
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_TEMP:
			*val = LPS25HB_TEMP_SCALE;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	return -EINVAL;
}

static const struct iio_info lps25hb_info = {
	.read_raw	= &lps25hb_read_raw,
};

static int lps25hb_probe(struct i2c_client *client,
		      const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct iio_dev *indio_dev;
	struct lps25hb_priv *priv;
        int ret;
	indio_dev = devm_iio_device_alloc(dev, sizeof(*priv));
	if (!indio_dev)
		return -ENOMEM;

	priv = iio_priv(indio_dev);
	priv->client = client;
	mutex_init(&priv->lock);
        indio_dev->channels = lps25hb_channels;
	indio_dev->num_channels = ARRAY_SIZE(lps25hb_channels);
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
        indio_dev->info = &lps25hb_info;
	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(dev, "Failed to register IIO device\n");
	}
	i2c_set_clientdata(client, indio_dev);
	return 0;

}

static int lps25hb_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unregister(indio_dev);

	return 0;
}

static const struct i2c_device_id lps25hb_id[] = {
	{ "lps25hb", 1 },
	{ },
};
MODULE_DEVICE_TABLE(i2c, lps25hb_id);

static struct i2c_driver lps25hb_driver = {
	.driver = {
		.name	= "lps25hb",
	},
	.probe		= lps25hb_probe,
	.remove         = lps25hb_remove,
	.id_table       = lps25hb_id,
};
module_i2c_driver(lps25hb_driver);

MODULE_AUTHOR("Hristo Hristov <me@hhristov.info>");
MODULE_DESCRIPTION("I2C driver for LPS25HB Sensor");
MODULE_LICENSE("GPL v2");
