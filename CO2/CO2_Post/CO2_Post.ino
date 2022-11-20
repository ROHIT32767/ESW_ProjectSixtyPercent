#include <WiFi.h>
#include <HTTPClient.h>
#include <ThingSpeak.h>
#include <PubSubClient.h>

#define PRANA_PIN 19

char *ssid = "redmi";
char *pass = "redmi123";

String cse_ip = "192.168.1.16";
String cse_port = "8080";

String server = "http://" + cse_ip + ":" + cse_port + "/~/in-cse/in-name/";
String ae = "Sensor_Readings";
String cnt[] = {"Prana_PM2.5", "Prana_PM10", "CO2_Levels", "VOC_Levels", "Temperature", "Humidity"};

unsigned long duration, th, tl;
int ppm_CO2;

const char *server_mqtt = "mqtt3.thingspeak.com";
char *Write_Api_Key = "MT7RVJ6QVMI3LO7X";
char *Read_Api_Key = "86FKCRBLN1IJ3G0X";
char *mqtt_clientID = "OjkuKSsAOB8SGBwKKwovFio"; //
char *pubChannelID = "1904939";
const char *mqtt_password = "2S30jiD1Joarlobggy6yg5ym"; //
int channel_ID = 1904939;

WiFiClient client;
PubSubClient mqttClient(server_mqtt, 1883, client);

void mqttConnect()
{
	while (mqttClient.connected() == 0)
	{
		Serial.println("Connecting to mqtt client");
		if (mqttClient.connect(mqtt_clientID, mqtt_clientID, mqtt_password))
		{
			Serial.println("Connected to MQTT");
		}
		else
		{
			Serial.println("Unable to connect to MQTT, Trying again");
			delay(5000);
		}
	}
}

void mqtt_reconnect()
{
	if (!mqttClient.connected())
	{
		mqttConnect();
	}
	mqttClient.loop();
}

void mqtt_Publish()
{
	Serial.print("inside Publish");
	String topicString = "channels/" + String(pubChannelID) + "/publish";
	mqtt_reconnect();
	delay(1000);
	String dataString = "field3=" + String(ppm_CO2);
	mqttClient.publish(topicString.c_str(), dataString.c_str());
	mqtt_reconnect();
	delay(1000);


}

void CreateCICO2()
{
	HTTPClient http;
	http.begin(server + ae + "/" + cnt[2] + "/");
	http.addHeader("X-M2M-Origin", "admin:admin");
	http.addHeader("Content-Type", "application/json;ty=4");
	String body = "{\"m2m:cin\": {\"cnf\": \"application/json\",\"con\": " + String(ppm_CO2) + "}}";

	int response = http.POST(body);
	Serial.println(response);
	if (response == -1)
	{
		Serial.println("Unable to connect");
	}
	http.end();
}

void setup()
{
	Serial.begin(115200);

	WiFi.begin(ssid, pass);
	Serial.print(".");
	delay(1000);
	while (WiFi.status() != WL_CONNECTED)
	{
		WiFi.begin(ssid, pass);
		Serial.print(".");
		delay(1000);
	}
	Serial.println("Connected to WIFI");
	ThingSpeak.begin(client);
}

void loop()
{
	th = pulseIn(PRANA_PIN, HIGH, 2008000) / 1000;
	tl = 1004 - th;
	ppm_CO2 = 2000 * (th - 2) / (th + tl - 4);

	if (ppm_CO2 <= 1000)
		Serial.print(" Co2 Concentration: ");
	Serial.println(ppm_CO2);

	// int x = ThingSpeak.writeField(1904939, 3, ppm_CO2, "MT7RVJ6QVMI3LO7X");
	// Serial.println(x);
	delay(1000);
}