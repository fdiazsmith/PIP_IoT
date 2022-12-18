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
    turnOff();
}

void Dash::setup(int length_, CRGB mainColor_, int delay_ms_, bool wrapindex_){
	wrap = wrapindex_;
	color = mainColor_;
	delay_ms = delay_ms_;
    len = length_;
    direction = 1;
    // turnOff();
}
void Dash::setup(int length_, CRGB mainColor_, int delay_ms_, bool wrapindex_, bool bounce_, int direction_, float domainStart_, float domainEnd_ , float life_){
	wrap = wrapindex_;
	color = mainColor_;
	delay_ms = delay_ms_;
    len = length_;
    bounce = bounce_;
    direction = direction_;
    domainStart = domainStart_;
    domainEnd = domainEnd_;
    life = life_;
    // turnOff();
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
    if ( bounce ){ // having both on is giving us a lot of edge cases.
        wrap = false;
    }
    // check if enough time has passed to update the dash
    if(millis() - _lastMillis > delay_ms){
        // if wrap is enabled, loop back to the beginning
        if(wrap && !bounce){
            if(pos >= _num_leds) pos = 0;

        }
        // if wrap is disabled, stop at the end of the strip
        else if(!wrap && !bounce){
            if(pos >= _num_leds) pos = _num_leds;
        }


        if ( bounce && (pos >= _num_leds - len)){
            pos = _num_leds - len;
            direction = -1;
        }
        else if ( bounce && (pos <= 0)){
            pos = 0;
            direction = 1;
        }

         // update the dash pos
        pos += direction;
        _cumulativeTicks += 1;
        age = _cumulativeTicks / ((float)_num_leds - (float)len);
 
        // save time of update
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
        if (age > life){
            _mainBrightness -= 1;
            if (_mainBrightness <= 0){
                kill = true;
                _mainBrightness = 0;
            }
        }

        col.nscale8(quadwave8(_mainBrightness*n));
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
