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
#include <vector> // Include the vector class
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

// Create a vector of Dash objects
std::vector<Dash> dashes;

/*
Note: I am creating two alternatives to handle the Dash objects
one is using a static array of Dash objects
the other is using a vector of Dash objects

The vector is a dynamic array that can be resized at runtime
The static array is a fixed size array that cannot be resized at runtime

I am leaning towards the vector because it is more dynamic and can be resized at runtime
but I leave the static array code here for reference

*/

void setup() { 
	Serial.begin(115200);
	Serial.println("resetting");
	FastLED.addLeds<APA102,DATA_PIN, CLOCK_PIN,BGR>(leds,NUM_LEDS);
	FastLED.setBrightness(100);
	// create a variable to hold struct data
	setupServer();
	// initialize the static array of Dash objects
	for(int i = 0; i < 15; i++){
		allDashes[i] = new Dash(NUM_LEDS);
		//note that array have a different syntax for accessing the elements
		allDashes[i]->setup(10, CRGB::Green, 50, true);
	}

	// Create a vector of Dash objects
	// Use the push_back() method to add elements to the vector
	for (int i = 0; i < 3; i++) {
		Dash dash(NUM_LEDS);
		// Push the Dash object to the end of the vector
		dashes.push_back(dash);
	}

	// example of how to access the vector elements
	// for (int i = 0; i < dashes.size(); i++) {
	// 	dashes[i].setup();
	// }

	dashes[0].setup(10, CRGB::Green, 50, true);
	dashes[1].setup(20, CRGB::Yellow, 100, true);
	dashes[2].setup(30, CRGB::Blue, 300, true);
	// two different ways to remove an element from the vector
	// the idea is that each dash  can have a kill me switch and then we remove it from the vector
	// dashes.erase(dashes.begin() + 5);

	// Use the pop_back() method to remove the last Dash object from the vector
	// dashes.pop_back();

	// Use the vector
	// for (int i = 0; i < dashes.size(); i++) {
	// 	Serial.println(dashes[i].color);
	// }
}



void loop() { 

  turnOff();
  FastLED.show();

   for (int i = 0; i < dashes.size(); i++) {
		dashes[i].tick_ms();
		
		dashes[i].mover();
		for(int j = 0; j < NUM_LEDS; j++){
			leds[j] += dashes[i].leds[j];
		}
	}
	// dashes[0].tick_ms();
	
	// dashes[0].mover();
	// for(int j = 0; j < NUM_LEDS; j++){
	// 	leds[j] += dashes[0].leds[j];
	// }
	
	// Serial.println(dashes[0].pos);
	FastLED.show();
	
	server.handleClient();
}


void turnOff(){
    for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
}
