#include <RunningAverage.h>
#include <WiFi.h>
#include <HTTPClient.h>


// ESP32 Touch Read Setup
// See Touch pins at https://wiki.dfrobot.com/FireBeetle_Board_ESP32_E_SKU_DFR0654#target_5

RunningAverage myRA(100);

const uint8_t touchPins[] = { T0, T1, T3, T4, T5, T6 };

// Hortus wifi
const char* ssid = "PIP";
const char* password = "plantispresent10";
String serverName = "http://192.168.86.240:9980";

const char* touchEndpoint = "/touchdialog?id=";
const char* healthcheckEndpoint = "/healthcheck?id=";

unsigned long startMillis = millis();
unsigned long currentMillis = 0;
unsigned long RETRY_INTERVAL = 5000;

const int BOARDNUM = 0;
const int HEARTBEAT_INTERVAL = 60000;

void sendRequest(String url) {
    HTTPClient http;
    http.begin(url.c_str());

    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
}

void setup() {
  Serial.println("TOUCH INTERACTIVE Attempting to connect");
  // Attempting to connect to SSID:

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Wifi was connected");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  //for reading the values in the Serial Monitor
  Serial.begin(115200);
  delay(1000);

  myRA.clear();

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  currentMillis = millis();

  // if the server's disconnected, reconnect:
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - startMillis >= RETRY_INTERVAL)) {
    WiFi.disconnect();
    WiFi.reconnect();
    return;
  }

   Serial.print((String) "[ ID " + BOARDNUM +" ] " );
  //loop through all the touchPins
  for (int i = 0; i < 6; i++) {
   Serial.print("| "+ (String)i +" " + touchRead(touchPins[i]));
  }
   Serial.println();


  delay(50);

  myRA.addValue(touchRead(T1));

  //this value will need to be tweaked based on cable length & plant size etc.
  if (myRA.getAverage() - touchRead(T1) > 15) {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    // Serial.print
    String sensorTouchedUrl = serverName + touchEndpoint + BOARDNUM + "&pin=" + T1;
    sendRequest(sensorTouchedUrl);
  } else {
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  }

  if (currentMillis - startMillis >= HEARTBEAT_INTERVAL) {
    String heartbeatUrl = serverName + healthcheckEndpoint + BOARDNUM;
    sendRequest(heartbeatUrl);
    startMillis = currentMillis;
  }
}
