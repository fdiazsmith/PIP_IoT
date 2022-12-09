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
        void shapeSection(int length);
        void tick_ms();
        void tick_bounce_ms();
        void mover();
        void turnOff();


        int pos;
        int len;
        bool wrap;
        CRGB color;
        int delay_ms;
        CRGB *leds;

    private:
        int _num_leds;
        unsigned long _lastMillis;
};


#endif
