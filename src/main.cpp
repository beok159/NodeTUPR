#include "core.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C	u8g2(U8G2_R0);
BluetoothSerial							ESP32BT;
WiFiServer									server(80);
HTTPClient									http;

device_t NodeDevice;

void setup()
{
	time_d		TimeOut;
	uint8_t		loop;

	TimeOut.last_time = 0;
	TimeOut.timedelay = TIMEOUT;
	NodeDevice.bluetooth = 0;
	NodeDevice.wifi = 0;
	NodeDevice.datasave = 0;
	loop = 1;

	u8g2.begin();
	Serial.begin(SERIAL_BEGIN);
	ESP32BT.begin(NAME_BT_DEIVICE);
	EEPROM.begin(EEPROM_SIZE);

	pinMode(LED_BUILTIN, OUTPUT);

	u8g2.setFont(u8g2_font_ncenB08_tr);
	u8g2.drawStr(0, 10, "Check DATAbase!");
	u8g2.sendBuffer();

	while (loop == 1)
	{
		u8g2.clearBuffer();
		if ((millis() - TimeOut.last_time) > TimeOut.timedelay && !ESP32BT.hasClient())
		{
			TimeOut.last_time = millis();
			if (NodeDevice.datasave == 0)
				ESP.restart();
			else
				loop = 0;
		}
		while (ESP32BT.hasClient())
		{
			digitalWrite(LED_BUILTIN, HIGH);
			u8g2.drawStr(0, 10, "Used Bluetooth");
			u8g2.sendBuffer();
		}
		digitalWrite(LED_BUILTIN, LOW);
		continue	;
	}

	// while (NodeDevice.wifi == 0)
	// {
	// 	u8g2.drawStr(0, 60, "Wifi");
	// 	if (ESP32BT.hasClient())
	// 	{
	// 		ft_putstr_BT("menu: setup-esp32s (TUPR-NODE)\n1:\n2:\n3:", ESP32BT);
	// 		digitalWrite(LED_BUILTIN, HIGH);
	// 		if (ESP32BT.available())
	// 		{
	// 		}
	// 	}
	// 	else
	// 	{
	// 		digitalWrite(LED_BUILTIN, LOW);
	// 	}
	// 	u8g2.sendBuffer();
	// }
	EEPROM.end();
}

void loop()
{
	digitalWrite(LED_BUILTIN, LOW);
	u8g2.firstPage();
	do
	{
		u8g2.clearDisplay();
		// u8g2.setFont(u8g2_font_ncenB08_tr);
		u8g2.drawStr(0, 10, "RUNNING...");
		u8g2.sendBuffer();
	} while(u8g2.nextPage());
}
