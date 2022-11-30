/*
BIG FUCKING TO DO: turn this logic into a class.
I  remember why I hate this shit. NOTHING FUCKING COMPILES! 

Rant over.


*/


void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

void cyclon(){
    static uint8_t hue = 0;
	// First slide the led in one direction
	for(int i = 0; i < NUM_LEDS; i++) {
		// Set the i'th led to red 
		leds[i] = CHSV(hue++, 255, 255);
		// Show the leds
		FastLED.show(); 
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(10);
	}
	

	// Now go in the other direction.  
	for(int i = (NUM_LEDS)-1; i >= 0; i--) {
		// Set the i'th led to red 
		leds[i] = CHSV(hue++, 255, 255);
		// Show the leds
		FastLED.show();
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(10);
	}
}
void fill(CRGB color ){
    for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = color;
    }
    FastLED.show(); 
}

void shapeSection(int len, int pos, bool wrap){
    // do a for loop and fill the leds with the color
    for(int i = pos; i < pos+len; i++) {
        float n = (float)i/(float)len;
        int npos =   pos + i;
        if(wrap){
            // if the section is longer than the strip, we need to wrap around
            leds[npos%NUM_LEDS] = CHSV(255, 255, 255*n);

        }
        else{
            if( npos   > NUM_LEDS ) npos = NUM_LEDS;
            leds[npos] = CHSV(255, 255, 255*n);
        }
        // leds[pos+i] = CHSV(0, 255, 255*n);
    }
}

// implement the tick_ms but with a struct by reference
void tick_bounce_ms(shape &s){
    if(millis() - s.lastMillis > s.delay_ms){
        s.pos++;
        s.lastMillis = millis();
    }
}
// implement tick bounce to take in a struct and modify it
void tick_bounce_ms(shape &s){
    if(millis() - s.lastMillis > s.delay_ms){
        if(s.wrap){
            s.pos++;
            if(s.pos >= NUM_LEDS) s.pos = 0;
        }
        else{
            s.pos++;
            if(s.pos >= NUM_LEDS) s.pos = NUM_LEDS;
        }
        s.lastMillis = millis();
    }
}



// implement mover to take in a struct
void mover(shape &s){
    // leds[pos] = CHSV(255, 255, 255);
    for (int i = 0; i < s.len; i++){
        /* code */
        float n = (float)i/(float)s.len;
        int npos =   s.pos + i;
        if (!s.wrap){
            // if the section is longer than the strip, we need to wrap around
            if( npos   > NUM_LEDS ) npos = NUM_LEDS;
        }
        CRGB col = s.color;

        col.nscale8(quadwave8(255*n));
        s.leds[npos%NUM_LEDS] = col;
        leds[npos%NUM_LEDS] += s.leds[npos%NUM_LEDS];

    }
    int trailingPos = s.pos - 1;
    int leadingPos = s.pos + s.len;
    // if pos is less than 0 make 0 
    if(trailingPos < 0) trailingPos = 0;
    if (leadingPos > NUM_LEDS) leadingPos = NUM_LEDS;
    s.leds[leadingPos%NUM_LEDS] = CRGB::Black;

    s.leds[trailingPos%NUM_LEDS] = CRGB::Black;
    // fadeall();
    
}

void turnOff(){
    for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
}