#include <Arduino.h>
#include <FastLED.h>
#include "Dash.h"

Dash::Dash(int num_leds) {
   	pos = 0;
	_num_leds = num_leds;
	bool wrap = true;
	color = CRGB::Red;
	_lastMillis = 0;
	delay_ms = 100;
	leds  = new CRGB[_num_leds];
}

void Dash::setup(int length, CRGB mainColor, int delayi, bool wrapindex){
	wrap = wrapindex;
	color = mainColor;
	delay_ms = delayi;
    len = length;
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

void Dash::turnOff( ){
    for(int i = 0; i < _num_leds; i++) {
        leds[i] = CRGB::Black;
    }
}

void  Dash::tick_ms(){
    // check if enough time has passed to update the dash
    if(millis() - _lastMillis > delay_ms){
        // update the dash pos
        pos++;
        // save time of update
        _lastMillis = millis();
        // if wrap is enabled, loop back to the beginning
        if(wrap){
            if(pos >= _num_leds) pos = 0;
        }
    }
}

void  Dash::tick_bounce_ms(){
    // If enough time has passed, update the position
    if(millis() - _lastMillis > delay_ms){
        // If wrap is enabled, simply increment the position
        if(wrap){
            pos++;
            // If we've reached the end of the strip, loop back to the beginning
            if(pos >= _num_leds) pos = 0;
        }
        // If wrap is disabled, increment the position, but stop at the end of the strip
        else{
            pos++;
            if(pos >= _num_leds) pos = _num_leds;
        }
        _lastMillis = millis();
    }
}



// implement mover to take in a struct
void Dash::mover(){
    // leds[pos] = CHSV(255, 255, 255);
    for (int i = 0; i < len; i++){
        /* code */
        float n = (float)i/(float)len;
        int npos =   pos + i;
        if (!wrap){
            // if the section is longer than the strip, we need to wrap around
            if( npos   > _num_leds ) npos = _num_leds;
        }
        CRGB col = color;

        col.nscale8(quadwave8(255*n));
        leds[npos%_num_leds] = col;

        // Serial.print(" LED:");
        // Serial.print(npos%_num_leds);
        
        // leds[npos%_num_leds] = leds[npos%_num_leds];

    }
    // Serial.println(" ");
    int trailingPos = pos - 1;
    int leadingPos = pos + len;
    // if pos is less than 0 make 0 
    if(trailingPos < 0) trailingPos = 0;
    if (leadingPos > _num_leds) leadingPos = _num_leds;
    leds[leadingPos%_num_leds] = CRGB::Black;
    leds[trailingPos%_num_leds] = CRGB::Black;
    
    
}
