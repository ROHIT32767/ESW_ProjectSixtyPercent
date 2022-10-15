/***************************************************
  This is an example for the SHT4x Humidity & Temp Sensor

  Designed specifically to work with the SHT4x sensor from Adafruit
  ----> https://www.adafruit.com/products/4885

  These sensors use I2C to communicate, 2 pins are required to
  interface
 ****************************************************/

#include "Adafruit_SHT4x.h"
#include "Adafruit_SGP40.h"

#define PRANA_PIN 19

Adafruit_SHT4x sht4 = Adafruit_SHT4x();
Adafruit_SGP40 sgp;
unsigned long duration, th, tl;
int ppm_CO2;

void setup()
{
  Serial.begin(115200);

  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit VOC test");
  if (!sht4.begin())
  {
    Serial.println("Couldn't find SHT4x");
    while (1)
      delay(1);
  }
  if (!sgp.begin())
  {
    Serial.println("SGP40 sensor not found :(");
    while (1)
      ;
  }

  Serial.println("Found SHT4x sensor");
  Serial.print("Serial number 0x");
  Serial.println(sht4.readSerial(), HEX);

  // You can have 3 different precisions, higher precision takes longer
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

  // You can have 6 different heater settings
  // higher heat and longer times uses more power
  // and reads will take longer too!
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
}

int counter = 0;
void loop()
{
  sensors_event_t humidity, temp;
  uint16_t sraw;
  int32_t voc_index;

  uint32_t timestamp = millis();
  sht4.getEvent(&humidity, &temp); // populate temp and humidity objects with fresh data
  timestamp = millis() - timestamp;

  float t = temp.temperature;
  float h = humidity.relative_humidity;
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" degrees C");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println("% rH");

  Serial.print("Read duration (ms): ");
  Serial.println(timestamp);

  sraw = sgp.measureRaw(t, h);
  Serial.print("Raw measurement: ");
  Serial.println(sraw);

  voc_index = sgp.measureVocIndex(t, h);
  Serial.print("Voc Index: ");
  Serial.println(voc_index);

  th = pulseIn(PRANA_PIN, HIGH, 2008000) / 1000;
  tl = 1004 - th;
  ppm_CO2 = 2000 * (th - 2) / (th + tl - 4);

  if (ppm_CO2 > 1000) {
    Serial.println(ppm_CO2);
    //ThingSpeak.setField(1, ppm_CO2);
  }
  else {
    Serial.print(" Co2 Concentration: ");
    Serial.println(ppm_CO2);
    //ThingSpeak.setField(1, ppm_CO2);
    //    Serial.println(" ppm_CO2");
  }

  delay(1000);
}