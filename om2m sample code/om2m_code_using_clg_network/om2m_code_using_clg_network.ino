#include <HTTPClient.h>
#include <WiFi.h>
#include <time.h>

#define MAIN_SSID "wifi-name"
#define MAIN_PASS "wifi-password"
#define CSE_IP "esw-onem2m.iiit.ac.in"
#define CSE_PORT 443
#define OM2M_ORGIN "aaaaa:aaaaaa"
#define OM2M_MN "/~/in-cse/in-name/"
#define OM2M_AE "Team-41"
#define OM2M_DATA_CONT "Node-1/Data"
#define INTERVAL 15000L

const char * ntpServer = "pool.ntp.org";

long randNumber;
long int prev_millis = 0;
unsigned long epochTime;

HTTPClient http;

unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime( & timeinfo)) {
    //Serial.println("Failed to obtain time");
    return (0);
  }
  time( & now);
  return now;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(MAIN_SSID, MAIN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("#");
  }
  configTime(0, 0, ntpServer);
}

void loop() {
  int occupancy = random(0,1);
  int distance = random(0,400);
  
  if (millis() - prev_millis >= INTERVAL) {
    epochTime = getTime();
    String data;
    String server = "http://" + String() + CSE_IP + ":" + String() + CSE_PORT + String() + OM2M_MN;

    http.begin(server + String() + OM2M_AE + "/" + OM2M_DATA_CONT + "/");

    http.addHeader("X-M2M-Origin", OM2M_ORGIN);
    http.addHeader("Content-Type", "application/json;ty=4");
    http.addHeader("Content-Length", "100");

    data = "[" + String(epochTime) + ", " + String(occupancy) + ", " + String(distance) +   + "]"; 
    String req_data = String() + "{\"m2m:cin\": {"

      +
      "\"con\": \"" + data + "\","

      +
      "\"lbl\": \"" + "V1.0.0" + "\","

      //+ "\"rn\": \"" + "cin_"+String(i++) + "\","

      +
      "\"cnf\": \"text\""

      +
      "}}";
    int code = http.POST(req_data);
    http.end();
    Serial.println(code);
    prev_millis = millis();
  }
  delay(500);
}
