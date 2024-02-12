#ifndef CORE_NODE_H
# define CORE_NODE_H
# include <Arduino.h>
# include <U8g2lib.h>
# include <SPI.h>
// # include <Wire.h>
# include <WiFi.h>
# include <HTTPClient.h>
# include <BluetoothSerial.h>
# include <EEPROM.h>

// Check if Bluetooth is available
# if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
  #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
# endif

// Check Serial Port Profile
# if !defined(CONFIG_BT_SPP_ENABLED)
  #error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
# endif

typedef struct time_d
{
	unsigned long	last_time;
	unsigned int	timedelay;
}					time_d;

typedef struct device_t
{
	int bluetooth;
	int wifi;
	int count;
} device_t;

// typedef struct display_t
// {
// 	uint32_t		page_id;
// }					display_t;

void	ft_putstr_BT(const char *str, BluetoothSerial &BT);

#endif
