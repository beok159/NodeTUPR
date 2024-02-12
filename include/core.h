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

// // Check if Bluetooth is available
// # if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
//   #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
// # endif

// // Check Serial Port Profile
// # if !defined(CONFIG_BT_SPP_ENABLED)
//   #error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
// # endif

# ifndef DELAY_TIMEOUT
# 	define DELAY_TIMEOUT 10000
# endif
# ifndef TIMEOUT
# 	define TIMEOUT 30000
# endif
# ifndef SERIAL_BEGIN
# 	define SERIAL_BEGIN 115200
# endif
# ifndef EEPROM_SIZE
# 	define EEPROM_SIZE 255
# endif
# ifndef NAME_BT_DEIVICE
# 	define NAME_BT_DEIVICE "TUPR NODEMCU"
# endif

typedef struct time_d
{
	unsigned long	last_time;
	unsigned int	timedelay;
}					time_d;

typedef struct device_t
{
	int	bluetooth;
	int	wifi;
	int	connect;
	int	datasave;
} device_t;

// typedef struct display_t
// {
// 	uint32_t		page_id;
// }					display_t;

void	putStr_BT(const char *str, BluetoothSerial &BT);

#endif
