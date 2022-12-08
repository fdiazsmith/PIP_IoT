#ifndef Dash_h
#define Dash_h

#include <Arduino.h>
#include <FastLED.h>

class Dash{
    public:
        Dash(int num_leds);
        void fill();
        void setup();
        void fadeall();
        
        int pos;
        bool wrap;
        CRGB color;
        int delay_ms;
        CRGB *leds;

    private:
        int _num_leds;
        unsigned long _lastMillis;
};


#endif
