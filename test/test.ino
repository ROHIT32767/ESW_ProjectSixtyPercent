#include <WiFi.h>

char *ssid = "redmi";
char *pass = "redmi123";

void setup()
{
    Serial.begin(115200);

    WiFi.begin(ssid, pass);
    Serial.print(".");
    delay(5000);
    while (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(ssid, pass);
        Serial.print(".");
        delay(5000);
    }
    Serial.println("Connected to WIFI");
}

void loop()
{

}