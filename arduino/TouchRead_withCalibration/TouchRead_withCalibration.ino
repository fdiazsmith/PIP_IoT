// SIGNAL SENDER FOR ANALOUGE INPUT
// by Bjorn Karmann
//
// Diviation amounts for different sensors a.k.a. sensitivity
// Flex senor:  10 
// IR sensor:   10

int diviation_amount = 10; // this should be the only variable needing to change depending on the sensor

//===============================================================//

//Constants:
const int ledPin = 3;   //pin 3 has PWM funtion
const int flexPin = A0; //pin A0 to read analog input

// smoothing
const int numReadings = 20; // averging amount
int readings[numReadings];  // the readings from the analog input
int readIndex = 0;          // the index of the current reading
int total = 0;              // the running total
int average = 0;            // the average

// calibration
int current_saved_value;    // uses this to calculate the diviation
int time_interval = 10000;  // time that signal has to be in a new position before calibration
int time_start;

// signal detection
int time_between_signals = 500;     // minimum time between signals
bool startup_sequence = true;
bool signal_fired = false;

// wifi stuff
#include <SPI.h>
#include <WiFi.h>
char ssid[] = "DontPanic";          // your network SSID (name)
char pass[] = "NoBadDays";          // your network password (use for WPA, or use as key for WEP)
char server[] = "www.google.com";   // server adress
int status = WL_IDLE_STATUS;
WiFiClient client;
int keyIndex = 0;  

//===============================================================//

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);     // Set pin 3 as 'output'
  Serial.begin(9600);               // Begin serial communication
  digitalWrite(LED_BUILTIN, LOW);   // Set led off  

  // Attempting to connect to SSID: 
  while (status != WL_CONNECTED) {
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  printWifiStatus();

  // connected to server
  if (client.connect(server, 80)) { 
    // Make a HTTP request:
    Serial.println("connecting to server.");
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println();
  }
  time_start = millis();  
}

void loop() { 

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println("disconnecting from server.");
    client.stop();
    while (true);   // do nothing forevermore:
  }

  //========== SMOOTHING ===========//
  // subtract the last reading
  total = total - readings[readIndex];
  // read from the sensor
  readings[readIndex] = analogRead(flexPin);
  // add the reading to the total
  total = total + readings[readIndex];
  // advance to the next position in the array
  readIndex = readIndex + 1;
  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    readIndex = 0; // wrap around to the beginning
  }
  average = total / numReadings; // calculate the average:
  //=================================//

  //=========== SIGNAL DETECTION ===========//
  // check if movement has acured within the last timer interval
  // if there was no movement we can procees to save the value  
  if(startup_sequence == false && signal_fired == false){
    if(average > current_saved_value + diviation_amount || average < current_saved_value - diviation_amount ){
      // yes diviation accured so reset timer 
      signal_fired = true;                // set signal fired to true
      time_start = millis();              // reset timer to wait the storing of new value
      plot(average, 1400);                // shows spike on monitor
      digitalWrite(LED_BUILTIN, HIGH);    // turn led off              
      if (client.connect(server, 80)) {   // send message to network what is connected
        client.println("GET /search?q=arduino HTTP/1.1");     // Make a HTTP request to send signal
        client.println();
      }
    }
  }
  // now that the signal was fires wait some time before listen for signals again
  if(signal_fired && millis() - time_start >= time_between_signals){
    digitalWrite(LED_BUILTIN, LOW);       // turn led off  
    if(average > current_saved_value + diviation_amount || average < current_saved_value - diviation_amount ){
      // value is still over diviation threshold
    }else{
      signal_fired = false;               // this sets the listening back 
      time_start = millis();              // restart timer
    }
  }
  //=========================================//

  //=========== CALIBRATION =========//
  // if timer does reach interval 
  if(millis()-time_start >= time_interval){  // timeout
    signal_fired = false;                    // this sets the listening back 
    startup_sequence = false;                // only needed on startup
    current_saved_value = average;           // store new baseline for calibration
    time_start = millis();                   // reset timer 
  }
  //=================================//
  
  plot(average, current_saved_value);
  delay(10);  // delay in between reads for stability
}

// Fernando is amazing

// function to plot variables onto the monitor
void plot(int x, int y){
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(900);      // max plot 
  Serial.print(",");
  Serial.println(1400);   // min plot
}

void printWifiStatus() {
  Serial.println("Connected to wifi");

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}