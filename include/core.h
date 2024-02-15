#ifndef CORE_NODE_H
# define CORE_NODE_H
# include <Arduino.h>
# include <U8g2lib.h>
# include <SPI.h>
// # include <Wire.h>
# include <WiFi.h>
# include <HTTPClient.h>

# ifndef DELAY_SENSOR
# 	define DELAY_SENSOR 120000
# endif
# ifndef TIMEOUT
# 	define TIMEOUT 120000
# endif
# ifndef SERIAL_BEGIN
# 	define SERIAL_BEGIN 115200
# endif

// Defual Value Set
# ifndef SSID
# 	define SSID ""
# endif
# ifndef PASSWORD
# 	define PASSWORD ""
# endif
# ifndef TOKEN
# 	define TOKEN ""
# endif

# ifndef TRIG_PIN
# 	define TRIG_PIN 19
# endif
# ifndef ECHO_PIN
# 	define ECHO_PIN 18
# endif

# ifndef DETECT_COUNT
# 	define DETECT_COUNT 5
# endif
# ifndef DETECT_DISTANCE
# 	define DETECT_DISTANCE 270
# endif

typedef struct time_d
{
	unsigned long	last_time;
	unsigned int	timedelay;
}					time_d;

typedef struct device_t
{
	int	wifi;
} device_t;

#endif
