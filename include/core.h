#ifndef CORE_NODE_H
# define CORE_NODE_H
# include <Arduino.h>
# include <U8g2lib.h>
# include <SPI.h>
// # include <Wire.h>
# include <WiFi.h>
# include <HTTPClient.h>
# include <BluetoothSerial.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C	u8g2(U8G2_R0);
BluetoothSerial							ESP32BT;
WiFiServer									server(80);
HTTPClient									http;

typedef struct time_d
{
	unsigned long	last_time;
	unsigned int	timedelay;
}					time_d;

typedef struct device_t
{
	int bluetooth;
	int wifi;
} device_t;

// typedef struct display_t
// {
// 	uint32_t		page_id;
// }					display_t;

#endif
