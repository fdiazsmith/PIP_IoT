/* 
MINI README:
This sketch is for controlling a LED strip with an Arduino.
It uses the FastLED library for now
The goal is to extend or to do a chip agnostic library for controlling LED strips.

It develop for the firebeetle esp32 board.
It uses the following pins:
for SPI: 18 sck (clock), 23 mosi (data out), 19 miso (data in)

Still need a simple webserver to control the LED strip functions

This was develop in the Arduino IDE 1.8.5
using visual studio code as editor and compiling and uploading with the arduino-cli via the terminal.
I recommend this set up as it is much faster than the Arduino IDE. though you need to add it to the path, etc.


You still need the IDE to do the board manager and library manager stuff as well as finding the serial port.

The arduino-cli can be found here: https://arduino.github.io/arduino-cli/0.29/
The basic coomands are:
arduino-cli compile -b firebeetle32:esp32:firebeetle32  ./
arduino-cli upload -b firebeetle32:esp32:firebeetle32 -p COM4  ./
 

author: fer
date: 2020-02-01

 */
#include <FastLED.h>
#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "Dash.h"

const char* ssid = "HILOLA";
const char* password = "hotspotforyourhotstuff";

WebServer server(80);
// How many leds in your strip?
#define NUM_LEDS  170 
#define DATA_PIN 23
#define CLOCK_PIN 18

// Define the array of leds
CRGB leds[NUM_LEDS];
int secSize = 10;
int j = 0;
int k = 0;


// Dash dash(NUM_LEDS);
// create an array  of 15 Dash
Dash *allDashes[15];


void setup() { 
	Serial.begin(115200);
	Serial.println("resetting");
	FastLED.addLeds<APA102,DATA_PIN, CLOCK_PIN,BGR>(leds,NUM_LEDS);
	FastLED.setBrightness(100);
	// create a variable to hold struct data
	setupServer();
	// create a for loop to initialize the array of dashes
	for(int i = 0; i < 15; i++){
		allDashes[i] = new Dash(NUM_LEDS);
		allDashes[i]->setup();
	}
}



void loop() { 
	// fill(CRGB::Yellow);
	// turnOff();
	// FastLED.show();
	// // create a for loop to move the index of the leds
	// tick_bounce_ms(s);
	// tick_ms(b);

	// mover(s);
	// mover(b);
	// FastLED.show();
	server.handleClient();
	//  fill_solid( leds, NUM_LEDS, CRGB( 200, 116, 110));
}
