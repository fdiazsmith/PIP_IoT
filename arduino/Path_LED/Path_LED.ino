#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 170 

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 23
#define CLOCK_PIN 18

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
	Serial.begin(57600);
	Serial.println("starting");
	FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds,NUM_LEDS);
	FastLED.setBrightness(100);
}

void loop() {
  fill_solid( leds, NUM_LEDS, CRGB(255,230,0));
  FastLED.show();
}
