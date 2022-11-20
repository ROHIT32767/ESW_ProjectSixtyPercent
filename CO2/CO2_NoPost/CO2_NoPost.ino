#define PRANA_PIN 19
unsigned long duration, th, tl;
int ppm_CO2;

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    th = pulseIn(PRANA_PIN, HIGH, 2008000) / 1000;
    tl = 1004 - th;
    ppm_CO2 = 2000 * (th - 2) / (th + tl - 4);

    Serial.print("Co2 Concentration: ");
    Serial.println(ppm_CO2);
    delay(1000);
}