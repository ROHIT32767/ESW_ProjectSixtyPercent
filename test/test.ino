#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "redmi";
const char *pass = "redmi123";

void setup()
{
    Serial.begin(115200);

    WiFi.begin(ssid, pass);
    Serial.print(".");
    delay(3000);

    while (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(ssid, pass);
        Serial.print(".");
        delay(3000);
    }

    Serial.println("Connected to WIFI");
}

void loop()
{
    
}