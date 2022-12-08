#include <Arduino.h>
#include <FastLED.h>
#include "Dash.h"

Dash::Dash(int num_leds) {
   	pos = 0;
	_num_leds = num_leds;
	bool wrap = false;
	color = CRGB::Red;
	_lastMillis = 0;
	delay_ms = 100;
	leds  = new CRGB[_num_leds];
}

void Dash::setup(){
    _num_leds = 10;
	wrap = true;
	color = CRGB::Red;
	delay_ms = 100;
}

void Dash::fadeall(){
    for(int i = 0; i < _num_leds; i++) {
         leds[i].nscale8(250); 
        } 
}



void Dash::fill( ){
    for(int i = 0; i < _num_leds; i++) {
        leds[i] = color;
     
    }
}
