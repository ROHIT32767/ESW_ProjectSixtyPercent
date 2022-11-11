#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = ":heisrightyouknow:";
const char *pass = "ESW_PASS1234";

String cse_ip = "esw-onem2m.iiit.ac.in";
String cse_port = "443";

String server = "https://" + cse_ip + ":" + cse_port + "/~/in-cse/in-name/";
String ae = "Team-18";
String cnt[] = {"Prana_PM2.5", "Prana_PM10", "CO2_Levels", "VOC_Levels", "Temperature", "Humidity"};

void setup()
{
    Serial.begin(115200);

    while (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(ssid, pass);
        Serial.print(".");
        delay(3000);
    }

    Serial.println("Connected to WIFI");

    for (int i = 0; i < 6; i++)
    {
        HTTPClient http;
        http.begin(server + ae + "/" + cnt[i] + "/");
        http.addHeader("X-M2M-Origin", "lp2MgQ:e4A#PT");
        http.addHeader("Content-Type", "application/json;ty=4");
        String body = "{\"m2m:cin\": {\"cnf\": \"application/json\",\"con\": " + String(10) + "}}";

        int response = http.POST(body);
        Serial.println(response);
        http.end();
        delay(100);
    }
}

void loop()
{
    
}