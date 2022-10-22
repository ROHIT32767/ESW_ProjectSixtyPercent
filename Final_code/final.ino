#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <PubSubClient.h>
#include <ThingSpeak.h>
#include <Adafruit_SHT4x.h>
#include <Adafruit_SGP40.h>
#include <PMS.h>

#define MongoDBPass 0
#define PM2_5 1
#define PM10 2
#define CO2 3
#define VOC 4
#define Temp 5
#define Humid 6
#define ArrSize 7

#define PRANA_PIN 19

float sensorVal[ArrSize] = {0};
Adafruit_SHT4x sht4 = Adafruit_SHT4x();
Adafruit_SGP40 sgp;
unsigned long duration, th, tl;
int ppm_CO2;
PMS pms(Serial2);
PMS::DATA data;

String mongoDBpassword = "ProjectSixtyPercent";

const char *WiFiSSID = ":heisrightyouknow:";
const char *WiFiPassword = "ESW_PASS1234";

const char *mqttServer = "mqtt3.thingspeak.com";
const char *mqttUserName = "Indoor Air Pollution";
const char *clientID = "KREkBxcbLQQyBQgSEywPDQ0";
const char *deviceUserName = "KREkBxcbLQQyBQgSEywPDQ0";
const char *devicePassword = "XZAvgedIieife+/TGiffFwo9";
const char *mqttPassword = "EXH40EH1B3EN2G85";

WiFiClient client;
PubSubClient mqttClient(mqttServer, 1883, client);

const unsigned long writeChannelID = 1878258;
const char *writeAPIKey = "BT4CUUI80PXSGMG3";

String cse_ip = "192.168.123.219"; // YOUR IP from ipconfig/ifconfig
String cse_port = "8080";
String server = "http://" + cse_ip + ":" + cse_port + "/~/in-cse/in-name/";
String ae = "Sensor Readings";
String cnt[] = {"Prana_PM2.5", "Prana_PM10", "CO2_Levels", "VOC_Levels", "Temperature", "Humidity"};

void reconnect()
{
	while (!mqttClient.connected())
	{
		Serial.print("Attempting MQTT connection...");

		if (mqttClient.connect(clientID, deviceUserName, devicePassword))
			Serial.println("Connected to MQTT");
		else
			delay(3000);
	}
}
void ThingSpeakWrite()
{
	for (unsigned int i = 1; i < ArrSize; i++)
	{
		String fieldData = "field" + String(i) + "=" + sensorVal[i];
		String publishData = "channels/" + String(writeChannelID) + "/publish";
		mqttClient.publish(publishData.c_str(), fieldData.c_str());
		delay(1000);
	}
}

void OM2MWrite()
{
	HTTPClient http;

	for (unsigned int i = 1; i < ArrSize; i++)
	{
		http.begin(server + ae + "/" + cnt[i] + "/");
		http.addHeader("X-M2M-Origin", "admin:admin");
		http.addHeader("Content-Type", "application/json;ty=4");

		if ((http.POST("{\"m2m:cin\": {\"cnf\":\"application/json\",\"con\": " + String(sensorVal[i]) + "}}")) == -1)
			Serial.println("UNABLE TO CONNECT TO THE SERVER");
		http.end();
	}
}

void setup()
{
	Serial.begin(115200);
	Serial2.begin(9600);

	Serial.println("Adafruit VOC test");
	if (!sht4.begin())
	{
		Serial.println("Couldn't find SHT4x");
		while (1)
			delay(1);
	}
	if (!sgp.begin())
	{
		Serial.println("SGP40 sensor not found");
		while (1)
			delay(1);
	}

	Serial.println("Found SHT4x sensor");
	Serial.print("Serial number 0x");
	Serial.println(sht4.readSerial(), HEX);

	sht4.setPrecision(SHT4X_HIGH_PRECISION);
	switch (sht4.getPrecision())
	{
	case SHT4X_HIGH_PRECISION:
		Serial.println("High precision");
		break;
	case SHT4X_MED_PRECISION:
		Serial.println("Med precision");
		break;
	case SHT4X_LOW_PRECISION:
		Serial.println("Low precision");
		break;

		Serial.print("Found SHT4x + SGP40 serial #");
		Serial.print(sgp.serialnumber[0], HEX);
		Serial.print(sgp.serialnumber[1], HEX);
		Serial.println(sgp.serialnumber[2], HEX);
	}

	sht4.setHeater(SHT4X_NO_HEATER);
	switch (sht4.getHeater())
	{
	case SHT4X_NO_HEATER:
		Serial.println("No heater");
		break;
	case SHT4X_HIGH_HEATER_1S:
		Serial.println("High heat for 1 second");
		break;
	case SHT4X_HIGH_HEATER_100MS:
		Serial.println("High heat for 0.1 second");
		break;
	case SHT4X_MED_HEATER_1S:
		Serial.println("Medium heat for 1 second");
		break;
	case SHT4X_MED_HEATER_100MS:
		Serial.println("Medium heat for 0.1 second");
		break;
	case SHT4X_LOW_HEATER_1S:
		Serial.println("Low heat for 1 second");
		break;
	case SHT4X_LOW_HEATER_100MS:
		Serial.println("Low heat for 0.1 second");
		break;
	}

	WiFi.mode(WIFI_STA);
	WiFi.begin(WiFiSSID, WiFiPassword);
	delay(3000);
	while (WiFi.status() != WL_CONNECTED)
	{
		WiFi.begin(WiFiSSID, WiFiPassword);
		delay(3000);
		Serial.println("Connecting to WiFi...");
	}
	Serial.println("Successfully connected to WiFi");
	Serial.print("IP address is : ");
	Serial.println(WiFi.localIP());

	mqttClient.setServer(mqttServer, 1883);
}

void loop()
{
	if (!mqttClient.connected())
		reconnect();
	mqttClient.loop();

	sensors_event_t humidity, temp;
	uint16_t sraw;
	int32_t voc_index;
	int pm2_5, pm10;

	sht4.getEvent(&humidity, &temp);

	float t = temp.temperature;
	float h = humidity.relative_humidity;
	Serial.print("Temperature: ");
	Serial.print(t);
	Serial.println(" degrees C");
	Serial.print("Humidity: ");
	Serial.print(h);
	Serial.println("% rH");

	voc_index = sgp.measureVocIndex(t, h);
	Serial.print("Voc Index: ");
	Serial.println(voc_index);

	th = pulseIn(PRANA_PIN, HIGH, 2008000) / 1000;
	tl = 1004 - th;
	ppm_CO2 = 2000 * (th - 2) / (th + tl - 4);

	if (ppm_CO2 > 1000)
		Serial.println(ppm_CO2);
	else
		Serial.print(" Co2 Concentration: " + String(ppm_CO2));

	if (pms.read(data))
	{
		pm2_5 = data.PM_AE_UG_2_5;
		pm10 = data.PM_AE_UG_10_0;
		Serial.println("PM2.5 :" + String(pm2_5) + "(ug/m3)");
		Serial.println("PM10  :" + String(pm10) + "(ug/m3)");
	}

	sensorVal[PM2_5] = pm2_5;
	sensorVal[PM10] = pm10;
	sensorVal[CO2] = ppm_CO2;
	sensorVal[VOC] = voc_index;
	sensorVal[Temp] = t;
	sensorVal[Humid] = h;

	delay(1000);

	ThingSpeakWrite();
	OM2MWrite();
	// MongoDBWrite();
}