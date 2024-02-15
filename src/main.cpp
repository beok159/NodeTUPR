#include "core.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);
WiFiServer server(80);
HTTPClient http;

device_t NodeDevice;

void setup()
{
	time_d TimeOut;
	uint8_t loop;

	TimeOut.last_time = 0;
	TimeOut.timedelay = TIMEOUT;
	NodeDevice.wifi = 0;
	loop = 1;

	u8g2.begin();
	Serial.begin(SERIAL_BEGIN);
	WiFi.begin(SSID, PASSWORD);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(TRIG_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);

	u8g2.setFont(u8g2_font_ncenB08_tr);
	u8g2.drawStr(0, 10, "Check WIFI");
	u8g2.sendBuffer();

	while (loop == 1)
	{
		u8g2.clearBuffer();
		if ((millis() - TimeOut.last_time) > TimeOut.timedelay && WiFi.status() != WL_CONNECTED)
		{
			TimeOut.last_time = millis();
			ESP.restart();
		}
		if (WiFi.status() == WL_CONNECTED)
		{
			http.begin("https://notify-api.line.me/api/notify");
			http.addHeader("Content-Type", "application/x-www-form-urlencoded");
			http.addHeader("Authorization", "Bearer " + String(TOKEN));
			NodeDevice.wifi = 1;
			loop = 0;
		}
		else
		{
			digitalWrite(LED_BUILTIN, HIGH);
			delay(100);
			digitalWrite(LED_BUILTIN, LOW);
			delay(100);
		}
	}
}

void loop()
{
	static unsigned long lastSensorCheckTime;
	static unsigned long lastDetectTime;
	unsigned long currentTime;
	static int count;
	int httpResponseCode;
	long duration;
	int sensor_value;
	String postData;

	
	lastSensorCheckTime = 0;
	lastDetectTime = 0;
	currentTime = millis();
	count = 0;
	postData = "message=ตรวจพบความผิดปกติของระดับน้ำ\n";
	if (currentTime - lastSensorCheckTime >= 3000)
	{
		lastSensorCheckTime = currentTime;

		digitalWrite(TRIG_PIN, LOW);
		delayMicroseconds(2);
		digitalWrite(TRIG_PIN, HIGH);
		delayMicroseconds(5);
		digitalWrite(TRIG_PIN, LOW);
		duration = pulseIn(ECHO_PIN, HIGH);
		sensor_value = duration / 29 / 2;

		Serial.printf("%d\n", sensor_value);
		if (sensor_value > DETECT_DISTANCE)
		{
			count++;
			if (count >= DETECT_COUNT && currentTime - lastDetectTime >= DELAY_SENSOR)
			{
				postData = "message=ตรวจพบความผิดปกติของระดับน้ำ\n";
				httpResponseCode = http.POST(postData);
				// if (httpResponseCode > 0)
				// {
				// 	Serial.print("HTTP Response code: ");
				// 	Serial.println(httpResponseCode);
				// 	String response = http.getString();
				// 	Serial.println(response);
				// }
				// else
				// {
				// 	Serial.print("Error sending request. HTTP Response code: ");
				// 	Serial.println(httpResponseCode);
				// }
				http.end();
				count = 0;
				lastDetectTime = currentTime;
			}
		}
	}
	u8g2.firstPage();
	do
	{
		u8g2.clearBuffer();
		if (WiFi.status() != WL_CONNECTED)
		{
			u8g2.drawStr(0, 10, "Restart..");
			u8g2.sendBuffer();
			ESP.restart();
		}
		else
		{
			u8g2.drawStr(0, 10, "RUNNIG..");
			u8g2.drawStr(0, 40, WiFi.localIP().toString().c_str());
		}
		u8g2.sendBuffer();
	} while (u8g2.nextPage());
}
