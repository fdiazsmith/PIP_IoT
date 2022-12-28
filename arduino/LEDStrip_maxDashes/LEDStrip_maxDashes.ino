/* 
MINI README:
This sketch is for controlling a LED strip with an Arduino.
It uses the FastLED library for now
The goal is to extend or to do a chip agnostic library for controlling LED strips.

It develop for the firebeetle esp32 board.
It uses the following pins:
for SPI: 18 sck (clock), 23 mosi (data out), 19 miso (data in)

it has a simple webserver to control the LED strip functions

This was develop in the Arduino IDE 1.8.5
using visual studio code as editor and compiling and uploading with the arduino-cli via the terminal.
I recommend this set up as it is much faster than the Arduino IDE. though you need to add it to the path, etc.ok it's a bit of a hassle but it's worth it.


You still need the IDE to do the board manager and library manager stuff as well as finding the serial port.

The arduino-cli can be found here: https://arduino.github.io/arduino-cli/0.29/
The basic coomands are:
arduino-cli compile -b firebeetle32:esp32:firebeetle32  ./
arduino-cli upload -b firebeetle32:esp32:firebeetle32 -p COM4  ./

author: fer
date: 2020-02-01

 */
#include <vector>  // Include the vector class
#include <FastLED.h>
#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <EEPROM.h>

#include "Dash.h"

#define EEPROM_SIZE 5  // 4 bytes for the IP address

const char* ssid = "PIP";
const char* password = "plantispresent10";
const IPAddress defaultIP(192, 168, 86, 155);  // assign a static IP to your ESP32
const IPAddress gateway(192, 168, 86, 1);
const IPAddress subnet(255, 255, 255, 0);

// the start address of the EEPROM memory where we will store the IP address
const int eepromStartAddress = 0;

WebServer server(80);
// How many leds in your strip?
#define NUM_LEDS 510
#define DATA_PIN 23
#define CLOCK_PIN 18
#define MAX_DASHES = 6;

unsigned long currentMillis = 0;
unsigned long RESTART_INTERVAL = 360000;

// Define the array of leds
CRGB leds[NUM_LEDS];
int secSize = 10;
int j = 0;
int k = 0;

// create an array of Dashes with an amount set by MAX_DASHES
Dash* allDashes[MAX_DASHES];

// Create a vector of Dash objects
std::vector<Dash> dashes;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup starting: ");
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
  // create a variable to hold struct data
  setupServer();
  // initialize the static array of Dash objects
  for (int i = 0; i < MAX_DASHES; i++) {
    allDashes[i] = new Dash(NUM_LEDS);
    //note that array have a different syntax for accessing the elements
    allDashes[i]->setup(10, CRGB::Green, 5, true);
  }

  // Create a vector of Dash objects
  // Use the push_back() method to add elements to the vector
  for (int i = 0; i < 1; i++) {
    Dash dash(NUM_LEDS);
    // Push the Dash object to the end of the vector
    dashes.push_back(dash);
  }

  dashes[0].setup(10, CRGB::Green, 5, true);
  dashes[0].bounce = true;
  dashes[0].life = 3.0;

  turnOff();
  FastLED.show();
}

void loop() {
  turnOff();
  FastLED.show();
  currentMillis = millis();

  for (int i = 0; i < MAX_DASHES; i++) {
    dashes[i].tick_ms();

    dashes[i].mover();
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] += dashes[i].leds[j];
    }

    if (dashes[i].kill) {
      dashes.erase(dashes.begin() + i);
    }
  }

  FastLED.show();
  server.handleClient();
}

void turnOff() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
}
