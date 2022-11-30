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

// Strip strip(NUM_LEDS);
// create a strut to hold the data for the shape
struct shape{
	int pos;
	int len;
	bool wrap;
	CRGB color;
	unsigned long lastMillis;
	int delay_ms;
	CRGB leds[NUM_LEDS];

};
// TODO: create a struct maker for the shape, to make it easier to create a shape
// can we get an array of structs?
// shape setupShape(int len, int delay_ms, bool wrap, CRGB color){
//     shape s;
//     s.pos = 0;
//     s.len = len;
//     s.delay_ms = delay_ms;
//     s.wrap = wrap;
//     s.color = color;
//     return s;
// }
shape s; 
shape b; 
// appartently this wroks
shape allShapes[10];
void setup() { 
	Serial.begin(115200);
	Serial.println("resetting");
	FastLED.addLeds<APA102,DATA_PIN, CLOCK_PIN,BGR>(leds,NUM_LEDS);
	FastLED.setBrightness(100);
	// create a variable to hold struct data
	setupServer();
	s.len = 10;
	s.wrap = true;
	s.color = CRGB::Red;
	s.delay_ms = 100;

	b.len = 20;
	b.wrap = false;
	b.color = CRGB::Blue;
	b.delay_ms = 30;

}



void loop() { 
	// fill(CRGB::Yellow);
	turnOff();
	FastLED.show();
	// create a for loop to move the index of the leds
	tick_bounce_ms(s);
	tick_ms(b);

	mover(s);
	mover(b);
	FastLED.show();
	server.handleClient();
	//  fill_solid( leds, NUM_LEDS, CRGB( 200, 116, 110));
}
