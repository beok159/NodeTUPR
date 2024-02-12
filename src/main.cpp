#include "core.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C	u8g2(U8G2_R0);
BluetoothSerial							ESP32BT;
WiFiServer									server(80);
HTTPClient									http;

device_t NodeDevice;

void setup()
{
	EEPROM.begin(255);
	Serial.begin(115200);
	u8g2.begin();
	ESP32BT.begin("NodeTUPR");

	NodeDevice.bluetooth = 0;
	NodeDevice.wifi = 0;

	pinMode(LED_BUILTIN, OUTPUT);


	Serial.println("Bluetooth device is ready to pair");
	u8g2.setFont(u8g2_font_ncenB08_tr);
	u8g2.drawStr(0, 10, "Menu C/R And Y/n");
	u8g2.sendBuffer();

	while (NodeDevice.wifi == 0)
	{
		NodeDevice.count = 0;
		u8g2.drawStr(0, 60, "Wifi");
		if (ESP32BT.hasClient())
		{
			ft_putstr_BT("menu: setup-esp32s (TUPR-NODE)\n1:\n2:\n3:", ESP32BT);
			digitalWrite(LED_BUILTIN, HIGH);
			while (1)
			{
				if (ESP32BT.available())
				{
				}
			}
		}
		else
		{
			digitalWrite(LED_BUILTIN, LOW);
		}
		u8g2.sendBuffer();
	}
	EEPROM.end();
}

void loop()
{
	u8g2.firstPage();
	do
	{
		u8g2.clearDisplay();
		u8g2.setFont(u8g2_font_ncenB08_tr);
		u8g2.drawStr(0, 10, "RUNNING...");
		u8g2.sendBuffer();
	} while(u8g2.nextPage());
}
