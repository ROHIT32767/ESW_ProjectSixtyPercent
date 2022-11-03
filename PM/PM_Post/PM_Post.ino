#include <SPI.h>
#include <Wire.h>
#include <HTTPClient.h>
#include <WiFi.h>

char *ssid = ":heisrightyouknow:";
char *pass = "ESW_PASS1234";

String cse_ip = "192.168.176.219";
String cse_port = "8080";

String server = "http://" + cse_ip + ":" + cse_port + "/~/in-cse/in-name/";
String ae = "Sensor_Readings";
String cnt[] = {"Prana_PM2.5", "Prana_PM10", "CO2_Levels", "VOC_Levels", "Temperature", "Humidity"};
int pm2 = 1, pm10 = 1;

void CreateCIPM2_5()
{
	HTTPClient http;
	http.begin(server + ae + "/" + cnt[0] + "/");
	http.addHeader("X-M2M-Origin", "admin:admin");
	http.addHeader("Content-Type", "application/json;ty=4");
	String body = "{\"m2m:cin\": {\"cnf\": \"application/json\",\"con\": " + String(pm2) + "}}";

	http.POST(body);
	http.end();
}

void CreateCIPM10()
{
	HTTPClient http;
	http.begin(server + ae + "/" + cnt[1] + "/");
	http.addHeader("X-M2M-Origin", "admin:admin");
	http.addHeader("Content-Type", "application/json;ty=4");
	String body = "{\"m2m:cin\": {\"cnf\": \"application/json\",\"con\": " + String(pm10) + "}}";

	http.POST(body);
	http.end();
}

void ConnectToWifi()
{
	WiFi.begin(ssid, pass);
	while (WiFi.status() != WL_CONNECTED)
	{
		WiFi.begin(ssid, pass);
		delay(3000);
	}
}

unsigned long previous_loop, previous_10, previous_25, prev_time;

byte command_frame[9] = {0xAA, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x67, 0xBB};
byte received_data[9];
int sum = 0;
void send_command(byte command)
{
	command_frame[1] = command;
	int sum = command_frame[0] + command_frame[1] + command_frame[2] + command_frame[3] + command_frame[4] + command_frame[5] + command_frame[8];
	int rem = sum % 256;
	command_frame[6] = (sum - rem) / 256;
	command_frame[7] = rem;
	delay(1000);
	Serial.write(command_frame, 9);
}

bool checksum()
{
	sum = int(received_data[0]) + int(received_data[1]) + int(received_data[2]) + int(received_data[3]) + int(received_data[4]) + int(received_data[5]) + int(received_data[8]);
	if (sum == ((int(received_data[6]) * 256) + int(received_data[7])))
	{
		return true;
	}
	else
		return false;
}
void calculate_pm()
{
	pm2 = int(received_data[4]) * 256 + int(received_data[5]);
	pm10 = int(received_data[2]) * 256 + int(received_data[3]);
	delay(2000);
}

void PM_setup()
{
	send_command(0x01);
}

void PM_Reading()
{
	delay(5000);
	if (millis() - prev_time > 5000)
	{
		send_command(0x02);
		prev_time = millis();
	}
	if (Serial.available())
	{
		Serial.readBytes(received_data, 9);
		if (checksum())
		{
			calculate_pm();
		}
	}
}

void setup()
{
	Serial.begin(9600);
	delay(500);
	ConnectToWifi();
	PM_setup();
}

void loop()
{
	PM_Reading();
	CreateCIPM2_5();
	CreateCIPM10();

	delay(2000);
}
